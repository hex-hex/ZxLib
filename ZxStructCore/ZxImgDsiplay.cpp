#include "StdAfx.h"
#include "ZxImgDsiplay.h"


Raster::ZxImgDsiplay::ZxImgDsiplay(void)
{
}


Raster::ZxImgDsiplay::~ZxImgDsiplay(void)
{
}

void Raster::ZxImgDsiplay::SetColor(ZxDisplayColor& _Color)
{
	int nChannel = GetDepth()/8;
	for (int i = 0; i < GetHeight();i++)
	{
		for(int j = 0; j < GetWidth(); j++)
		{
			memcpy(GetImgData() + i * GetWidthStep() + j * nChannel ,&_Color,nChannel);
		}
	}
}

void Raster::ZxImgDsiplay::MakeColor(ZxDisplayColor& _color,int _r, int _g, int _b, int _a)
{
	_color.m_Val = (_b << 24) | (_g << 16) | (_r << 8) | _b;
}

