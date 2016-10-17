#include "StdAfx.h"
#include "ZxGraph.h"



Graph::ZxGraph::ZxGraphNodeLog::ZxGraphNodeLog()
	:m_NodeSize(0)
{

}

Graph::ZxGraph::ZxGraphNodeLog::~ZxGraphNodeLog()
{

}

Graph::ZxGraph::ZxGraphEdgeLog::ZxGraphEdgeLog()
	:m_EdgeSize(0)
{

}

Graph::ZxGraph::ZxGraphEdgeLog::~ZxGraphEdgeLog()
{

}

bool Graph::ZxGraph::ZxGraphEdgeLog::SetFilePath(const char* _FileName)
{
	ZeroMemory(m_PhysicalPath,MAX_PATH);
	strcpy_s(m_PhysicalPath,MAX_PATH,_FileName);
	m_IsFolder = false;
	CString strExt(GetFileExt());
	strExt.MakeLower();
	if (strExt != _T(".zbel"))
	{
		strExt = _T(".ZBEL");
		const char* strDriver = GetDriver();
		const char* strDir = GetFolders();
		const char* strFName = GetFileTitle();
		_makepath_s(m_PhysicalPath,strDriver,strDir,strFName,strExt);
		delete[] strDriver;
		delete[] strDir;
		delete[] strFName;
	}
	return Existance();
}


bool Graph::ZxGraph::ZxGraphEdgeLog::Import(ZxGraph& _refGraph)
{
	if (m_fileSize < 0)
		return false;

	CFile fileLog;
	if(!fileLog.Open(m_PhysicalPath,CFile::modeRead))
		return false;
	fileLog.Read(&m_NodeSize,sizeof(m_NodeSize));
	fileLog.Read(&m_EdgeSize,sizeof(m_EdgeSize));
	if (m_NodeSize != _refGraph.m_NodeSet.size())
		return false;
	int EdgeIndex[2];
	for (int i = 0; i != m_EdgeSize; i++)
	{
		fileLog.Read(&EdgeIndex,sizeof(int)*2);
		if(!_refGraph.AddEdge(EdgeIndex[0],EdgeIndex[1]))
			return false;
	}
	fileLog.Close();
	return true;
}


bool Graph::ZxGraph::ZxGraphEdgeLog::Export(ZxGraph& _refGraph)
{
	CFile fileLog;
	if(!fileLog.Open(m_PhysicalPath,CFile::modeWrite | CFile::modeCreate))
		return false;

	m_NodeSize = _refGraph.m_NodeSet.size();
	fileLog.Write(&m_NodeSize,sizeof(m_NodeSize));
	fileLog.Write(&m_EdgeSize,sizeof(m_EdgeSize));

	ZxGraphElement::ZxGraphElementPtr pNode;
	_refGraph.ResetIterator();
	while(_refGraph.HasNext())
	{
		pNode = _refGraph.NextNode()->GetLower();
		while(!pNode.IsNull())
		{
			fileLog.Write(&(pNode->GetDbIndex()),sizeof(double));
			m_EdgeSize++;
			pNode = pNode->GetLower();
		}
	}
	fileLog.SeekToBegin();
	fileLog.Write(&m_NodeSize,sizeof(m_NodeSize));
	fileLog.Write(&m_EdgeSize,sizeof(m_EdgeSize));
	fileLog.Close();
	return true;
}

Graph::ZxGraph::ZxGraph(void)
{
	m_MergeIndiceBuffer.clear();
	InitializeCriticalSection(&m_IOLock);
}


Graph::ZxGraph::~ZxGraph(void)
{
	DeleteCriticalSection(&m_IOLock);
}

void Graph::ZxGraph::ResetIterator()
{
	m_iterNode = m_NodeSet.begin();
}

Graph::ZxGraphNodeObject* Graph::ZxGraph::Next()
{
	return (m_iterNode++)->second.m_pObject;
}

Graph::ZxGraphNode* Graph::ZxGraph::NextNode()
{
	return &((m_iterNode++)->second);
}

bool Graph::ZxGraph::HasNext()
{
	return m_iterNode != m_NodeSet.end();
}

Graph::ZxGraphNode* Graph::ZxGraph::GetNode(unsigned int _Index)
{
	if(m_NodeSet.count(_Index) == 0)
		return NULL;
	else
		return &(m_NodeSet[_Index]);
}

