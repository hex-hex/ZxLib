#include "StdAfx.h"
#include "ZxGeoRef.h"


GeoReference::ZxGeoRef::ZxGeoRef(void)
	: m_strLength(0)
	, m_Mark(Projction)
{
	m_pSR = (void*)OSRNewSpatialReference("GEOGCS[\"WGS 84\",DATUM[\"WGS_1984\",SPHEROID[\"WGS 84\",6378137,298.257223563,AUTHORITY[\"EPSG\",\"7030\"]],TOWGS84[0,0,0,0,0,0,0],AUTHORITY[\"EPSG\",\"6326\"]],PRIMEM[\"Greenwich\",0,AUTHORITY[\"EPSG\",\"8901\"]],UNIT[\"degree\",0.0174532925199433,AUTHORITY[\"EPSG\",\"9108\"]],AUTHORITY[\"EPSG\",\"4326\"]]");
}

GeoReference::ZxGeoRef::ZxGeoRef(const ZxGeoRef& _Ref)
	:m_strLength(_Ref.m_strLength)
	,m_Mark(_Ref.m_Mark)
{
	m_pSR = (void*)OSRClone((OGRSpatialReferenceH)(_Ref.m_pSR));
}

GeoReference::ZxGeoRef::~ZxGeoRef(void)
{
	if(m_pSR)
		OSRDestroySpatialReference((OGRSpatialReferenceH)m_pSR);
}


bool  GeoReference::ZxGeoRef::operator==(const GeoReference::ZxGeoRef& rhs)
{
	if (m_Mark == rhs.m_Mark)
	{
		if(m_Mark == Projction)
		{
			CString strWKT1 = ExportWKT();
			CString strWKT2 = rhs.ExportWKT();
			if (strWKT1 == strWKT2)
				return true;
			else
				return false;
		}
		else
			return true;
	}
	else
		return false;
}


void GeoReference::ZxGeoRef::CloneFrom(ZxGeoRef* _pGeoRef)
{
	m_Mark = _pGeoRef->GetType();
	if (m_Mark == Projction)
	{
		m_pSR = (void*)OSRClone((OGRSpatialReferenceH)(_pGeoRef->m_pSR));
	}
}

GeoReference::ZxGeoRef& GeoReference::ZxGeoRef::operator=(const GeoReference::ZxGeoRef& rhs)
{
	if(&rhs != this)
	{
		m_Mark = rhs.m_Mark;
		m_strLength = rhs.m_strLength;
		if(m_Mark == Projction)
			m_pSR = (void*)OSRClone((OGRSpatialReferenceH)(rhs.m_pSR));
	}
	return *this;
}

void* GeoReference::ZxGeoRef::GetData()
{
	return m_pSR;
}

void GeoReference::ZxGeoRef::SetNone()
{
	m_Mark = None;
}

bool GeoReference::ZxGeoRef::SetUTM(int _Zone)
{
	if(OSRSetUTM((OGRSpatialReferenceH)m_pSR,_Zone,true) == OGRERR_NONE)
		return true;
	else
		return false;
}


void GeoReference::ZxGeoRef::Reset(void)
{
	m_Mark = Projction;
	OSRDestroySpatialReference((OGRSpatialReferenceH)m_pSR);
	m_pSR = OSRNewSpatialReference(NULL);
	OSRSetWellKnownGeogCS((OGRSpatialReferenceH)m_pSR,"WGS84");
}


bool GeoReference::ZxGeoRef::SetTransverseMercator(double  _dbCenterLat,  
	double  _dbCenterLong,  
	double  _dbScale,  
	double  _dbFalseEasting,  
	double  _dbFalseNorthing ) 
{
	if (OSRSetTM((OGRSpatialReferenceH)m_pSR,_dbCenterLat,_dbCenterLong,_dbScale,_dbFalseEasting,_dbFalseNorthing))
	{
		return true;
	}
	else
		return false;
}


void GeoReference::ZxGeoRef::SetECR()
{
	m_Mark = ECR;
}


void GeoReference::ZxGeoRef::SetOrbit()
{
	m_Mark = Orbit;
}


GeoReference::ZxRefType GeoReference::ZxGeoRef::GetType() const
{
	return m_Mark;
}


void GeoReference::ZxGeoRef::ImportWKT(char* _StringWKT)
{
	if (_StringWKT)
	{
		m_strLength = strlen(_StringWKT);
		OSRImportFromWkt((OGRSpatialReferenceH)m_pSR,&_StringWKT);
		m_Mark = Projction;
	}
	else
	{
		m_strLength = 0;
		m_Mark = None;
	}
}

char* GeoReference::ZxGeoRef::ExportWKT() const
{
	if (m_strLength)
	{
		char * pWKT = new char[m_strLength + 1];
		OSRExportToWkt((OGRSpatialReferenceH)m_pSR,&pWKT);
		return pWKT;
	}
	else
		return NULL;
}