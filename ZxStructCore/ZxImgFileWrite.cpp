#include "StdAfx.h"
#include "ZxImgFileWrite.h"


Raster::ZxImgFileWrite::ZxImgFileWrite(CRITICAL_SECTION& _Lock)
	:ZxImgFileBase(_Lock)
{
}


Raster::ZxImgFileWrite::~ZxImgFileWrite(void)
{

}

bool Raster::ZxImgFileWrite::SetFilePath(const char* _FileName)
{
	ZeroMemory(m_PhysicalPath,MAX_PATH);
	CString strFileName(_FileName);
	strFileName.MakeLower();
	strcpy_s(m_PhysicalPath,MAX_PATH,strFileName);

	CString strExt(GetFileExt());
	GDALDriver** ppoDriver = (GDALDriver**)(&m_pDriver);
	GDALDriver*& poDriver = *ppoDriver;
	strExt.MakeLower().TrimLeft(_T('.'));
	if (strExt == "bmp")
		poDriver = GetGDALDriverManager()->GetDriverByName("BMP");
	else if (strExt == "jpg" || strExt == "jpge")
		poDriver = GetGDALDriverManager()->GetDriverByName("JPEG");
	else if (strExt == "tif" || strExt == "tiff")
		poDriver = GetGDALDriverManager()->GetDriverByName("GTiff");
	else if (strExt == "img")
		poDriver = GetGDALDriverManager()->GetDriverByName("HFA");
	else if (strExt == "bt")
		poDriver = GetGDALDriverManager()->GetDriverByName("BT");
	else if (strExt == "ecw")
		poDriver = GetGDALDriverManager()->GetDriverByName("ECW");
	else if (strExt == "fits")
		poDriver = GetGDALDriverManager()->GetDriverByName("FITS");
	else if (strExt == "gif")
		poDriver = GetGDALDriverManager()->GetDriverByName("GIF");
	else if (strExt == "hdf")
		poDriver = GetGDALDriverManager()->GetDriverByName("HDF4");
	else if (strExt == "hdr")
		poDriver = GetGDALDriverManager()->GetDriverByName("EHdr");
	else
		poDriver = NULL;

	if( poDriver == NULL )
	{
		ZeroMemory(m_PhysicalPath,MAX_PATH);
		return false;
	}

	return true;
}


bool Raster::ZxImgFileWrite::CreateUInteger16(int _Height, int _Width, int _BandCount)
{
	EnterCriticalSection(&m_IOLock);
	if (m_pDataSet !=  NULL)
	{
		GDALClose((GDALDatasetH)m_pDataSet);
	}

	const unsigned __int64 Free = ZxFileAbstract::GetDriverFreeSpace(this);
	if (Free < _Height * _Width * _BandCount * 2 + 200)//假设文件头占200字节
		return false;

	GDALDriver** ppoDriver = (GDALDriver**)(&m_pDriver);
	GDALDriver*& poDriver = *ppoDriver;

	char **papszOptions = NULL;
	m_pDataSet =(void*)( poDriver->
		Create( m_PhysicalPath, _Width, _Height, _BandCount, GDT_UInt16, papszOptions ));
	if (m_pDataSet == NULL)
	{
		return false;
	}

	LeaveCriticalSection(&m_IOLock);
	return true;
}

bool Raster::ZxImgFileWrite::CreateUInteger32(int _Height, int _Width, int _BandCount)
{
	EnterCriticalSection(&m_IOLock);
	if (m_pDataSet !=  NULL)
	{
		GDALClose((GDALDatasetH)m_pDataSet);
	}

	const unsigned __int64 Free = ZxFileAbstract::GetDriverFreeSpace(this);
	if (Free < _Height * _Width * _BandCount * 4 + 200)//假设文件头占200字节
		return false;

	GDALDriver** ppoDriver = (GDALDriver**)(&m_pDriver);
	GDALDriver*& poDriver = *ppoDriver;

	char **papszOptions = NULL;
	m_pDataSet =(void*)( poDriver->
		Create( m_PhysicalPath, _Width, _Height, _BandCount, GDT_UInt32, papszOptions ));
	if (m_pDataSet == NULL)
	{
		return false;
	}

	LeaveCriticalSection(&m_IOLock);
	return true;
}

bool Raster::ZxImgFileWrite::CreateByte(int _Height, int _Width, int _BandCount)
{
	EnterCriticalSection(&m_IOLock);
	if (m_pDataSet !=  NULL)
	{
		GDALClose((GDALDatasetH)m_pDataSet);
	}

	const unsigned __int64 Free = ZxFileAbstract::GetDriverFreeSpace(this);
	if (Free < _Height * _Width * _BandCount + 200)//假设文件头占200字节
		return false;

	GDALDriver** ppoDriver = (GDALDriver**)(&m_pDriver);
	GDALDriver*& poDriver = *ppoDriver;

	char **papszOptions = NULL;
	m_pDataSet =(void*)( poDriver->
		Create( m_PhysicalPath, _Width, _Height, _BandCount, GDT_Byte, papszOptions ));
	if (m_pDataSet == NULL)
	{
		return false;
	}

	LeaveCriticalSection(&m_IOLock);
	return true;
}


