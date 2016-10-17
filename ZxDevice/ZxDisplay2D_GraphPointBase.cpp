#include "StdAfx.h"
#include "ZxDisplay2D_GraphPointBase.h"


Display2D::ZxDisplay2D_GraphPointBase::ZxDisplay2D_GraphPointBase(void)
{
	m_Type = ZXDISPLAY2D_GRAPH_POINT;
}


Display2D::ZxDisplay2D_GraphPointBase::~ZxDisplay2D_GraphPointBase(void)
{
}

void Display2D::ZxDisplay2D_GraphPointBase::Zoom(float _Scale)
{
	m_Location = m_LocationOrigin * _Scale;
	RefreshFeature(m_Location);
}

void Display2D::ZxDisplay2D_GraphPointBase::SetPoint(Zx2DPoint& _Point)
{
	m_LocationOrigin = _Point;
	m_bDraw = false;
}

Zx2DPoint Display2D::ZxDisplay2D_GraphPointBase::GetOriginPoint()
{
	return m_LocationOrigin;
}