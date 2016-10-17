#pragma once
#include "ZxDisplay2D_GraphPointBase.h"
#include "ZxDisplay2D_GraphicSolidBase.h"

namespace Display2D
{
	class ZXDEVICE_API ZxDisplay2D_GraphCharacters 
		: public ZxDisplay2D_GraphPointBase
		, public ZxDisplay2D_GraphicSolidBase
	{
	protected:
		IDWriteTextFormat* m_pWriteTextFormat;
		D2D1_RECT_F m_WriteRegion;
		WCHAR* m_wcsContent;
		UINT m_nMemStrLen;
		UINT m_nStrLen;
		static IDWriteFactory* ms_pDWriteFactory;
		static unsigned int ms_RefpDWriteFactory;
	public:
		ZxDisplay2D_GraphCharacters(void);
		~ZxDisplay2D_GraphCharacters(void);
		void SetString(const char* _strContent);
		virtual void DoDraw(ID2D1RenderTarget* _pRenderTarget);
		virtual void RefreshFeature(Zx2DPoint& _Point);
	};
}

