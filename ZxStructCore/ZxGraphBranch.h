#pragma once
namespace Graph
{
	class ZXSTRUCT_API ZxGraphBranch
	{
	private:
		void* m_pGraph;
		int m_MaxSize;
	public:
		ZxGraphBranch(void);
		ZxGraphBranch(int _MaxNode);
		~ZxGraphBranch(void);
		void CreateGraph(int _MaxNode);
		bool SetEdge(int _lNode, int _rNode, int _nValue);
		bool DeleteEdge(int _lNode, int _rNode);
		//bool MergeNode(int _lNode, int _rNode);
		int  GetEdge(int _lNode, int _rNode);
	};
}

