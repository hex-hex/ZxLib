#pragma once
#include "Zx2DPoint.h"
#include <list>
using namespace std;
namespace Geometry
{
	typedef list<Zx2DPoint> Zx2DPointList;
	class Zx2DPointChain
	{
	protected:
		Zx2DPointList::iterator m_iPoint;
		Zx2DPointList m_PontList;
	public:
		Zx2DPointChain(void);
		~Zx2DPointChain(void);
		void ResetIterator(void);
		bool HasNext(void);
		Zx2DPoint& Next(void);
		bool MakeClose(void);
		int GetCount(void) const;
		void AddPoint(const Zx2DPoint& _Point);
	};
}

