#pragma once
#include "ZxDisplay2D_Layer.h"
#include "ZxDisplay2D_GraphicBrushMaker.h"

#define ZXDISPLAY2D_GRAPH_UNKNOW	0
#define ZXDISPLAY2D_GRAPH_POINT		1
#define ZXDISPLAY2D_GRAPH_LINE		2
#define ZXDISPLAY2D_GRAPH_POLOGON	4

namespace Display2D
{
	class ZXDEVICE_API ZxDisplay2D_GraphBase
		:public ZxDisplay2D_DisplayObject
	{
	protected:
		int  m_Type;
	public:
		ZxDisplay2D_GraphBase(void);
		~ZxDisplay2D_GraphBase(void);
		int GetType();
		virtual void Zoom(float _Scale) = 0;
		virtual void DoDraw(ID2D1RenderTarget* _pRenderTarget) = 0;
	};
}