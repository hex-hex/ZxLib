#pragma once
#include "zximgbase.h"
namespace Raster
{
	struct ZxDisplayColor//用于显示的颜色
	{
		union
		{
			int		m_Val;
			unsigned char	m_Com[4];
		};
	};

	class ZxImgDsiplay :
		public ZxImgBase
	{
	public:
		ZxImgDsiplay(void);
		~ZxImgDsiplay(void);
		virtual void SetColor(ZxDisplayColor&);//仅对显示用图像起作用
		virtual void SetBlack() = 0;
		static void MakeColor(ZxDisplayColor& _color,int _r, int _g, int _b, int _a);
	};
}

