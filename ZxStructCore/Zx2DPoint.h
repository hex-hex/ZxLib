#pragma once
#include <vector>

namespace Geometry
{
	struct ZxInt2DPOINT
	{
		int m_X;
		int m_Y;
	};

	typedef std::vector<ZxInt2DPOINT> ZxInt2DPoints;

	struct ZxImg2DPOINT
	{
		unsigned short m_X;
		unsigned short m_Y;
	};

	class ZXSTRUCT_API Zx2DPoint
	{
	public:
		Zx2DPoint();
		Zx2DPoint(double);
		Zx2DPoint(double, double);
		struct
		{
			double m_X;
			double m_Y;
		};
		Zx2DPoint operator +(Zx2DPoint&);	
		Zx2DPoint& operator +=(const Zx2DPoint&);
		Zx2DPoint& operator +=(const ZxInt2DPOINT&);
		Zx2DPoint operator -(Zx2DPoint&);
		Zx2DPoint operator *(Zx2DPoint&);
		Zx2DPoint operator /(Zx2DPoint&);
		Zx2DPoint operator *(double);
		Zx2DPoint operator *(int);
		Zx2DPoint operator /(int);
		bool operator ==(const Zx2DPoint&);
		/*Zx2DPoint& operator=(const Zx2DPoint&);*/
		double GetGeoMean() const;
		double GetDistance(Zx2DPoint&);
		static void AffineTrans(Zx2DPoint&, const double*);//确保double指向是6元数组
	};

}
