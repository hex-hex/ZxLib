#include "StdAfx.h"
#include "ZxDisplay2D_GraphicSolidBase.h"


Display2D::ZxDisplay2D_GraphicSolidBase::ZxDisplay2D_GraphicSolidBase(void)
	:m_pFillBrush(NULL)
	,m_bManagedBrush(true)
{
}


Display2D::ZxDisplay2D_GraphicSolidBase::~ZxDisplay2D_GraphicSolidBase(void)
{
	if(m_bManagedBrush)
		SAFE_RELEASE(m_pFillBrush);
}

bool Display2D::ZxDisplay2D_GraphicSolidBase::SetFillBrush(ID2D1Brush* _pBrush, bool _bManaged/* = false*/)
{
	if (_pBrush != NULL)
	{
		if (m_bManagedBrush)
			SAFE_RELEASE(m_pFillBrush);
		m_pFillBrush = _pBrush;
		m_bManagedBrush = _bManaged;
		return true;
	}
	else
		return false;
}