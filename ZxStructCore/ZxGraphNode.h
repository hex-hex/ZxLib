#pragma once
#include <map>
#include <list>
#include "ZxGraphElement.h"
using namespace std;

namespace Graph
{
	class ZXSTRUCT_API ZxGraphNodeObject
	{
	private:
		virtual void CombineObject(ZxGraphNodeObject* _pObject) = 0;
	public:
		ZxGraphNodeObject();
		virtual ~ZxGraphNodeObject();
		static void CombineObject(ZxGraphNodeObject* _pObject1, ZxGraphNodeObject* _pObject2);
	};

	class ZXSTRUCT_API ZxGraphNode
		:public ZxGraphElement
	{
	public:
		class ZXSTRUCT_API ZxGraphNodeIterator
		{
		private:
			ZxGraphNode* m_pNode;
			ZxGraphElement::ZxGraphElementPtr m_pEdge;
			int m_Flag;//0标记下移，1标记右移;
		public:
			ZxGraphNodeIterator(ZxGraphNode& _refNode);
			ZxGraphNodeIterator(ZxGraphNode* _pNode);
			~ZxGraphNodeIterator();
			ZxGraphNodeIterator(const ZxGraphNodeIterator& _Ptr);
			ZxGraphNodeIterator& operator =(const ZxGraphNodeIterator& _Iter);
			void operator ++();
			unsigned int Index();
			bool IsNull();
		};
		typedef stack<unsigned int> ZxGraphIndexStack;
		typedef list<unsigned int> ZxGraphIndexList;

		ZxGraphNode();
		ZxGraphNode(unsigned int _Index,ZxGraphNodeObject* _pObject);
		ZxGraphNode(const ZxGraphNode& _Node);
		const ZxGraphNode& operator=(const ZxGraphNode& _Node);
		~ZxGraphNode(void);

		void MoreDegree();//请谨慎,一般不需要调用;
		void LessDegree();//请谨慎,一般不需要调用;
		//unsigned int m_Index[0]标识节点索引;
		//unsigned int m_Index[1]标识节点的度;
		bool PushAdjacent(ZxGraphIndexStack& _stackIndex);
		ZxGraphNodeObject* m_pObject;
		static void CombineNodeObject(ZxGraphNode* ,ZxGraphNode*);
	};
	typedef map<unsigned int,ZxGraphNode> ZxGraphNodeSet;
}