void Graph::ZxGraph::Clear()
{
	EnterCriticalSection(&m_IOLock);
	stack<ZxGraphElement::ZxGraphElementPtr> GraphEdge;
	ZxGraphElement::ZxGraphElementPtr pEdge = ZxGraphElement::ZxGraphElementPtr::NullPtr();
	for (ZxGraphNodeSet::iterator Iter = m_NodeSet.begin();
		Iter != m_NodeSet.end(); Iter++)
	{
		delete Iter->second.m_pObject;
		pEdge = Iter->second.GetLower();
		while (!pEdge.IsNull()) 
		{
			GraphEdge.push(pEdge);
			pEdge = pEdge->GetLower();
		};		
	}
	m_NodeSet.clear();
	while(!GraphEdge.empty())
	{
		ZxGraphElement::ZxGraphElementPtr::DestroyEdge(GraphEdge.top());
		GraphEdge.pop();
	}
	LeaveCriticalSection(&m_IOLock);
}

int Graph::ZxGraph::GetSize()
{
	size_t intSize;
	EnterCriticalSection(&m_IOLock);
	intSize = m_NodeSet.size();
	LeaveCriticalSection(&m_IOLock);
	return intSize;
}

Graph::ZxGraphNodeObject* Graph::ZxGraph::GetNodeObject(unsigned int _Index)
{
	if(m_NodeSet.count(_Index) == 0)
		return NULL;
	else
		return m_NodeSet[_Index].m_pObject;
}

bool  Graph::ZxGraph::AddNode(unsigned int _Index, ZxGraphNodeObject* _pObject)
{
	EnterCriticalSection(&m_IOLock);
	if (m_NodeSet.count(_Index) != 0)
	{
		LeaveCriticalSection(&m_IOLock);
		return false;
	}
	ZxGraphNode NewNode(_Index,_pObject);
	m_NodeSet.insert(pair<unsigned, ZxGraphNode>(_Index, NewNode));
	LeaveCriticalSection(&m_IOLock);
	return true;
}


bool Graph::ZxGraph::AddEdge(unsigned int _Node1,unsigned int _Node2)
{
	EnterCriticalSection(&m_IOLock);
	if(_Node1 > _Node2)//总是挂在标号小的节点下面;
	{
		LeaveCriticalSection(&m_IOLock);
		return AddEdge(_Node2,_Node1);
	}
// 	else if (_Node1 == _Node2)//不允许自己邻接;
// 	{
// 		LeaveCriticalSection(&m_IOLock);
// 		return false;
// 	}
	else if (m_NodeSet.count(_Node1) == 0 ||
		m_NodeSet.count(_Node2) == 0)
	{
		LeaveCriticalSection(&m_IOLock);
		return false;
	}
	else
	{
		ZxGraphNode& refNode1(m_NodeSet[_Node1]);
		ZxGraphNode& refNode2(m_NodeSet[_Node2]);
		//Node1总比Node2小
		ZxGraphElement::ZxGraphElementPtr pEdge = ZxGraphElement::ZxGraphElementPtr::CreateEdge(_Node2);
		pEdge->SetIndex2(_Node1);//Index2即该Edge所属的Node
		ZxGraphElement::ZxGraphElementPtr pEdgeFore, pEdgeBack = refNode1.GetLower();
		if (pEdgeBack.IsNull())
		{
			refNode1.SetLower(pEdge);
			//没有反向赋值，表示直接连接节点
		}
		else
		{
			if (pEdgeBack->GetIndex() == _Node2)
			{
				ZxGraphElement::ZxGraphElementPtr::DestroyEdge(pEdge);
				LeaveCriticalSection(&m_IOLock);
				return true;
			}
			else if (pEdgeBack->GetIndex() > _Node2)
			{
				pEdge->SetLower(pEdgeBack);
				//没有反向赋值，表示直接连接节点
				refNode1.SetLower(pEdge);
				pEdgeBack->SetUpper(pEdge);
				//跳出
			}
			else
 			{
				pEdgeFore = pEdgeBack->GetLower();
				while(!pEdgeFore.IsNull())
				{
					if(pEdgeFore->GetIndex() < _Node2)
					{
						pEdgeBack = pEdgeFore;
						pEdgeFore = pEdgeFore->GetLower();
						continue;
					}
					else if (pEdgeFore->GetIndex() > _Node2)
					{
						pEdge->SetLower(pEdgeFore);
						pEdgeFore->SetUpper(pEdge);
						break;
					}
					else
					{
						ZxGraphElement::ZxGraphElementPtr::DestroyEdge(pEdge);
						LeaveCriticalSection(&m_IOLock);
						return true;
					}
				}
				pEdge->SetUpper(pEdgeBack);
				pEdgeBack->SetLower(pEdge);
				//跳出
			}
		}

		pEdgeBack = refNode2.GetRight();
		if (pEdgeBack.IsNull())
		{
			refNode2.SetRight(pEdge);
		}
		else
		{
			if (pEdgeBack->GetIndex() < _Node1)
			{
				pEdge->SetRight(pEdgeBack);
				refNode2.SetRight(pEdge);
				pEdgeBack->SetLeft(pEdge);
				//跳出
			}
			else
			{
				pEdgeFore = pEdgeBack->GetRight();
				if(pEdgeFore.IsNull())
				{
					pEdge->SetLeft(pEdgeBack);
					pEdgeBack->SetRight(pEdge);
					//跳出
				}
				else
				{
					while(!pEdgeFore.IsNull())
					{
						if(pEdgeFore->GetIndex() > _Node2)
						{
							pEdgeBack = pEdgeFore;
							pEdgeFore = pEdgeFore->GetRight();
							continue;
						}
						else
						{
							pEdge->SetRight(pEdgeFore);
							pEdgeFore->SetLeft(pEdge);
							break;
						}
					}
					pEdge->SetLeft(pEdgeBack);
					pEdgeBack->SetRight(pEdge);
				}
			}
		}
		refNode1.MoreDegree();
		refNode2.MoreDegree();
		LeaveCriticalSection(&m_IOLock);
		return true;
	}
}


