#include "StdAfx.h"
#include "ZxGraphBranch.h"


Graph::ZxGraphBranch::ZxGraphBranch(void)
	:m_MaxSize(0)
{
	this->m_pGraph = new cv::SparseMat();
}

Graph::ZxGraphBranch::ZxGraphBranch(int _MaxNode)
	:m_MaxSize(_MaxNode)
{
	int GraphSize[2];
	GraphSize[0] = GraphSize[1] = _MaxNode;
	this->m_pGraph = new cv::SparseMat(2,GraphSize,CV_32S);
}

Graph::ZxGraphBranch::~ZxGraphBranch(void)
{
	delete (cv::SparseMat*)m_pGraph;
}


void Graph::ZxGraphBranch::CreateGraph(int _MaxNode)
{
	int GraphSize[2];
	GraphSize[0] = GraphSize[1] = _MaxNode;
	m_MaxSize = _MaxNode;
	((cv::SparseMat*)m_pGraph)->create(2,GraphSize,CV_32S);
}

bool Graph::ZxGraphBranch::SetEdge(int _lNode, int _rNode, int _nValue)
{
	if (_nValue)
		if(_lNode < m_MaxSize && _rNode < m_MaxSize)
		{
			int* pVal= ((int *)(((cv::SparseMat*)m_pGraph)->ptr(_lNode,_rNode,1)));
			if (pVal != NULL)
			{
				*pVal = _nValue;
				return true;
			}
			else
				return false;
		}
		else
			return false;
	else 
		return false;
}

bool Graph::ZxGraphBranch::DeleteEdge(int _lNode, int _rNode)
{
	if(_lNode < m_MaxSize && _rNode < m_MaxSize)
	{
		((cv::SparseMat*)m_pGraph)->erase(_lNode,_rNode);
		return true;
	}
	else
		return false;
}

// bool Graph::ZxGraphBranch::MergeNode(int _lNode, int _rNode)
// {
// 	if(_lNode < m_MaxSize && _rNode < m_MaxSize)
// 	{
// 
// 	}
// 	else
// 		return false;
// }

int Graph::ZxGraphBranch::GetEdge(int _lNode, int _rNode)
{
	int* pVal= ((int *)(((cv::SparseMat*)m_pGraph)->ptr(_lNode,_lNode,0)));
	if (pVal == NULL)
		return 0;
	else
		return *pVal;
}