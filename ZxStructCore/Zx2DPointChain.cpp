#include "StdAfx.h"
#include "Zx2DPointChain.h"


Geometry::Zx2DPointChain::Zx2DPointChain(void)
{
}


Geometry::Zx2DPointChain::~Zx2DPointChain(void)
{
	m_PontList.clear();
}


bool Geometry::Zx2DPointChain::MakeClose(void)
{
	if (m_PontList.size() < 3)
	{
		return false;
	}
	else if (*(--m_PontList.end()) == *m_PontList.begin())
	{
		return false;
	}
	else
	{
		m_PontList.push_back(*m_PontList.begin());
		return true;
	}
}


int Geometry::Zx2DPointChain::GetCount(void) const
{
	return m_PontList.size();
}


void Geometry::Zx2DPointChain::ResetIterator(void)
{
	m_iPoint = m_PontList.begin();
}


bool Geometry::Zx2DPointChain::HasNext(void)
{
	return m_iPoint != m_PontList.end();
}


Geometry::Zx2DPoint& Geometry::Zx2DPointChain::Next(void)
{
	return *(m_iPoint++);
}


void Geometry::Zx2DPointChain::AddPoint(const Zx2DPoint& _Point)
{
	m_PontList.push_back(_Point);
}