bool Graph::ZxGraph::HasEdge(unsigned int _Node1, unsigned int _Node2)
{
	if(_Node1 > _Node2)//总是挂在标号小的节点下面;
		return HasEdge(_Node2, _Node1);
	else if (_Node1 == _Node2)//不允许自己邻接;
		return false;
	else if (m_NodeSet.count(_Node1) == 0 ||
		m_NodeSet.count(_Node2) == 0)
		return false;
	else
	{	
		ZxGraphElement::ZxGraphElementPtr pIterator = m_NodeSet[_Node1].GetLower();
		while(!pIterator.IsNull())
		{
			if (pIterator->GetIndex() == _Node2)
			{
				return true;
			}
			else
				pIterator = pIterator->GetLower();
		}
		return false;
	}
}


bool Graph::ZxGraph::DeleteEdge(unsigned int _Node1, unsigned int _Node2)
{
	if(_Node1 > _Node2)//总是挂在标号小的节点下面;
		return DeleteEdge(_Node2,_Node1);
// 	else if (_Node1 == _Node2)//不允许自己邻接;
// 		return false;
	else if (m_NodeSet.count(_Node1) == 0 ||
		m_NodeSet.count(_Node2) == 0)
		return false;
	else
	{	
		ZxGraphNode& refNode1(m_NodeSet[_Node1]);
		ZxGraphNode& refNode2(m_NodeSet[_Node2]);
		ZxGraphElement::ZxGraphElementPtr pEdgeFore,
			pEdgeBack = refNode1.GetLower();

		if(pEdgeBack.IsNull())
		{
			return false;
		}
		else if (pEdgeBack->GetIndex() == _Node2)
		{
			pEdgeFore = pEdgeBack->GetLower();
			pEdgeFore->SetUpper(ZxGraphElement::ZxGraphElementPtr::NullPtr());
			refNode1.SetLower(pEdgeFore);
		}
		else
		{
			while(!pEdgeBack.IsNull())
			{
				if (pEdgeBack->GetIndex() == _Node2)
				{
					pEdgeFore = pEdgeBack->GetLower();
					pEdgeFore->SetUpper(pEdgeBack->GetUpper());
					pEdgeBack->GetUpper()->SetLower(pEdgeFore);
					break;
				}
				else
					pEdgeBack = pEdgeBack->GetLower();
			}
			if (pEdgeBack.IsNull())
			{
				return false;
			}
		}

		if(pEdgeBack->GetLeft().IsNull())
		{
			pEdgeFore = pEdgeBack->GetRight();
			refNode2.SetRight(pEdgeFore);
			pEdgeFore->SetLeft(ZxGraphElement::ZxGraphElementPtr::NullPtr());
		}
		else
		{
			pEdgeFore = pEdgeBack->GetRight();
			pEdgeFore->SetLeft(pEdgeBack->GetLeft());
			pEdgeBack->GetLeft()->SetRight(pEdgeFore);
		}
		ZxGraphElement::ZxGraphElementPtr::DestroyEdge(pEdgeBack);
		refNode1.LessDegree();
		refNode2.LessDegree();
		return true;
	}
}


