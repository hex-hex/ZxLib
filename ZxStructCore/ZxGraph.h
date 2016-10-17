#pragma once
#include "ZxGraphNode.h"
#include "ZxFileBase.h"
#include <stack>
using namespace std;
using namespace File;
namespace Graph
{
	class ZXSTRUCT_API ZxGraph
	{
	private:
		vector<int> m_MergeIndiceBuffer;
		ZxGraphNodeSet m_NodeSet;
		ZxGraphNodeSet::iterator m_iterNode;
		CRITICAL_SECTION m_IOLock;
	public:
		ZxGraph(void);
		~ZxGraph(void);
		int GetSize();
		void Clear();
		void ResetIterator();
		ZxGraphNodeObject* Next();
		ZxGraphNode* NextNode();
		bool HasNext();

		ZxGraphNodeObject* GetNodeObject(unsigned int _Index);
		ZxGraphNode* GetNode(unsigned int _Index);
		bool AddNode(unsigned int _Index, ZxGraphNodeObject* _pObject);
		ZxGraphNode* MergeNode(unsigned int _Node1, unsigned int _Node2);
		bool AddEdge(unsigned int _Node1, unsigned int _Node2);
		bool DeleteNode(unsigned int _Node);
		bool DeleteEdge(unsigned int _Node1, unsigned int _Node2);
		bool HasEdge(unsigned int _Node1, unsigned int _Node2);

		class ZXSTRUCT_API ZxGraphNodeLog
			:public ZxFileBase
		{
		protected:
			int m_NodeSize;
		public:
			ZxGraphNodeLog();
			virtual ~ZxGraphNodeLog();
			virtual bool SetFilePath(const char* _FileName) = 0;
			virtual bool Import(ZxGraph& _refGraph) = 0;
			virtual bool Export(ZxGraph& _refGraph) = 0;
		};

		class ZXSTRUCT_API ZxGraphEdgeLog
			:public ZxGraphNodeLog
		{
		private:
			int m_EdgeSize;
		public:
			ZxGraphEdgeLog();
			virtual ~ZxGraphEdgeLog();
			virtual bool SetFilePath(const char* _FileName);
			virtual bool Import(ZxGraph& _refGraph);
			virtual bool Export(ZxGraph& _refGraph);
		};
	};
}
