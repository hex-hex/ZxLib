#include "StdAfx.h"
#include "ZxDisplay2D_GraphicBrushMaker.h"


Display2D::ZxDisplay2D_GraphicBrushMaker::ZxDisplay2D_GraphicBrushMaker(void)
{
}


Display2D::ZxDisplay2D_GraphicBrushMaker::~ZxDisplay2D_GraphicBrushMaker(void)
{
}

UINT Display2D::ZxDisplay2D_GraphicBrushMaker::MakeColor(BYTE _r,BYTE _g, BYTE _b, BYTE _a/* = 255*/)
{
	UINT ColorU(0);
	ColorU |= _a;
	ColorU <<= 8;
	ColorU |= _r;
	ColorU <<= 8;
	ColorU |= _g;
	ColorU <<= 8;
	ColorU |= _b;
	return ColorU;
}

ID2D1SolidColorBrush* Display2D::ZxDisplay2D_GraphicBrushMaker::CreateSolidColorBrush(ID2D1RenderTarget* _pRenderTarget,
	UINT _rgb, float _Opacity)
{
	ID2D1SolidColorBrush* pBrush;
	_pRenderTarget->CreateSolidColorBrush(
		D2D1::ColorF(_rgb,_Opacity),&pBrush);
	return pBrush;
}
