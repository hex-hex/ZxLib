#pragma once
#include "ZxDisplay2D_Layer.h"
#include "ZxDisplay2D_Bitmap.h"

#include <vector>
using namespace std;

namespace Display2D
{
	typedef vector<ZxDisplay2D_Bitmap*> ZxDisplay2D_Bitmap_List;
	class ZXDEVICE_API ZxDisplay2D_BitmapGroup
		: public ZxDisplay2D_Layer
	{
	protected:
		ZxDisplay2D_Bitmap_List m_BitmapList;
		D2D1_BITMAP_INTERPOLATION_MODE m_ModeInterpolation;
	public:
		ZxDisplay2D_BitmapGroup(void);
		virtual ~ZxDisplay2D_BitmapGroup(void);
		void Clear();
		virtual bool DoDraw(ID2D1RenderTarget* _pRenderTarget);
		virtual HRESULT AddBitmap(ID2D1Factory* _ptrFactoty, ID2D1RenderTarget* _pRenderTarget,
			ZxImgBase* _pImage, DXGI_FORMAT _PixelFormat,D2D1_ALPHA_MODE _Mode,bool _bDraw);
		ZxDisplay2D_Bitmap* GetBitmap(int _Index);
		D2D1_POINT_2F GetOrigin();
		void SetInterpolationMode(D2D1_BITMAP_INTERPOLATION_MODE);
		int GetLastBitmapID(void);
		void Zoom(float _Scale);
	};
}

