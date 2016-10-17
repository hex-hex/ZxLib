#include "StdAfx.h"
#include "ZxGraphElement.h"


Graph::ZxGraphElement::ZxGraphElement(unsigned int _Index)
{
	m_Index[0] = _Index;
	m_Index[1] = 0;
}


Graph::ZxGraphElement::ZxGraphElement(const ZxGraphElement& _Element)
	:m_dbIndex(_Element.m_dbIndex)
{
	m_Ptr[0] = _Element.m_Ptr[0];
	m_Ptr[1] = _Element.m_Ptr[1];
	m_Ptr[2] = _Element.m_Ptr[2];
	m_Ptr[3] = _Element.m_Ptr[3];
}

const Graph::ZxGraphElement& Graph::ZxGraphElement::operator=(const ZxGraphElement& _Element)
{
	if (&_Element != this)
	{
		m_dbIndex = _Element.m_dbIndex;
		m_Ptr[0] = _Element.m_Ptr[0];
		m_Ptr[1] = _Element.m_Ptr[1];
		m_Ptr[2] = _Element.m_Ptr[2];
		m_Ptr[3] = _Element.m_Ptr[3];
	}
	return *this;
}


Graph::ZxGraphElement::~ZxGraphElement(void)
{
}


bool Graph::ZxGraphElement::operator==(const ZxGraphElement& _Element)
{
	return m_Index == _Element.m_Index;
}


Graph::ZxGraphElement::ZxGraphElementPtr& Graph::ZxGraphElement::GetRight()
{
	return m_Ptr[1];
}


Graph::ZxGraphElement::ZxGraphElementPtr& Graph::ZxGraphElement::GetLower()
{
	return m_Ptr[0];
}


void Graph::ZxGraphElement::SetRight(const ZxGraphElementPtr& _Ptr)
{
	m_Ptr[1] = _Ptr;
}


void Graph::ZxGraphElement::SetLower(const ZxGraphElementPtr& _Ptr)
{
	m_Ptr[0] = _Ptr;
}


Graph::ZxGraphElement::ZxGraphElementPtr& Graph::ZxGraphElement::GetLeft()
{
	return m_Ptr[3];
}


Graph::ZxGraphElement::ZxGraphElementPtr& Graph::ZxGraphElement::GetUpper()
{
	return m_Ptr[2];
}

void Graph::ZxGraphElement::SetLeft(const ZxGraphElementPtr& _Ptr)
{
	m_Ptr[3] = _Ptr;
}


void Graph::ZxGraphElement::SetUpper(const ZxGraphElementPtr& _Ptr)
{
	m_Ptr[2] = _Ptr;
}

unsigned int Graph::ZxGraphElement::GetIndex() const
{
	return m_Index[0];
}

unsigned int Graph::ZxGraphElement::GetIndex2() const
{
	return m_Index[1];
}

const double& Graph::ZxGraphElement::GetDbIndex() const
{
	return m_dbIndex;
}

void Graph::ZxGraphElement::SetIndex(unsigned int _Index)
{
	m_Index[0] = _Index;
}


void Graph::ZxGraphElement::SetIndex2(unsigned int _Index)
{
	m_Index[1] = _Index;
}