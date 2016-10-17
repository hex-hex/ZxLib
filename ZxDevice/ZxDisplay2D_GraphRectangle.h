#pragma once
#include "ZxDisplay2D_GraphBase.h"
#include "ZxDisplay2D_GraphicLineBase.h"
#include "ZxDisplay2D_GraphicSolidBase.h"

namespace Display2D
{
	class ZXDEVICE_API ZxDisplay2D_GraphRectangle 
		:public ZxDisplay2D_GraphBase
		,public ZxDisplay2D_GraphicLineBase
		,public ZxDisplay2D_GraphicSolidBase
	{
	protected:
		D2D1_RECT_F m_Rect;
		bool m_bFill;
	public:
		ZxDisplay2D_GraphRectangle(void);
		~ZxDisplay2D_GraphRectangle(void);
		virtual void DoDraw(ID2D1RenderTarget* _pRenderTarget);
		virtual void Zoom(float _Scale);
		void SetRect(float _left, float _right, float _top, float _bottom);
		void SetFill(bool);
		static bool IsPointInRect(POINT _point, RECT _rect);
	};
}

