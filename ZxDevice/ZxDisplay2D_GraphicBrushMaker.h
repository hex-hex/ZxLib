#pragma once
namespace Display2D
{
	class ZXDEVICE_API ZxDisplay2D_GraphicBrushMaker
	{
	protected:
		ID2D1RenderTarget* m_pRenderTarget;
	public:
		ZxDisplay2D_GraphicBrushMaker(void);
		~ZxDisplay2D_GraphicBrushMaker(void);
		static UINT MakeColor(BYTE _r,BYTE _g, BYTE _b, BYTE _a = 255);
		static ID2D1SolidColorBrush* CreateSolidColorBrush(	ID2D1RenderTarget* _pRenderTarget,
			UINT _rgb, float _Opacity = 1.0);
	};
}