bool Raster::ZxImgFileWrite::CreateDouble(int _Height, int _Width, int _BandCount)
{
	EnterCriticalSection(&m_IOLock);
	if (m_pDataSet !=  NULL)
	{
		GDALClose((GDALDatasetH)m_pDataSet);
	}

	const unsigned __int64 Free = ZxFileAbstract::GetDriverFreeSpace(this);
	if (Free < _Height * _Width * _BandCount * 8 + 200)//假设文件头占200字节
		return false;

	GDALDriver** ppoDriver = (GDALDriver**)(&m_pDriver);
	GDALDriver*& poDriver = *ppoDriver;

	char **papszOptions = NULL;
	m_pDataSet =(void*)( poDriver->
		Create( m_PhysicalPath, _Width, _Height, _BandCount, GDT_Float64, papszOptions ));
	if (m_pDataSet == NULL)
	{
		return false;
	}

	LeaveCriticalSection(&m_IOLock);
	return true;
}


bool Raster::ZxImgFileWrite::SetProjection(const double* _pTransformParam, const ZxGeoRef& _GeoRef)
{
	if (_GeoRef.GetType() != Projction)
	{
		return false;
	}
	m_GeoRef = _GeoRef;
	SetTransPara(_pTransformParam);
	char* strWKT = m_GeoRef.ExportWKT();
	EnterCriticalSection(&m_IOLock);
	((GDALDataset*)m_pDataSet)->SetGeoTransform(m_GeoTransform);
	((GDALDataset*)m_pDataSet)->SetProjection(strWKT);
	LeaveCriticalSection(&m_IOLock);
	delete[] strWKT;
	return true;
}


void Raster::ZxImgFileWrite::SetTransPara(const double* _pPara)
{
	memcpy_s(m_GeoTransform,6 * sizeof(double), _pPara, 6 * sizeof(double));
	MakeInvTransPara();
}


