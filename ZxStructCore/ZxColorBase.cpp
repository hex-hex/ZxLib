#include "StdAfx.h"
#include "ZxColorBase.h"
#include "ZxGeoRef.h"
using namespace GeoReference;

Raster::ZxColorBase::ZxColorBase(void)
{
}


Raster::ZxColorBase::ZxColorBase(ZxDN& _DN)
	:m_dbVal0(_DN.m_ExportByte[2])//R
	,m_dbVal1(_DN.m_ExportByte[1])//G
	,m_dbVal2(_DN.m_ExportByte[0])//B
	,m_Type(ZxRGB)
{

}

Raster::ZxColorBase::ZxColorBase(const ZxColorBase& _Color)
	:m_dbVal0(_Color.m_dbVal0)
	,m_dbVal1(_Color.m_dbVal1)
	,m_dbVal2(_Color.m_dbVal2)
	,m_Type(_Color.m_Type)
{

}

Raster::ZxColorBase::~ZxColorBase(void)
{

}

void Raster::ZxColorBase::RGB2HSV()
{
	ZxColorBase Src(*this);
	m_Type = ZxHSV;
	if (Src.m_dbVal0 > Src.m_dbVal1)
	{
		if (Src.m_dbVal2 > Src.m_dbVal0)//2,0,1
		{
			m_dbVal2 = Src.m_dbVal2;
			m_dbVal1 = 255 * (m_dbVal2 - Src.m_dbVal1) / m_dbVal2;
			m_dbVal0 = (Src.m_dbVal1 - Src.m_dbVal0) * g_dbThirdPI / m_dbVal1;
		}
		else
		{
			if (Src.m_dbVal2 > Src.m_dbVal1)//0,2,1
			{
				m_dbVal2 = Src.m_dbVal0;
				m_dbVal1 = 255 * (m_dbVal2 - Src.m_dbVal1) / m_dbVal2;
				m_dbVal0 = g_dbThirdPI * 4 + (Src.m_dbVal2 - Src.m_dbVal1) * g_dbThirdPI / m_dbVal1;
			}
			else//0,1,2
			{
				if (Src.m_dbVal0 == 0)
				{
					m_dbVal0 = m_dbVal1 = m_dbVal2 = 0;
					return;
				}
				m_dbVal2 = Src.m_dbVal0;
				m_dbVal1 = 255 * (m_dbVal2 - Src.m_dbVal2) / m_dbVal2;
				m_dbVal0 = g_dbThirdPI * 4 + (Src.m_dbVal2 - Src.m_dbVal1) * g_dbThirdPI / m_dbVal1;
			}
		}
	}
	else
	{
		if (Src.m_dbVal2 > Src.m_dbVal1)//2,1,0
		{
			m_dbVal2 = Src.m_dbVal2;
			m_dbVal1 = (m_dbVal2 - Src.m_dbVal0) / m_dbVal2;
			m_dbVal0 = (Src.m_dbVal1 - Src.m_dbVal0) * g_dbThirdPI / m_dbVal1;
		}
		else
		{
			if (Src.m_dbVal2 > Src.m_dbVal0)//1,2,0
			{
				m_dbVal2 = Src.m_dbVal1;
				m_dbVal1 = 255 * (m_dbVal2 - Src.m_dbVal0) / m_dbVal2;
				m_dbVal0 = g_dbPI + (Src.m_dbVal0 - Src.m_dbVal2) * g_dbThirdPI / m_dbVal1;
			}
			else//1,0,2
			{
				if (Src.m_dbVal1 == 0)
				{
					m_dbVal0 = m_dbVal1 = m_dbVal2 = 0;
					return;
				}
				m_dbVal2 = Src.m_dbVal1;
				m_dbVal1 = 255 * (m_dbVal2 - Src.m_dbVal2) / m_dbVal2;
				if (m_dbVal1 == 0)
				{
					m_dbVal0 = 0;
					return;
				}
				m_dbVal0 = g_dbPI + (Src.m_dbVal0 - Src.m_dbVal2) * g_dbThirdPI / m_dbVal1;
			}
		}
	}
}


void Raster::ZxColorBase::All2RGB()
{

}

void Raster::ZxColorBase::RGB2Lab()
{

}
void Raster::ZxColorBase::RGB2Luv()
{

}

void Raster::ZxColorBase::RGB2XYZ()
{
	ZxColorBase Src(*this);
	m_Type = ZxXYZ;
	m_dbVal0 = 0.412411 * Src.m_dbVal0 + 0.357585 * Src.m_dbVal1 + 0.180454 * Src.m_dbVal2;
	m_dbVal1 = 0.212649 * Src.m_dbVal0 + 0.715169 * Src.m_dbVal1 + 0.072182 * Src.m_dbVal2;
	m_dbVal2 = 0.019332 * Src.m_dbVal0 + 0.119195 * Src.m_dbVal1 + 0.950390 * Src.m_dbVal2;
}

double Raster::ZxColorBase::DistHSV(const ZxColorBase& _Clr1, const ZxColorBase& _Clr2)
{
	return 0;
}


double Raster::ZxColorBase::DistSquare(const ZxColorBase& _Clr1, const ZxColorBase& _Clr2)
{
	return (_Clr1.m_dbVal0 - _Clr2.m_dbVal0) * (_Clr1.m_dbVal0 - _Clr2.m_dbVal0)
		+ (_Clr1.m_dbVal1 - _Clr2.m_dbVal1) * (_Clr1.m_dbVal1 - _Clr2.m_dbVal1)
		+ (_Clr1.m_dbVal2 - _Clr2.m_dbVal2) * (_Clr1.m_dbVal2 - _Clr2.m_dbVal2);
}

// Raster::ZxDN Raster::ZxColorBase::ZxDisplayColor2DN(ZxColorDisplay& _Color)
// {
// 	ZxDN dnResult;
// 	dnResult.m_ExportInt32[0] = _Color.m_Val;
// 	dnResult.m_ExportInt32[1] = 0;
// 	return dnResult;
// }
// 
// Raster::ZxDN Raster::ZxColorBase::ZxDisplayColor2DN(ZxColorDisplay* _pColor)
// {
// 	ZxDN dnResult;
// 	dnResult.m_ExportInt32[0] = _pColor->m_Val;
// 	dnResult.m_ExportInt32[1] = 0;
// 	return dnResult;
// }