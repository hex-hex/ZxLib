#pragma once
#include "Zx2DPoint.h"
#include <vector>
using namespace std;
using namespace Geometry;
namespace Graph
{
	class ZXSTRUCT_API ZxQuadTree
	{
	private:
		struct ZxQuadNode
		{
			unsigned int m_Children[4];
			unsigned int m_pObject;
		};
		vector<ZxQuadNode> m_MainIndex;
	public:
		ZxQuadTree(void);
		~ZxQuadTree(void);
		virtual bool AddObject(unsigned int _Index, unsigned int _pObject);
		virtual unsigned int GetObject(unsigned int _Index);
		virtual bool DeleteObject(unsigned int _Index);

		static int GetIndex(const ZxInt2DPOINT& _Point);
		static int GetRightIndex(int _Index);
		static int GetLeftIndex(int _Index);
		static int GetUpperIndex(int _Index);
		static int GetLowerIndex(int _Index);
		static ZxInt2DPOINT GetRegion(int _Index);
	};
}

