#pragma once
#include "ZxDisplay2D_GraphBase.h"
namespace Display2D
{
	class ZXDEVICE_API ZxDisplay2D_GraphPointBase	//表明其本身不受比例尺影响
		:public ZxDisplay2D_GraphBase
	{
	protected:
		Zx2DPoint m_LocationOrigin;
		Zx2DPoint m_Location;
	public:
		ZxDisplay2D_GraphPointBase(void);
		~ZxDisplay2D_GraphPointBase(void);
		void Zoom(float _Scale);
		virtual void SetPoint(Zx2DPoint& _Point);//只定位，不更新图例
		Zx2DPoint GetOriginPoint();
		virtual void RefreshFeature(Zx2DPoint& _Point) = 0;//必须要refresh一下才能显示，函数内指明图例的绘制方法
	};
}


