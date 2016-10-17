#pragma once
#include "ZxDisplay2D_GraphBase.h"
namespace Display2D
{
	class ZXDEVICE_API ZxDisplay2D_GraphPointBase	//�����䱾���ܱ�����Ӱ��
		:public ZxDisplay2D_GraphBase
	{
	protected:
		Zx2DPoint m_LocationOrigin;
		Zx2DPoint m_Location;
	public:
		ZxDisplay2D_GraphPointBase(void);
		~ZxDisplay2D_GraphPointBase(void);
		void Zoom(float _Scale);
		virtual void SetPoint(Zx2DPoint& _Point);//ֻ��λ��������ͼ��
		Zx2DPoint GetOriginPoint();
		virtual void RefreshFeature(Zx2DPoint& _Point) = 0;//����Ҫrefreshһ�²�����ʾ��������ָ��ͼ���Ļ��Ʒ���
	};
}


