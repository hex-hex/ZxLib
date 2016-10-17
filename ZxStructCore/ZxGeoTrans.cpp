#include "StdAfx.h"
#include "ZxGeoTrans.h"
#define PARA_N (fa / sqrt(1 - feSqr * sin(fPhy) * sin(fPhy)))

GeoReference::ZxGeoTrans::ZxGeoTrans(void)
	:m_Trans(NULL)
	,m_hGeoRefTemp(NULL)
	,m_pDst(NULL)
	,m_pSrc(NULL)
{
}


GeoReference::ZxGeoTrans::~ZxGeoTrans(void)
{
	if (m_Trans)
	{
		OCTDestroyCoordinateTransformation((OGRCoordinateTransformationH)m_Trans);
	}
	if (m_hGeoRefTemp)
	{
		OSRDestroySpatialReference((OGRSpatialReferenceH)m_hGeoRefTemp);
	}
}

bool GeoReference::ZxGeoTrans::DoTransSelf(Zx3DPoint* _pPoint)
{
	if (m_pDst->GetType() == Projction &&
		m_pSrc->GetType() == Projction)
	{
		if(m_Trans == NULL)
		{
			m_Trans = (void*)OCTNewCoordinateTransformation(
				(OGRSpatialReferenceH)(m_pSrc->GetData()),
				(OGRSpatialReferenceH)(m_pDst->GetData()));
		}
		OCTTransform((OGRCoordinateTransformationH)m_Trans,
			1, &(_pPoint->m_X), &(_pPoint->m_Y), &(_pPoint->m_Z));
		return true;
	}
	else if (m_pDst->GetType() == ECR &&
		m_pSrc->GetType() == Projction)
	{
		if(OSRIsProjected((OGRSpatialReferenceH)(m_pSrc->GetData())))
		{
			OCTTransform((OGRCoordinateTransformationH)m_Trans,
				1, &(_pPoint->m_X), &(_pPoint->m_Y), &(_pPoint->m_Z));
		}
		double a = OSRGetSemiMajor((OGRSpatialReferenceH)(m_pSrc->GetData()),NULL);
		double b = OSRGetSemiMinor((OGRSpatialReferenceH)(m_pSrc->GetData()),NULL);
		double feSqr = (a * a - b * b)/(a * a);
		double fLamda,fPhy,fh,N;
		fPhy = _pPoint->m_Y / 180 * g_dbPI;
		fLamda = _pPoint->m_X / 180 * g_dbPI;
		fh = _pPoint->m_Z;
		N = a/sqrt(1 - sin(fPhy)*sin(fPhy)*feSqr);
		_pPoint->m_X = (N + fh) * cos(fPhy) * cos(fLamda);
		_pPoint->m_Y = (N + fh) * cos(fPhy) * sin(fLamda);
		_pPoint->m_Z = (N * (1 - feSqr) + fh) * sin(fPhy);	
		return true;
	}
	else if (m_pDst->GetType() == Projction &&
		m_pSrc->GetType() == ECR)
	{
		double fLamda, fPhy, fh;
		double fa = OSRGetSemiMajor((OGRSpatialReferenceH)(m_pDst->GetData()),NULL);
		double fb = OSRGetSemiMinor((OGRSpatialReferenceH)(m_pDst->GetData()),NULL);
		double feSqr = (fa * fa - fb * fb)/(fa * fa);
		if (fabs(_pPoint->m_X) < 1E-10)
		{
			if (_pPoint->m_Y < 0)
			{
				fLamda = -g_dbPI/2;
			}
			else
			{
				fLamda = g_dbPI/2;
			}
		}
		else
		{
			fLamda = atan(_pPoint->m_Y / _pPoint->m_X);
			if (_pPoint->m_X < 0)
			{
				if (_pPoint->m_Y < 0)
				{
					fLamda -= g_dbPI;
				}
				else
				{
					fLamda += g_dbPI;
				}
			}
		}
		double fPhyPre = fPhy = 
			asin(_pPoint->m_Z / sqrt(_pPoint->m_X * _pPoint->m_X + 
			_pPoint->m_Y * _pPoint->m_Y + _pPoint->m_Z * _pPoint->m_Z));
		do 
		{
			fPhyPre = fPhy;
			fPhy = atan(
				(_pPoint->m_Z + feSqr * sin(fPhy) * PARA_N) 
				/ sqrt(_pPoint->m_X * _pPoint->m_X + _pPoint->m_Y * _pPoint->m_Y)
				);
		} while (fabs(fPhyPre - fPhy) < 1e-10);
		fh = sqrt(
			_pPoint->m_X * _pPoint->m_X + _pPoint->m_Y * _pPoint->m_Y + 
			pow(_pPoint->m_Z + feSqr * PARA_N * sin(fPhy),2)
			) - PARA_N;
		_pPoint->m_X = fLamda * 180 / g_dbPI;
		_pPoint->m_Y = fPhy * 180 / g_dbPI;
		_pPoint->m_Z = fh;

		if(OSRIsProjected((OGRSpatialReferenceH)(m_pDst->GetData())))
		{
			OCTTransform((OGRCoordinateTransformationH)m_Trans,
				1, &(_pPoint->m_X), &(_pPoint->m_Y), &(_pPoint->m_Z));
		}
		return true;
	}
	else
		return false;
}

void GeoReference::ZxGeoTrans::SetSource(const ZxGeoRef* _pGeoRef)
{
	if (m_pSrc == _pGeoRef)
	{
		return;
	}
	else
	{
		m_pSrc = const_cast<ZxGeoRef*>(_pGeoRef);
		PrepareTrans();
	}
}


void GeoReference::ZxGeoTrans::SetTarget(const ZxGeoRef* _pGeoRef)
{
	if(m_pDst == _pGeoRef)
	{	
		return;
	}
	else
	{
		m_pDst = const_cast<ZxGeoRef*>(_pGeoRef);
		PrepareTrans();
	}
}


void GeoReference::ZxGeoTrans::PrepareTrans(void)
{
	if (!(m_pDst && m_pSrc))
	{
		return;
	}
	if (m_pDst->GetType() == Projction && m_pSrc->GetType() == ECR)
	{
		if(m_Trans)
			OCTDestroyCoordinateTransformation((OGRCoordinateTransformationH)m_Trans);
		if (m_hGeoRefTemp)
			OSRDestroySpatialReference((OGRSpatialReferenceH)m_hGeoRefTemp);

		m_hGeoRefTemp
			= (void*)OSRCloneGeogCS((OGRSpatialReferenceH)(m_pDst->GetData()));
		m_Trans = (void*)OCTNewCoordinateTransformation(
			(OGRSpatialReferenceH)m_hGeoRefTemp,
			(OGRSpatialReferenceH)(m_pDst->GetData()));
	}
	else if (m_pDst->GetType() == ECR && m_pSrc->GetType() == Projction)
	{
		if(m_Trans)
			OCTDestroyCoordinateTransformation((OGRCoordinateTransformationH)m_Trans);
		if (m_hGeoRefTemp)
			OSRDestroySpatialReference((OGRSpatialReferenceH)m_hGeoRefTemp);

		m_hGeoRefTemp 
			= (void*)OSRCloneGeogCS((OGRSpatialReferenceH)(m_pSrc->GetData()));
		m_Trans = (void*)OCTNewCoordinateTransformation(
			(OGRSpatialReferenceH)(m_pSrc->GetData()),
			(OGRSpatialReferenceH)m_hGeoRefTemp);
	}
}