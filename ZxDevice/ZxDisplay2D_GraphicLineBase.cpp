#include "StdAfx.h"
#include "ZxDisplay2D_GraphicLineBase.h"


Display2D::ZxDisplay2D_GraphicLineBase::ZxDisplay2D_GraphicLineBase(void)
	:m_pStyle(NULL)
	,m_pLineBrush(NULL)
	,m_strokeWidth(1.0)
	,m_strokeShowWidth(1.0)
	,m_bManagedBrush(true)
	,m_bManagedStyle(true)
{
}


Display2D::ZxDisplay2D_GraphicLineBase::~ZxDisplay2D_GraphicLineBase(void)
{
	if(m_bManagedBrush)
		SAFE_RELEASE(m_pLineBrush);
	if (m_bManagedStyle)
		SAFE_RELEASE(m_pStyle);
}

void Display2D::ZxDisplay2D_GraphicLineBase::SetStrokeWidth(float _strokeWidth)
{
	m_strokeWidth = _strokeWidth;
	m_strokeShowWidth = _strokeWidth;
}


bool Display2D::ZxDisplay2D_GraphicLineBase::SetLineBrush(ID2D1Brush* _pBrush, bool _bManaged/* = false*/)
{
	if (_pBrush != NULL)
	{
		if (m_bManagedBrush)
			SAFE_RELEASE(m_pLineBrush);
		m_pLineBrush = _pBrush;
		m_bManagedBrush = _bManaged;
		return true;
	}
	else
		return false;
}
