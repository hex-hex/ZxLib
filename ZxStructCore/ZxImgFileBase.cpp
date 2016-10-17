#include "StdAfx.h"
#include "ZxImgFileBase.h"


//int Image::ZxImgFileBase::m_DriverCount = 0;
int CalcDepth(const GDALDataType& _Type)
{
	int depth(0);
	switch(_Type)
	{
	case GDT_Byte:
		depth = 8;
		break;
	case GDT_UInt16:
	case GDT_Int16:
	case GDT_CInt16:
		depth = 16;
		break;
	case GDT_UInt32:
	case GDT_Int32:
	case GDT_Float32:
	case GDT_CInt32:
	case GDT_CFloat32:
		depth = 32;
		break;
	case GDT_CFloat64:
	case GDT_Float64:
		depth = 64;
		break;
	default:
		return 0;
	}
	return depth;
}

Raster::ZxImgFileBase::ZxImgFileBase(CRITICAL_SECTION& _Lock)
	:m_pDriver(NULL)
	,m_pDataSet(NULL)
	,m_IOLock(_Lock)
{
	memset(m_GeoTransformInv,0,sizeof(double) * 6);
	memset(m_GeoTransform,0,sizeof(double) * 6);
	GDALAllRegister();
}


Raster::ZxImgFileBase::~ZxImgFileBase(void)
{
	if (m_pDataSet != NULL)
	{
		GDALClose((GDALDatasetH)m_pDataSet);
	}
}


void Raster::ZxImgFileBase::MakeInvTransPara()
{
	double pamc = (m_GeoTransform[1] * m_GeoTransform[5] - m_GeoTransform[2] * m_GeoTransform[4]);
	m_GeoTransformInv[1] = m_GeoTransform[5] / pamc;
	m_GeoTransformInv[2] = - m_GeoTransform[2] / pamc;
	m_GeoTransformInv[4] = - m_GeoTransform[4] / pamc;
	m_GeoTransformInv[5] = m_GeoTransform[1] / pamc;
	m_GeoTransformInv[0] = - m_GeoTransformInv[1] * m_GeoTransform[0] - m_GeoTransformInv[2] * m_GeoTransform[3];
	m_GeoTransformInv[3] = - m_GeoTransformInv[4] * m_GeoTransform[0] - m_GeoTransformInv[5] * m_GeoTransform[3];
}


const double* Raster::ZxImgFileBase::GetTransformPara(bool _IsForewardPam/* = true*/)
{
	if (_IsForewardPam)
		return m_GeoTransform;
	else
		return m_GeoTransformInv;
}

char* Raster::ZxImgFileBase::GetWKT()
{
	return m_GeoRef.ExportWKT();
}


bool Raster::ZxImgFileBase::IsPointIn(Zx2DPoint _point)
{
	Zx2DPoint point;
	point.m_X = m_GeoTransformInv[0] + _point.m_X * m_GeoTransformInv[1] + _point.m_Y * m_GeoTransformInv[2];
	point.m_Y = m_GeoTransformInv[3] + _point.m_X * m_GeoTransformInv[4] + _point.m_Y * m_GeoTransformInv[5];
	if (point.m_X < 0 || point.m_X >= GetImageWidth())
		return false;
	else if (point.m_Y < 0 || point.m_Y >= GetImageHeight())
		return false;
	else
		return true;
}


ZxGeoRef& Raster::ZxImgFileBase::GetGeoRef()
{
	return m_GeoRef;
}


int Raster::ZxImgFileBase::GetBandCount(void)
{
	if (m_pDataSet)
		return ((GDALDataset*)m_pDataSet)->GetRasterCount();
	else
		return 0;
}


int Raster::ZxImgFileBase::GetImageWidth(void)
{
	if (m_pDataSet)
		return ((GDALDataset*)m_pDataSet)->GetRasterXSize();
	else
		return 0;
}


int Raster::ZxImgFileBase::GetImageHeight(void)
{
	if (m_pDataSet)
		return ((GDALDataset*)m_pDataSet)->GetRasterYSize();
	else
		return 0;
}


int Raster::ZxImgFileBase::GetBPC(void)
{
	if (m_pDataSet)
		return CalcDepth(((GDALDataset*)m_pDataSet)->GetRasterBand(1)->GetRasterDataType());
	else
		return 0;
}


int Raster::ZxImgFileBase::GetDataType(void)
{
	if (m_pDataSet)
		return (int)(((GDALDataset*)m_pDataSet)->GetRasterBand(1)->GetRasterDataType());
	else
		return 0;
}