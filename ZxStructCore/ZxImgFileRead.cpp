#include "StdAfx.h"
#include "ZxImgFileRead.h"


Raster::ZxImgFileRead::ZxImgFileRead(CRITICAL_SECTION& _Lock)
	:ZxImgFileBase(_Lock)
{
}


Raster::ZxImgFileRead::~ZxImgFileRead(void)
{
}


bool Raster::ZxImgFileRead::SetFilePath(const char* _FileName)
{
	if (!ZxFileBase::SetFilePath(_FileName))
	{
		ZeroMemory(m_PhysicalPath,MAX_PATH);
		return false;
	}

	m_pDataSet = (void*)GDALOpen(_FileName,GA_ReadOnly);
	if (m_pDataSet == NULL)
	{
		ZeroMemory(m_PhysicalPath,MAX_PATH);
		return false;
	}
	m_pDriver = ((GDALDataset*)m_pDataSet)->GetDriver();
	size_t wktLength = strlen(((GDALDataset*)m_pDataSet)->GetProjectionRef());
	if(wktLength)
	{
		char* pWKT = new char[wktLength+1];
		strcpy_s(pWKT,wktLength + 1,((GDALDataset*)m_pDataSet)->GetProjectionRef());
		m_GeoRef.ImportWKT(pWKT);
	}
	else
	{
		m_GeoRef.ImportWKT(NULL);
	}
	((GDALDataset*)m_pDataSet)->GetGeoTransform(m_GeoTransform);
	MakeInvTransPara();
	return true;
}



bool Raster::ZxImgFileRead::Read8U(ZxImgBase* _pImg, ZxImgBase::ZxImgIOParamBase* _ReadOption)
{
	if(_pImg->GetDepth()/_pImg->GetBand() != 8)
		return false;
	EnterCriticalSection(&m_IOLock);
	for (int i = 0; i != _pImg->GetBand(); i++)
	{
		if (_ReadOption->m_Channel[i] != 0)
		{
			((GDALDataset*)m_pDataSet)->GetRasterBand(_ReadOption->m_Channel[i])->RasterIO(GF_Read,
				_ReadOption->m_pRegion->m_Left,_ReadOption->m_pRegion->m_Top,
				_ReadOption->m_pRegion->m_Width,
				_ReadOption->m_pRegion->m_Height,
				_pImg->GetImgData() + i,
				_pImg->GetWidth(),
				_pImg->GetHeight(),
				GDT_Byte,
				_pImg->GetBand(), _pImg->GetWidthStep());
		}
	}
	LeaveCriticalSection(&m_IOLock);
	return true;
}

bool Raster::ZxImgFileRead::Read16U(ZxImgBase* _pImg, ZxImgBase::ZxImgIOParamBase* _ReadOption)
{
	if(_pImg->GetDepth()/_pImg->GetBand() != 16)
		return false;
	EnterCriticalSection(&m_IOLock);
	for (int i = 0; i != _pImg->GetBand(); i++)
	{
		if (_ReadOption->m_Channel[i] != 0)
		{
			((GDALDataset*)m_pDataSet)->GetRasterBand(_ReadOption->m_Channel[i])->RasterIO(GF_Read,
				_ReadOption->m_pRegion->m_Left,_ReadOption->m_pRegion->m_Top,
				_ReadOption->m_pRegion->m_Width,
				_ReadOption->m_pRegion->m_Height,
				_pImg->GetImgData() + i * 2,
				_pImg->GetWidth(),
				_pImg->GetHeight(),
				GDT_UInt16,
				_pImg->GetBand() * 2, _pImg->GetWidthStep());
		}
	}
	LeaveCriticalSection(&m_IOLock);
	return true;
}

bool Raster::ZxImgFileRead::Read32U(ZxImgBase* _pImg, ZxImgBase::ZxImgIOParamBase* _ReadOption)
{
	if(_pImg->GetDepth()/_pImg->GetBand() != 32)
		return false;
	EnterCriticalSection(&m_IOLock);
	for (int i = 0; i != _pImg->GetBand(); i++)
	{
		if (_ReadOption->m_Channel[i] != 0)
		{
			((GDALDataset*)m_pDataSet)->GetRasterBand(_ReadOption->m_Channel[i])->RasterIO(GF_Read,
				_ReadOption->m_pRegion->m_Left,_ReadOption->m_pRegion->m_Top,
				_ReadOption->m_pRegion->m_Width,
				_ReadOption->m_pRegion->m_Height,
				_pImg->GetImgData() + i * 4,
				_pImg->GetWidth(),
				_pImg->GetHeight(),
				GDT_UInt32,
				_pImg->GetBand() * 4, _pImg->GetWidthStep());
		}
	}
	LeaveCriticalSection(&m_IOLock);
	return true;
}

