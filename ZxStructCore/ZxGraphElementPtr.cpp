#include "StdAfx.h"
#include "ZxGraphElement.h"



Graph::ZxGraphElement::ZxGraphElementPtr::ZxGraphElementAutoMemory::ZxGraphElementAutoMemory()
{
	m_pGraphElementSet = new vector<ZxGraphElement>();
	ZxGraphElement Edge(0);
	m_pGraphElementSet->push_back(Edge);//第0个是废的;
	m_pGraphElementRecycle = new stack<int>();
	InitializeCriticalSection(&m_IOLock);
}

Graph::ZxGraphElement::ZxGraphElementPtr::ZxGraphElementAutoMemory::~ZxGraphElementAutoMemory()
{
	DeleteCriticalSection(&m_IOLock);
	delete m_pGraphElementRecycle;
	delete m_pGraphElementSet;
}

Graph::ZxGraphElement::ZxGraphElementPtr Graph::ZxGraphElement::ZxGraphElementPtr::ZxGraphElementAutoMemory::CreateEdge(unsigned int _Index)
{
	EnterCriticalSection(&m_IOLock);
	if (m_pGraphElementRecycle->size())
	{
		ZxGraphElementPtr EdgePtr(m_pGraphElementRecycle->top());
		m_pGraphElementRecycle->pop();
		EdgePtr->SetIndex(_Index);
		EdgePtr->SetIndex2(0);
		LeaveCriticalSection(&m_IOLock);
		return EdgePtr;
	}
	else
	{
		ZxGraphElementPtr EdgePtr(m_pGraphElementSet->size());
		ZxGraphElement Edge(_Index);
		m_pGraphElementSet->push_back(Edge);
		LeaveCriticalSection(&m_IOLock);
		return EdgePtr;
	}
}

void Graph::ZxGraphElement::ZxGraphElementPtr::ZxGraphElementAutoMemory::DestroyEdge(Graph::ZxGraphElement::ZxGraphElementPtr& _Ptr)
{
	EnterCriticalSection(&m_IOLock);
	m_pGraphElementRecycle->push(_Ptr.m_Index);
	_Ptr->m_Ptr[0] = ZxGraphElementPtr::NullPtr();
	_Ptr->m_Ptr[1] = ZxGraphElementPtr::NullPtr();
	_Ptr->m_Ptr[2] = ZxGraphElementPtr::NullPtr();
	_Ptr->m_Ptr[3] = ZxGraphElementPtr::NullPtr();
	LeaveCriticalSection(&m_IOLock);
}

void Graph::ZxGraphElement::ZxGraphElementPtr::ZxGraphElementAutoMemory::ClearEdges(bool _bSure)
{
	if (_bSure)
	{
		EnterCriticalSection(&m_IOLock);
		m_pGraphElementSet->clear();
		while(!m_pGraphElementRecycle->empty())
			m_pGraphElementRecycle->pop();
		LeaveCriticalSection(&m_IOLock);
	}
}

Graph::ZxGraphElement& Graph::ZxGraphElement::ZxGraphElementPtr::ZxGraphElementAutoMemory::ElementAt(int _Index)
{
	ASSERT(!(_Index < 0));
	return m_pGraphElementSet->at(_Index);
}

Graph::ZxGraphElement::ZxGraphElementPtr::ZxGraphElementAutoMemory Graph::ZxGraphElement::ZxGraphElementPtr::g_AutoMemory 
	= Graph::ZxGraphElement::ZxGraphElementPtr::ZxGraphElementAutoMemory();

Graph::ZxGraphElement::ZxGraphElementPtr const Graph::ZxGraphElement::ZxGraphElementPtr::g_Null = 
	Graph::ZxGraphElement::ZxGraphElementPtr::ZxGraphElementPtr();

const Graph::ZxGraphElement::ZxGraphElementPtr& Graph::ZxGraphElement::ZxGraphElementPtr::NullPtr()
{
	return g_Null;
}


Graph::ZxGraphElement::ZxGraphElementPtr::ZxGraphElementPtr(int _Index)
	:m_Index(_Index)
{

}

Graph::ZxGraphElement::ZxGraphElementPtr::ZxGraphElementPtr()
	:m_Index(0)
{

}

Graph::ZxGraphElement::ZxGraphElementPtr::ZxGraphElementPtr(const ZxGraphElementPtr& _Ptr)
	:m_Index(_Ptr.m_Index)
{

}

Graph::ZxGraphElement::ZxGraphElementPtr::~ZxGraphElementPtr()
{

}


bool Graph::ZxGraphElement::ZxGraphElementPtr::IsNull()
{
	return m_Index == 0;
}

Graph::ZxGraphElement::ZxGraphElementPtr& Graph::ZxGraphElement::ZxGraphElementPtr::operator =(const Graph::ZxGraphElement::ZxGraphElementPtr& _Ptr)
{
	if (&_Ptr != this)
	{
		this->m_Index = _Ptr.m_Index;
	}
	return *this;
}

Graph::ZxGraphElement& Graph::ZxGraphElement::ZxGraphElementPtr::operator*()
{
	return (g_AutoMemory.ElementAt(this->m_Index));
}


Graph::ZxGraphElement* Graph::ZxGraphElement::ZxGraphElementPtr::operator->()
{
	return &(g_AutoMemory.ElementAt(this->m_Index));
}

Graph::ZxGraphElement::ZxGraphElementPtr Graph::ZxGraphElement::ZxGraphElementPtr::CreateEdge(unsigned int _Index)
{
	return g_AutoMemory.CreateEdge(_Index);
}

void Graph::ZxGraphElement::ZxGraphElementPtr::DestroyEdge(Graph::ZxGraphElement::ZxGraphElementPtr& _pEdge)
{
	g_AutoMemory.DestroyEdge(_pEdge);
}

void Graph::ZxGraphElement::ZxGraphElementPtr::ClearEdges(bool _bSure)
{
	g_AutoMemory.ClearEdges(_bSure);
}