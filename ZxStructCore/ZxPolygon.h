#pragma once
#include <list>
#include "Zx2DPointChain.h"
#include "ZxRectangle.h"
using namespace std;

using namespace std;
namespace Geometry
{
	typedef list<Zx2DPointChain*> Zx2DPointChainList;
	class ZxPolygon
	{
	protected:
		Zx2DPointChainList m_InteriorChain;
		Zx2DPointChain* m_pExteriorChain;
		ZxRectangle m_MiniEnclosing;
	public:
		ZxPolygon(void);
		~ZxPolygon(void);
		void MakeRectangle(void);
	};
}