bool Raster::ZxImgFileRead::DoSafeRead(ZxImgBase* _pImg, ZxImgBase::ZxImgIOParamBase* _ReadOption)
{
	if (_ReadOption->GetMaxChannel() > _pImg->GetBand())
		return false;
	if (_ReadOption->GetMaxBand() > ((GDALDataset*)m_pDataSet)->GetRasterCount())
		return false;
	switch(GetDataType())
	{
	case GDT_Byte:
		return Read8U(_pImg,_ReadOption);
	case GDT_UInt16:
		return Read16U(_pImg,_ReadOption);
	case GDT_UInt32:
		return Read32U(_pImg,_ReadOption);
	default:
		return false;
	}
}

// void Raster::ZxImgFileRead::DoQuickRead(ZxImgDisplay* _pImg, ZxImgBase::ZxImgIOParamBase* _ReadOption)
// {
// 	EnterCriticalSection(&m_IOLock);
// 	for (int i = 0; i != 4; i++)
// 	{
// 		if (_ReadOption->m_Channel[i] != 0)
// 		{
// 			((GDALDataset*)m_pDataSet)->GetRasterBand(_ReadOption->m_Channel[i])->RasterIO(GF_Read,
// 				_ReadOption->m_pRegion->m_Left,_ReadOption->m_pRegion->m_Top,
// 				_ReadOption->m_pRegion->m_Width,
// 				_ReadOption->m_pRegion->m_Height,
// 				_pImg->GetImgData() + i,
// 				_pImg->GetWidth(),
// 				_pImg->GetHeight(),
// 				GDT_Byte,
// 				4, _pImg->GetWidthStep());
// 		}
// 	}
// 	LeaveCriticalSection(&m_IOLock);
// }
//
// void  Raster::ZxImgFileRead::DoQuickRead(ZxImg64Bit* _pImg,	ZxImgBase::ZxImgIOParamBase* _ReadOption)
// {
// 	EnterCriticalSection(&m_IOLock);
// 	for (int i = 0; i != 4; i++)
// 	{
// 		if (_ReadOption->m_Channel[i] != 0)
// 		{
// 			((GDALDataset*)m_pDataSet)->GetRasterBand(_ReadOption->m_Channel[i])->RasterIO(GF_Read,
// 				_ReadOption->m_pRegion->m_Left,_ReadOption->m_pRegion->m_Top,
// 				_ReadOption->m_pRegion->m_Width,
// 				_ReadOption->m_pRegion->m_Height,
// 				_pImg->GetImgData() + i * 2,
// 				_pImg->GetWidth(),
// 				_pImg->GetHeight(),
// 				GDT_UInt16,
// 				8, _pImg->GetWidthStep());
// 		}
// 	}
// 	LeaveCriticalSection(&m_IOLock);
// }
// 
// void Raster::ZxImgFileRead::DoQuickRead(ZxImg24Bit* _pImg, ZxImgBase::ZxImgIOParamBase* _ReadOption)
// {
// 	EnterCriticalSection(&m_IOLock);
// 	for (int i = 0; i != 3; i++)
// 	{
// 		if (_ReadOption->m_Channel[i] != 0)
// 		{
// 			((GDALDataset*)m_pDataSet)->GetRasterBand(_ReadOption->m_Channel[i])->RasterIO(GF_Read,
// 				_ReadOption->m_pRegion->m_Left,_ReadOption->m_pRegion->m_Top,
// 				_ReadOption->m_pRegion->m_Width,
// 				_ReadOption->m_pRegion->m_Height,
// 				_pImg->GetImgData() + i,
// 				_pImg->GetWidth(),
// 				_pImg->GetHeight(),
// 				GDT_Byte,
// 				3, _pImg->GetWidthStep());
// 		}
// 	}
// 	LeaveCriticalSection(&m_IOLock);
// }


void Raster::ZxImgFileRead::DoQuickReadMatrix(ZxMatrix& _Mat, const ZxInt2DPOINT& _HeaderPoint, int _Band)
{
	EnterCriticalSection(&m_IOLock);
	((GDALDataset*)m_pDataSet)->GetRasterBand(_Band)->RasterIO(GF_Read,
		_HeaderPoint.m_X,_HeaderPoint.m_Y,
		_Mat.GetCol(),
		_Mat.GetRow(),
		_Mat.GetData(),
		_Mat.GetCol(),
		_Mat.GetRow(),
		GDT_Float64,8
		, _Mat.GetCol() * 8);
	LeaveCriticalSection(&m_IOLock);
}