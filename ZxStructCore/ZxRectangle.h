#pragma once
#include "Zx2DPoint.h"
#define ZXRECT_INTASFLOAT(x) *(((float*)(&x)))
namespace Geometry
{
	class ZxIntImgRECT;
	class ZXSTRUCT_API ZxIntRECT
	{
	public:
		struct
		{
			int m_Left;
			int m_Top;
			int m_Width;
			int m_Height;
			float m_Angle;
		};
		ZxIntRECT();
		ZxIntRECT(int _Left, int _Top, int _Width, int _Height, float _Angle = 0);
		operator ZxIntImgRECT();
		bool IsInside(int _x, int _y);
		static void SetOff(const ZxInt2DPOINT&, ZxIntRECT);
		static ZxIntRECT QuickGetMinRect(const ZxInt2DPoints& _PointSet);//左右界表示矩形中心，上下界表示宽和高;
	};

	class ZXSTRUCT_API ZxIntImgRECT
	{
	public:
		int m_Left;
		int m_Top;
		int m_Right;
		int m_Bottom;
		ZxIntImgRECT();
		operator ZxIntRECT();
	};

	class ZXSTRUCT_API ZxRectangle//需保持最简单结构
	{
	public:
		double m_Left;
		double m_Right;
		double m_Top;
		double m_Bottom;
		ZxRectangle(void);
		ZxRectangle(double _Left, double _Top, double _Right, double _Bottom);
		~ZxRectangle(void);

	};
}
