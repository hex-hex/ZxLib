#include "StdAfx.h"
#include "ZxPolygon.h"


Geometry::ZxPolygon::ZxPolygon(void)
	:m_pExteriorChain(NULL)
{
	m_InteriorChain.clear();
}


Geometry::ZxPolygon::~ZxPolygon(void)
{
	if (m_pExteriorChain != NULL)
	{
		delete m_pExteriorChain;
	}
	for (Zx2DPointChainList::iterator iChain = m_InteriorChain.begin();
		iChain != m_InteriorChain.end(); iChain++)
	{
		delete *iChain;
	}
	m_InteriorChain.clear();
}


void Geometry::ZxPolygon::MakeRectangle(void)
{
	if (m_pExteriorChain->GetCount() == 0)
		return;
	Zx2DPoint* pPoint = &(m_pExteriorChain->Next());
	m_pExteriorChain->ResetIterator();
	m_MiniEnclosing.m_Bottom = 
		m_MiniEnclosing.m_Top = pPoint->m_Y;
	m_MiniEnclosing.m_Left =
		m_MiniEnclosing.m_Right = pPoint->m_X;
	while (m_pExteriorChain->HasNext())
	{
		pPoint = &(m_pExteriorChain->Next());
		if (m_MiniEnclosing.m_Left > pPoint->m_X)
			m_MiniEnclosing.m_Left = pPoint->m_X;
		if(m_MiniEnclosing.m_Right < pPoint->m_X)
			m_MiniEnclosing.m_Right = pPoint->m_X;
		if(m_MiniEnclosing.m_Top > pPoint->m_Y)
			m_MiniEnclosing.m_Top = pPoint->m_Y;
		if(m_MiniEnclosing.m_Bottom < pPoint->m_Y)
			m_MiniEnclosing.m_Bottom = pPoint->m_Y;
	}
}
