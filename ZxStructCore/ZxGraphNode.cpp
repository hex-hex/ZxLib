#include "StdAfx.h"
#include "ZxGraphNode.h"

Graph::ZxGraphNodeObject::ZxGraphNodeObject()
{

}

Graph::ZxGraphNodeObject::~ZxGraphNodeObject()
{

}

void Graph::ZxGraphNodeObject::CombineObject(ZxGraphNodeObject* _pObject1, ZxGraphNodeObject* _pObject2)
{
	_pObject1->CombineObject(_pObject2);
}


Graph::ZxGraphNode::ZxGraphNodeIterator::ZxGraphNodeIterator(ZxGraphNode* _pNode)
	:m_pNode(_pNode)
	,m_Flag(0)
{
	m_pEdge = m_pNode->GetLower();
	if (m_pEdge.IsNull())
	{
		m_pEdge = m_pNode->GetRight();
		m_Flag = 1;
	}
}

Graph::ZxGraphNode::ZxGraphNodeIterator::ZxGraphNodeIterator(ZxGraphNode& _refNode)
	:m_pNode(&_refNode)
	,m_Flag(0)
{
	m_pEdge = m_pNode->GetLower();
	if (m_pEdge.IsNull())
	{
		m_pEdge = m_pNode->GetRight();
		m_Flag = 1;
	}
}

Graph::ZxGraphNode::ZxGraphNodeIterator::~ZxGraphNodeIterator()
{

}



Graph::ZxGraphNode::ZxGraphNodeIterator::ZxGraphNodeIterator(const ZxGraphNodeIterator& _Ptr)
	:m_pNode(_Ptr.m_pNode)
	,m_Flag(_Ptr.m_Flag)
	,m_pEdge(_Ptr.m_pEdge)
{

}

Graph::ZxGraphNode::ZxGraphNodeIterator& Graph::ZxGraphNode::ZxGraphNodeIterator::operator =(const ZxGraphNodeIterator& _Iter)
{
	if (&_Iter != this)
	{
		m_pNode = _Iter.m_pNode;
		m_Flag = _Iter.m_Flag;
		m_pEdge = _Iter.m_pEdge;
	}
	return *this;
}

void Graph::ZxGraphNode::ZxGraphNodeIterator::operator ++()
{
	if (m_Flag)
	{
		m_pEdge = m_pEdge->GetRight();
	}
	else
	{
		m_pEdge = m_pEdge->GetLower();
		if (m_pEdge.IsNull())
		{
			m_pEdge = m_pNode->GetRight();
			m_Flag = 1;
		}
	}
}

unsigned int Graph::ZxGraphNode::ZxGraphNodeIterator::Index()
{
	if (m_Flag)
		return m_pEdge->GetIndex2();
	else
		return m_pEdge->GetIndex();
}

bool Graph::ZxGraphNode::ZxGraphNodeIterator::IsNull()
{
	return m_pEdge.IsNull();
}

Graph::ZxGraphNode::ZxGraphNode()
	:ZxGraphElement(UINT_MAX)
	,m_pObject(NULL)
{

}


Graph::ZxGraphNode::ZxGraphNode(unsigned int _Index,ZxGraphNodeObject* _pObject)
	:ZxGraphElement(_Index)
	,m_pObject(_pObject)
{

}


Graph::ZxGraphNode::ZxGraphNode(const ZxGraphNode& _Node)
	:ZxGraphElement(_Node)
	,m_pObject(_Node.m_pObject)
{

}

const Graph::ZxGraphNode& Graph::ZxGraphNode::operator=(const ZxGraphNode& _Node)
{
	if (&_Node != this)
	{
		ZxGraphElement::operator=(_Node);
		m_pObject = _Node.m_pObject;
	}
	return *this;
}


Graph::ZxGraphNode::~ZxGraphNode(void)
{
}

void Graph::ZxGraphNode::CombineNodeObject(ZxGraphNode* _Node1,ZxGraphNode* _Node2)
{
	ZxGraphNodeObject::CombineObject(_Node1->m_pObject,_Node2->m_pObject);
}


void Graph::ZxGraphNode::MoreDegree()
{
	m_Index[1]++;
}


void Graph::ZxGraphNode::LessDegree()
{
	m_Index[1]--;
}

bool Graph::ZxGraphNode::PushAdjacent(ZxGraphIndexStack& _stackIndex)
{
	if (m_Index[1])
	{
		ZxGraphElement::ZxGraphElementPtr IteratorEdge = ZxGraphElement::ZxGraphElementPtr::NullPtr();//Á¬½Ó±ß±éÀúÆ÷;
		IteratorEdge = GetLower();
		while(!IteratorEdge.IsNull())
		{
			_stackIndex.push(IteratorEdge->GetIndex());
			IteratorEdge = IteratorEdge->GetLower();
		}
		IteratorEdge = GetRight();
		while(!IteratorEdge.IsNull())
		{
			_stackIndex.push(IteratorEdge->GetIndex2());
			IteratorEdge = IteratorEdge->GetRight();
		}
		return true;
	}
	else
		return false;
}