bool Graph::ZxGraph::DeleteNode(unsigned int _Node)
{
	if(m_NodeSet.count(_Node) == 0)
		return false;
	else
	{
		ZxGraphElement::ZxGraphElementPtr pEdgeBack,
			pEdgeFore = m_NodeSet[_Node].GetLower();
		while(!pEdgeFore.IsNull())
		{
			pEdgeBack = pEdgeFore;
			pEdgeFore = pEdgeFore->GetLower();
			if (pEdgeBack->GetLeft().IsNull())
			{
				m_NodeSet[pEdgeBack->GetIndex()].SetRight(pEdgeBack->GetRight());
				pEdgeBack->GetRight()->SetLeft(ZxGraphElement::ZxGraphElementPtr::NullPtr());
			}
			else
			{
				pEdgeBack->GetLeft()->SetRight(pEdgeBack->GetRight());
				pEdgeBack->GetRight()->SetLeft(pEdgeBack->GetLeft());
			}
			m_NodeSet[pEdgeBack->GetIndex()].LessDegree();
			ZxGraphElement::ZxGraphElementPtr::DestroyEdge(pEdgeBack);
		}

		pEdgeFore = m_NodeSet[_Node].GetRight();
		while(!pEdgeFore.IsNull())
		{
			pEdgeBack = pEdgeFore;
			pEdgeFore = pEdgeFore->GetRight();
			if (pEdgeBack->GetUpper().IsNull())
			{
				m_NodeSet[pEdgeBack->GetIndex2()].SetLower(pEdgeBack->GetLower());
				pEdgeBack->GetLower()->SetUpper(ZxGraphElement::ZxGraphElementPtr::NullPtr());
			}
			else
			{
				pEdgeBack->GetUpper()->SetLower(pEdgeBack->GetLower());
				pEdgeBack->GetLower()->SetUpper(pEdgeBack->GetUpper());
			}
			m_NodeSet[pEdgeBack->GetIndex2()].LessDegree();
			ZxGraphElement::ZxGraphElementPtr::DestroyEdge(pEdgeBack);
		}
		m_NodeSet.erase(_Node);
		return true;
	}
}


Graph::ZxGraphNode* Graph::ZxGraph::MergeNode(unsigned int _Node1, unsigned int _Node2)
{
	EnterCriticalSection(&m_IOLock);
	if(_Node1 > _Node2)//总是挂在标号小的节点下面;
	{
		LeaveCriticalSection(&m_IOLock);
		return MergeNode(_Node2,_Node1);
	}
	else if (_Node1 == _Node2)
	{
		LeaveCriticalSection(&m_IOLock);
		return NULL;
	}
	else if (m_NodeSet.count(_Node1) == 0 ||
		m_NodeSet.count(_Node2) == 0)
	{
		LeaveCriticalSection(&m_IOLock);
		return NULL;
	}
	else
	{
		ZxGraphNode& refNode1(m_NodeSet[_Node1]);
		ZxGraphNode& refNode2(m_NodeSet[_Node2]);
		unsigned int intIndex;
		m_MergeIndiceBuffer.clear();
		ZxGraphElement::ZxGraphElementPtr pEdgeFore = refNode2.GetLower();
		ZxGraphElement::ZxGraphElementPtr pEdgeBack;
		while(!pEdgeFore.IsNull())
		{
			pEdgeBack = pEdgeFore;
			pEdgeFore = pEdgeFore->GetLower();
			intIndex = pEdgeBack->GetIndex();

			if (pEdgeBack->GetLeft().IsNull())
			{
				m_NodeSet[intIndex].SetRight(pEdgeBack->GetRight());
			}
			else
			{
				pEdgeBack->GetLeft()->SetRight(pEdgeBack->GetRight());
			}
			pEdgeBack->GetRight()->SetLeft(pEdgeBack->GetLeft());

			m_MergeIndiceBuffer.push_back(intIndex);
			m_NodeSet[intIndex].LessDegree();
			ZxGraphElement::ZxGraphElementPtr::DestroyEdge(pEdgeBack);
		}

		pEdgeFore = refNode2.GetRight();
		while(!pEdgeFore.IsNull())
		{
			pEdgeBack = pEdgeFore;
			pEdgeFore = pEdgeFore->GetRight();
			intIndex = pEdgeBack->GetIndex2();
			if (pEdgeBack->GetUpper().IsNull())
			{
				m_NodeSet[intIndex].SetLower(pEdgeBack->GetLower());
				pEdgeBack->GetLower()->SetUpper(ZxGraphElement::ZxGraphElementPtr::NullPtr());
			}
			else
			{
				pEdgeBack->GetUpper()->SetLower(pEdgeBack->GetLower());
				pEdgeBack->GetLower()->SetUpper(pEdgeBack->GetUpper());
			}		
			m_MergeIndiceBuffer.push_back(intIndex);
			m_NodeSet[intIndex].LessDegree();
			ZxGraphElement::ZxGraphElementPtr::DestroyEdge(pEdgeBack);
		}

		ASSERT(m_MergeIndiceBuffer.size() == refNode2.GetIndex2());

		ZxGraphNode::CombineNodeObject(&(refNode1),&(refNode2));
		m_NodeSet.erase(_Node2);

		for(vector<int>::iterator i = m_MergeIndiceBuffer.begin(); 
			i != m_MergeIndiceBuffer.end(); i++)
		{
			AddEdge(_Node1,*i);
		}
		LeaveCriticalSection(&m_IOLock);
		return &refNode1;
	}
}

