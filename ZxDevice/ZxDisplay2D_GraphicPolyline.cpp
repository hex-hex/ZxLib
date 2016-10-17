#include "StdAfx.h"
#include "ZxDisplay2D_GraphicPolyline.h"


Display2D::ZxDisplay2D_GraphicPolyline::ZxDisplay2D_GraphicPolyline(void)
{
	m_Type = ZXDISPLAY2D_GRAPH_LINE;
}


Display2D::ZxDisplay2D_GraphicPolyline::~ZxDisplay2D_GraphicPolyline(void)
{
}

void Display2D::ZxDisplay2D_GraphicPolyline::DoDraw(ID2D1RenderTarget* _pRenderTarget)
{

}

void Display2D::ZxDisplay2D_GraphicPolyline::Zoom(float _Scale)
{
	m_strokeShowWidth = m_strokeWidth / _Scale;
}
