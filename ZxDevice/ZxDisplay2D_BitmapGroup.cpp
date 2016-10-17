#include "StdAfx.h"
#include "ZxDisplay2D_BitmapGroup.h"


Display2D::ZxDisplay2D_BitmapGroup::ZxDisplay2D_BitmapGroup(void)
{
	Clear();
	m_ModeInterpolation = D2D1_BITMAP_INTERPOLATION_MODE_LINEAR;
}


Display2D::ZxDisplay2D_BitmapGroup::~ZxDisplay2D_BitmapGroup(void)
{
	Clear();
}


void Display2D::ZxDisplay2D_BitmapGroup::Clear()
{
	for (ZxDisplay2D_Bitmap_List::iterator pBitmap = m_BitmapList.begin();
		pBitmap != m_BitmapList.end(); pBitmap++)
	{
		delete (*pBitmap);
	}
	m_BitmapList.clear();
	m_matDisplayTransform = D2D1::Matrix3x2F::Identity();
}


bool Display2D::ZxDisplay2D_BitmapGroup::DoDraw(ID2D1RenderTarget* _pRenderTarget)
{
	if (!ZxDisplay2D_Layer::DoDraw(_pRenderTarget))
		return false;
	for (ZxDisplay2D_Bitmap_List::iterator pBitmap = m_BitmapList.begin();
		pBitmap != m_BitmapList.end(); pBitmap++)
	{
		(*pBitmap)->DoDraw(_pRenderTarget,m_ModeInterpolation);
	}
	return true;
}


HRESULT Display2D::ZxDisplay2D_BitmapGroup::AddBitmap(
	ID2D1Factory* _ptrFactoty, ID2D1RenderTarget* _pRenderTarget,
	ZxImgBase* _pImage, DXGI_FORMAT _PixelFormat,D2D1_ALPHA_MODE _Mode, bool _bDraw)
{
	ZxDisplay2D_Bitmap* pBitmap = new ZxDisplay2D_Bitmap;
	pBitmap->SetPixelFormat(_PixelFormat);
	pBitmap->SetAlphaMode(_Mode);
	pBitmap->SetDPI(_ptrFactoty);
	pBitmap->CreatBitmap(_pRenderTarget,_pImage);
	pBitmap->SetDraw(_bDraw);
	m_BitmapList.push_back(pBitmap);
	return S_OK;
}


D2D1_POINT_2F Display2D::ZxDisplay2D_BitmapGroup::GetOrigin()
{
	D2D1_POINT_2F point;
	point.x = m_matDisplayTransform._31;
	point.y = m_matDisplayTransform._32;
	return point;
}


Display2D::ZxDisplay2D_Bitmap* Display2D::ZxDisplay2D_BitmapGroup::GetBitmap(int _Index)
{
	if (_Index < 0)
	{
		return m_BitmapList.at(m_BitmapList.size() - 1);
	}
	else if (_Index < m_BitmapList.size())
	{
		return m_BitmapList.at(_Index);
	}
	else
		return NULL;
}

void Display2D::ZxDisplay2D_BitmapGroup::SetInterpolationMode(D2D1_BITMAP_INTERPOLATION_MODE _mode)
{
	m_ModeInterpolation = _mode;
}


int Display2D::ZxDisplay2D_BitmapGroup::GetLastBitmapID(void)
{
	return m_BitmapList.size() - 1;
}


void Display2D::ZxDisplay2D_BitmapGroup::Zoom(float _Scale)
{
	m_matDisplayTransform._11 = _Scale;
	m_matDisplayTransform._22 = _Scale;
}
