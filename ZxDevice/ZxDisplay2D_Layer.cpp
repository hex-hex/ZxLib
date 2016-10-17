#include "StdAfx.h"
#include "ZxDisplay2D_Layer.h"


Display2D::ZxDisplay2D_DisplayObject::ZxDisplay2D_DisplayObject()
	:m_bDraw(false)
{

}

Display2D::ZxDisplay2D_DisplayObject::~ZxDisplay2D_DisplayObject()
{

}

void Display2D::ZxDisplay2D_DisplayObject::SetDraw(bool _bDraw/* = true*/)
{
	m_bDraw = _bDraw;
}


Display2D::ZxDisplay2D_Layer::ZxDisplay2D_Layer(void)
	:m_bShow(true)
{
}


Display2D::ZxDisplay2D_Layer::~ZxDisplay2D_Layer(void)
{
}

void Display2D::ZxDisplay2D_Layer::MoveBy(float _x, float _y)
{
	m_matDisplayTransform._31 -= _x;
	m_matDisplayTransform._32 -= _y;
}

void Display2D::ZxDisplay2D_Layer::SetGraphicTransform(D2D1::Matrix3x2F& _matTranform)
{
	m_matDisplayTransform = _matTranform;
}

float* Display2D::ZxDisplay2D_Layer::GetTransformPara(int _ij)
{
	switch(_ij)
	{
	case 11:
		return &m_matDisplayTransform._11;
	case 12:
		return &m_matDisplayTransform._12;
	case 21:
		return &m_matDisplayTransform._21;
	case 22:
		return &m_matDisplayTransform._22;
	case 31:
		return &m_matDisplayTransform._31;
	case 32:
		return &m_matDisplayTransform._32;
	default:
		return NULL;
	}
}


void Display2D::ZxDisplay2D_Layer::SetShow(bool _bShow)
{
	m_bShow = _bShow;
}


bool Display2D::ZxDisplay2D_Layer::DoDraw(ID2D1RenderTarget* _pRenderTarget)
{
	if (!m_bShow)
		return false;
	if (!(_pRenderTarget))
		return false;
	_pRenderTarget->SetTransform(m_matDisplayTransform);
	return true;
}

