#pragma once
#include <list>
using namespace std;
#include "ZxDisplay2D_GraphBase.h"
#include "zxdisplay2d_graphiclinebase.h"
namespace Display2D
{
	class ZXDEVICE_API ZxDisplay2D_GraphicPolyline 
		: public ZxDisplay2D_GraphBase
		, public ZxDisplay2D_GraphicLineBase
	{
	protected:
		list<D2D1_POINT_2F> m_PointList;
	public:
		ZxDisplay2D_GraphicPolyline(void);
		~ZxDisplay2D_GraphicPolyline(void);
		virtual void DoDraw(ID2D1RenderTarget* _pRenderTarget);
		virtual void Zoom(float _Scale);
	};
}

