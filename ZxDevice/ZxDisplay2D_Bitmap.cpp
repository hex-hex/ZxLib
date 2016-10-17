#include "StdAfx.h"
#include "ZxDisplay2D_Bitmap.h"


Display2D::ZxDisplay2D_Bitmap::ZxDisplay2D_Bitmap(void)
	: m_pBitmap(NULL)
	, m_pScrRect(new D2D1_RECT_F)
	, m_pDstRect(new D2D1_RECT_F)
{
	m_pDstRect->left = m_pDstRect->right = 0;
	m_pDstRect->top = m_pDstRect->bottom = 0;
	m_pScrRect->left = m_pScrRect->right = 0;
	m_pScrRect->top = m_pScrRect->bottom = 0;
	m_BitmapSize.height = m_BitmapSize.width = 0;
}


Display2D::ZxDisplay2D_Bitmap::~ZxDisplay2D_Bitmap(void)
{
	Clear();
	if (m_pDstRect != NULL)
		delete[] m_pDstRect;
	if (m_pScrRect != NULL)
		delete[] m_pScrRect;
}


void Display2D::ZxDisplay2D_Bitmap::Clear()
{
	m_bDraw = false;
	SAFE_RELEASE(m_pBitmap);
}

D2D1_POINT_2F Display2D::ZxDisplay2D_Bitmap::GetOrigin() const
{
	D2D1_POINT_2F point;
	point.x = m_pDstRect->left;
	point.y = m_pDstRect->top;
	return point;
}

bool Display2D::ZxDisplay2D_Bitmap::SetDPI(ID2D1Factory* _pFactoty)
{
	if(!_pFactoty)
		return false;
	_pFactoty->GetDesktopDpi(&(m_BitmapProperties.dpiX),&(m_BitmapProperties.dpiY));
	return true;
}

bool Display2D::ZxDisplay2D_Bitmap::CreatBitmap(ID2D1RenderTarget* _RenderTarget,ZxImgBase* _pImage)
{
	if ((!_RenderTarget)||(!_pImage->GetImgData()))
	{
		return false;
	}
	if (m_BitmapSize.width == _pImage->GetWidth() &&
		m_BitmapSize.height == _pImage->GetHeight()
		)
	{
		if (m_pBitmap->CopyFromMemory(&(D2D1::RectU(0,0,_pImage->GetWidth(),_pImage->GetHeight())),
			_pImage->GetImgData(),_pImage->GetWidthStep()))
		{
			return false;
		}
	}
	else
	{
		SAFE_RELEASE(m_pBitmap);
		m_BitmapSize.width = _pImage->GetWidth();
		m_BitmapSize.height = _pImage->GetHeight();
		if(_RenderTarget->CreateBitmap(m_BitmapSize,_pImage->GetImgData(),_pImage->GetWidthStep(),m_BitmapProperties,&m_pBitmap) != S_OK)
		{
			return false;
		}
		*m_pDstRect = 
			*m_pScrRect = D2D1::RectF(0,0,m_BitmapSize.width,m_BitmapSize.height);
	}
	_pImage->DetachManagement();
	return true;

}


void Display2D::ZxDisplay2D_Bitmap::SetAlphaMode(D2D1_ALPHA_MODE _Mode)
{
	m_BitmapProperties.pixelFormat.alphaMode = _Mode;
}


void Display2D::ZxDisplay2D_Bitmap::SetPixelFormat(DXGI_FORMAT _PixelFormat)
{
	m_BitmapProperties.pixelFormat.format = _PixelFormat;
}


bool Display2D::ZxDisplay2D_Bitmap::DoDraw(ID2D1RenderTarget* _pRenderTarget,D2D1_BITMAP_INTERPOLATION_MODE _modeInterpolation)
{
	if (!(m_bDraw))
		return false;
	_pRenderTarget->DrawBitmap(
		m_pBitmap,
		m_pDstRect,
		1.0F,
		_modeInterpolation,
		m_pScrRect
		);
	return true;
}


void Display2D::ZxDisplay2D_Bitmap::SetDstPoint(float _x,float _y)
{
	m_pDstRect->left = _x;
	m_pDstRect->top = _y;
	m_pDstRect->right = _x + m_BitmapSize.width;
	m_pDstRect->bottom = _y + m_BitmapSize.height;
}


void Display2D::ZxDisplay2D_Bitmap::SetDstRect(float _x, float _y, float _width, float _height)
{
	m_pDstRect->left = _x;
	m_pDstRect->right = _x + _width;
	m_pDstRect->top = _y;
	m_pDstRect->bottom = _y + _height;
	SetDraw(true);
}

void Display2D::ZxDisplay2D_Bitmap::SetRscRect(float _x, float _y, float _width, float _height)
{
	m_pScrRect->left = _x;
	m_pScrRect->right = _x + _width;
	m_pScrRect->top = _y;
	m_pScrRect->bottom = _y + _height;
	SetDraw(true);
}