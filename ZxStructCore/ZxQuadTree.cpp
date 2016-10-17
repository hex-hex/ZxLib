#include "StdAfx.h"
#include "ZxQuadTree.h"


Graph::ZxQuadTree::ZxQuadTree(void)
{
	ZxQuadNode nodeHead;
	memset(nodeHead.m_Children,0,sizeof(unsigned int) * 4);
	nodeHead.m_pObject = NULL;
	m_MainIndex.push_back(nodeHead);
}


Graph::ZxQuadTree::~ZxQuadTree(void)
{
}


bool Graph::ZxQuadTree::AddObject(unsigned int _Index, unsigned int _pObject)
{
	return false;
}

unsigned int Graph::ZxQuadTree::GetObject(unsigned int _Index)
{
	return NULL;
}

bool Graph::ZxQuadTree::DeleteObject(unsigned int _Index)
{
	return false;
}



int Graph::ZxQuadTree::GetIndex(const ZxInt2DPOINT& _Point)
{
	ZxInt2DPOINT tmpPoint(_Point);
	unsigned int PixelIndex(0);
	for(unsigned int i = 0x80000000; i != 0; i >>= 1)
	{
		PixelIndex <<= 1;
		PixelIndex |= tmpPoint.m_Y / i;
		tmpPoint.m_Y %= i;

		PixelIndex <<= 1;
		PixelIndex |= tmpPoint.m_X / i;
		tmpPoint.m_X %= i;
	}
	return PixelIndex;
}


ZxInt2DPOINT Graph::ZxQuadTree::GetRegion(int _Index)
{
	ZxInt2DPOINT point;
	point.m_X = point.m_Y = 0;
	for (int i = 0; _Index != 0; _Index >>= 2, i++)
	{
		if (_Index & 1)
		{
			point.m_X += 1 << i;
		}
		if (_Index & 2)
		{
			point.m_Y += 1 << i;
		}
	}
	return point;
}

int Graph::ZxQuadTree::GetRightIndex(int _Index)
{
	for(unsigned int i = 1; i != 0x40000000; i <<= 2)
	{
		if (_Index & i)
		{
			_Index &= ~i;
		}
		else
		{
			_Index |= i;
			return _Index;
		}
	}
	return -1;
}

int Graph::ZxQuadTree::GetLeftIndex(int _Index)
{
	for(unsigned int i = 1; i != 0x40000000; i <<= 2)
	{
		if (_Index & i)
		{
			_Index &= ~i;
			return _Index;
		}
		else
		{
			_Index |= i;
		}
	}
	return -1;
}

int Graph::ZxQuadTree::GetUpperIndex(int _Index)
{
	for(unsigned int i = 2; i != 0x80000000; i <<= 2)
	{
		if (_Index & i)
		{
			_Index &= ~i;
			return _Index;
		}
		else
		{
			_Index |= i;
		}
	}
	return -1;
}

int Graph::ZxQuadTree::GetLowerIndex(int _Index)
{
	for(unsigned int i = 2; i != 0x80000000; i <<= 2)
	{
		if (_Index & i)
		{
			_Index &= ~i;
		}
		else
		{
			_Index |= i;
			return _Index;
		}
	}
	return -1;
}