void Raster::ZxImgFileWrite::DoQuickWriteMatrix(ZxMatrix& _Mat, const ZxInt2DPOINT& _HeaderPoint, int _Band)
{
	EnterCriticalSection(&m_IOLock);
	((GDALDataset*)m_pDataSet)->GetRasterBand(_Band)->RasterIO(GF_Write,
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

bool Raster::ZxImgFileWrite::DoFullWrite(ZxImgBase* _pImg)
{
	ZxImgBase::ZxImgIOParamBase IOParam;
	IOParam.m_pRegion = new ZxIntRECT(0,0,_pImg->GetWidth(),_pImg->GetHeight());

	delete IOParam.m_pRegion;
	return true;
}

bool Raster::ZxImgFileWrite::DoSafeWrite(ZxImgBase* _pImg, ZxImgBase::ZxImgIOParamBase* _WiriteOption)
{
	if (_WiriteOption->GetMaxChannel() > _pImg->GetBand())
		return false;
	if (_WiriteOption->GetMaxBand() > ((GDALDataset*)m_pDataSet)->GetRasterCount())
		return false;
	switch(GetDataType())
	{
	case GDT_Byte:
		return Write8U(_pImg,_WiriteOption);
	case GDT_UInt16:
		return Write16U(_pImg,_WiriteOption);
	case GDT_UInt32:
		return Write32U(_pImg,_WiriteOption);
	default:
		return false;
	}
	return true;
}

bool Raster::ZxImgFileWrite::Write8U(ZxImgBase* _pImg, ZxImgBase::ZxImgIOParamBase* _WiriteOption)
{
	if(_pImg->GetDepth()/_pImg->GetBand() != 8)
		return false;
	EnterCriticalSection(&m_IOLock);
	for (int i = 0; i < 4; i++)
	{
		if (_WiriteOption->m_Channel[i] != 0)
		{
			((GDALDataset*)m_pDataSet)->GetRasterBand(_WiriteOption->m_Channel[i])->RasterIO(GF_Write,
				_WiriteOption->m_pRegion->m_Left,_WiriteOption->m_pRegion->m_Top,
				_WiriteOption->m_pRegion->m_Width,
				_WiriteOption->m_pRegion->m_Height,
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

bool Raster::ZxImgFileWrite::Write16U(ZxImgBase* _pImg, ZxImgBase::ZxImgIOParamBase* _WiriteOption)
{
	if(_pImg->GetDepth()/_pImg->GetBand() != 16)
		return false;
	EnterCriticalSection(&m_IOLock);
	for (int i = 0; i < 4; i++)
	{
		if (_WiriteOption->m_Channel[i] != 0)
		{
			((GDALDataset*)m_pDataSet)->GetRasterBand(_WiriteOption->m_Channel[i])->RasterIO(GF_Write,
				_WiriteOption->m_pRegion->m_Left,_WiriteOption->m_pRegion->m_Top,
				_WiriteOption->m_pRegion->m_Width,
				_WiriteOption->m_pRegion->m_Height,
				_pImg->GetImgData() + i * 2,
				_pImg->GetWidth(),
				_pImg->GetHeight(),
				GDT_Int16,
				_pImg->GetBand() * 2, _pImg->GetWidthStep());
		}
	}
	LeaveCriticalSection(&m_IOLock);
	return true;
}

bool Raster::ZxImgFileWrite::Write32U(ZxImgBase* _pImg, ZxImgBase::ZxImgIOParamBase* _WiriteOption)
{
	if(_pImg->GetDepth()/_pImg->GetBand() != 32)
		return false;
	EnterCriticalSection(&m_IOLock);
	for (int i = 0; i < 4; i++)
	{
		if (_WiriteOption->m_Channel[i] != 0)
		{
			((GDALDataset*)m_pDataSet)->GetRasterBand(_WiriteOption->m_Channel[i])->RasterIO(GF_Write,
				_WiriteOption->m_pRegion->m_Left,_WiriteOption->m_pRegion->m_Top,
				_WiriteOption->m_pRegion->m_Width,
				_WiriteOption->m_pRegion->m_Height,
				_pImg->GetImgData() + i * 4,
				_pImg->GetWidth(),
				_pImg->GetHeight(),
				GDT_CInt32,
				_pImg->GetBand() * 4, _pImg->GetWidthStep());
		}
	}
	LeaveCriticalSection(&m_IOLock);
	return true;
}

// void Raster::ZxImgFileWrite::DoQuickWrite(ZxImg32Bit* _pImg, ZxImgBase::ZxImgIOParamBase* _WiriteOption)
// {
// 	EnterCriticalSection(&m_IOLock);
// 	for (int i = 0; i < 4; i++)
// 	{
// 		if (_WiriteOption->m_Channel[i] != 0)
// 		{
// 			((GDALDataset*)m_pDataSet)->GetRasterBand(_WiriteOption->m_Channel[i])->RasterIO(GF_Write,
// 				_WiriteOption->m_pRegion->m_Left,_WiriteOption->m_pRegion->m_Top,
// 				_WiriteOption->m_pRegion->m_Width,
// 				_WiriteOption->m_pRegion->m_Height,
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
// 
// void Raster::ZxImgFileWrite::DoQuickWrite(ZxImg24Bit* _pImg, ZxImgBase::ZxImgIOParamBase* _WiriteOption)
// {
// 	EnterCriticalSection(&m_IOLock);
// 	for (int i = 0; i < 3; i++)
// 	{
// 		if (_WiriteOption->m_Channel[i] != 0)
// 		{
// 			((GDALDataset*)m_pDataSet)->GetRasterBand(_WiriteOption->m_Channel[i])->RasterIO(GF_Write,
// 				_WiriteOption->m_pRegion->m_Left,_WiriteOption->m_pRegion->m_Top,
// 				_WiriteOption->m_pRegion->m_Width,
// 				_WiriteOption->m_pRegion->m_Height,
// 				_pImg->GetImgData() + i,
// 				_pImg->GetWidth(),
// 				_pImg->GetHeight(),
// 				GDT_Byte,
// 				3, _pImg->GetWidthStep());
// 		}
// 	}
// 	LeaveCriticalSection(&m_IOLock);
// }
// 
// void Raster::ZxImgFileWrite::DoQuickWrite(ZxImg64Bit* _pImg,	ZxImgBase::ZxImgIOParamBase* _WiriteOption)
// {
// 	EnterCriticalSection(&m_IOLock);
// 	for (int i = 0; i < 4; i++)
// 	{
// 		if (_WiriteOption->m_Channel[i] != 0)
// 		{
// 			((GDALDataset*)m_pDataSet)->GetRasterBand(_WiriteOption->m_Channel[i])->RasterIO(GF_Write,
// 				_WiriteOption->m_pRegion->m_Left,_WiriteOption->m_pRegion->m_Top,
// 				_WiriteOption->m_pRegion->m_Width,
// 				_WiriteOption->m_pRegion->m_Height,
// 				_pImg->GetImgData() + i * 2,
// 				_pImg->GetWidth(),
// 				_pImg->GetHeight(),
// 				GDT_Int16,
// 				8, _pImg->GetWidthStep());
// 		}
// 	}
// 	LeaveCriticalSection(&m_IOLock);
// }