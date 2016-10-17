#pragma once
#include "zximgbase.h"
namespace Raster
{
	struct ZxDisplayColor//������ʾ����ɫ
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
		virtual void SetColor(ZxDisplayColor&);//������ʾ��ͼ��������
		virtual void SetBlack() = 0;
		static void MakeColor(ZxDisplayColor& _color,int _r, int _g, int _b, int _a);
	};
}

