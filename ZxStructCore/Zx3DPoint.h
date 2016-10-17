#pragma once
#include "Zx2DPoint.h"

namespace Geometry
{
	class ZXSTRUCT_API Zx3DPoint
	{
	public:
		Zx3DPoint();
		Zx3DPoint(double);
		Zx3DPoint(double, double, double);
		Zx3DPoint(Zx2DPoint&);
		struct
		{
			double m_X;
			double m_Y;
			double m_Z;
		};
		static bool Xmorethan(Zx3DPoint&,Zx3DPoint&);
		static bool pXmorethan(Zx3DPoint*,Zx3DPoint*);
		Zx3DPoint operator +(Zx3DPoint&);	
		Zx3DPoint operator -(Zx3DPoint&);
		Zx3DPoint operator *(Zx3DPoint&);
		Zx3DPoint operator /(Zx3DPoint&);
		Zx3DPoint operator *(int);
		Zx3DPoint operator /(int);
		const bool operator ==(const Zx3DPoint&);
		/*Zx3DPoint& operator=(const Zx3DPoint&);*/
		void CopyTo2D(Zx2DPoint&);
		void CopyFrom2D(Zx2DPoint&);
		Zx2DPoint Get2D();
		double GetGeoMean() const;
		static void AffineTrans(Zx3DPoint&,const double*);//确保double指向是6元数组
	};
}

