#include "StdAfx.h"
#include "ZxDisplay2D_GraphicMultiline.h"


Display2D::ZxDisplay2D_GraphicMultiline::ZxDisplay2D_GraphicMultiline(void)
{
	m_Type = ZXDISPLAY2D_GRAPH_LINE;
}


Display2D::ZxDisplay2D_GraphicMultiline::~ZxDisplay2D_GraphicMultiline(void)
{
}

void Display2D::ZxDisplay2D_GraphicMultiline::DoDraw(ID2D1RenderTarget* _pRenderTarget)
{
	if(m_bDraw)
	{
		for (list<ZxDisplay2D_SimpleLine>::iterator pLine = m_LineList.begin();
			pLine != m_LineList.end(); pLine++)
		{
			_pRenderTarget->DrawLine(pLine->m_Header,pLine->m_Tail,m_pLineBrush,m_strokeShowWidth,m_pStyle);
		}
	}
}


void Display2D::ZxDisplay2D_GraphicMultiline::Zoom(float _Scale)
{
	m_strokeShowWidth = m_strokeWidth / _Scale;
}


void Display2D::ZxDisplay2D_GraphicMultiline::AddLine(ZxDisplay2D_SimpleLine _Line)
{
	m_LineList.push_back(_Line);
}       