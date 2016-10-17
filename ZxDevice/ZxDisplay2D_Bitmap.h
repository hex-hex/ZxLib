#pragma once
#include "ZxDisplay2D_Layer.h"

namespace Display2D
{
	class ZXDEVICE_API ZxDisplay2D_Bitmap
		:public ZxDisplay2D_DisplayObject
	{
	protected:
		D2D1_BITMAP_PROPERTIES m_BitmapProperties;
		D2D1_RECT_F* m_pScrRect;
		D2D1_RECT_F* m_pDstRect;
		D2D1_SIZE_U m_BitmapSize;
		ID2D1Bitmap *m_pBitmap;
	public:
		ZxDisplay2D_Bitmap(void);
		~ZxDisplay2D_Bitmap(void);
		D2D1_POINT_2F GetOrigin() const;
		bool SetDPI(ID2D1Factory* _pFactoty);
		void SetDstPoint(float _x,float _y);
		void SetRscRect(float _x, float _y, float _width, float _height);
		void SetDstRect(float _x, float _y, float _width, float _height);
		bool CreatBitmap(ID2D1RenderTarget* _RenderTarget, ZxImgBase* _pImage);
		void SetAlphaMode(D2D1_ALPHA_MODE _Mode = D2D1_ALPHA_MODE_IGNORE);
		void SetPixelFormat(DXGI_FORMAT _PixelFormat);
		bool DoDraw(ID2D1RenderTarget* _pRenderTarget,
			D2D1_BITMAP_INTERPOLATION_MODE _modeInterpolation);
		void Clear();
	};
}
