#include "StdAfx.h"
#include "ZxDisplay2D_GraphRectangle.h"


Display2D::ZxDisplay2D_GraphRectangle::ZxDisplay2D_GraphRectangle(void)
{
	m_Type = ZXDISPLAY2D_GRAPH_POLOGON;
}


Display2D::ZxDisplay2D_GraphRectangle::~ZxDisplay2D_GraphRectangle(void)
{
}



bool Display2D::ZxDisplay2D_GraphRectangle::IsPointInRect(POINT _point, RECT _rect)
{
	if (_point.x < _rect.right &&
		_point.y < _rect.bottom &&
		_point.x > _rect.left &&
		_point.y > _rect.top)
	{
		return true;
	}
	else
		return false;
}

void Display2D::ZxDisplay2D_GraphRectangle::SetFill(bool _bFill)
{
	m_bFill = _bFill;
}


void Display2D::ZxDisplay2D_GraphRectangle::DoDraw(ID2D1RenderTarget* _pRenderTarget)
{
	if (m_bFill)
	{
		_pRenderTarget->FillRectangle(m_Rect,m_pFillBrush);
	}
	if (m_bDraw)
	{
		_pRenderTarget->DrawRectangle(m_Rect,m_pLineBrush,m_strokeShowWidth,m_pStyle);
	}
}


void Display2D::ZxDisplay2D_GraphRectangle::SetRect(float _left, float _right, float _top, float _bottom)
{
	m_Rect.left = _left;
	m_Rect.top = _top;
	m_Rect.bottom = _bottom;
	m_Rect.right = _right;
}

void Display2D::ZxDisplay2D_GraphRectangle::Zoom(float _Scale)
{
	m_strokeShowWidth = m_strokeWidth / _Scale;
}