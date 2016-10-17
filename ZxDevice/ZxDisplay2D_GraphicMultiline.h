#pragma once
#include <list>
using namespace std;
#include "ZxDisplay2D_GraphBase.h"
#include "zxdisplay2d_graphiclinebase.h"
namespace Display2D
{
	struct ZxDisplay2D_SimpleLine
	{
		D2D1_POINT_2F m_Header;
		D2D1_POINT_2F m_Tail;
	};

	class ZXDEVICE_API ZxDisplay2D_GraphicMultiline
		:public ZxDisplay2D_GraphBase
		,public ZxDisplay2D_GraphicLineBase
	{
	protected: 
		list<ZxDisplay2D_SimpleLine> m_LineList;
	public:
		ZxDisplay2D_GraphicMultiline(void);
		~ZxDisplay2D_GraphicMultiline(void);
		void AddLine(ZxDisplay2D_SimpleLine _Line);
		virtual void DoDraw(ID2D1RenderTarget* _pRenderTarget);
		virtual void Zoom(float _Scale);
	};
}

