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
			int m_Flag;//0������ƣ�1�������;
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

		void MoreDegree();//�����,һ�㲻��Ҫ����;
		void LessDegree();//�����,һ�㲻��Ҫ����;
		//unsigned int m_Index[0]��ʶ�ڵ�����;
		//unsigned int m_Index[1]��ʶ�ڵ�Ķ�;
		bool PushAdjacent(ZxGraphIndexStack& _stackIndex);
		ZxGraphNodeObject* m_pObject;
		static void CombineNodeObject(ZxGraphNode* ,ZxGraphNode*);
	};
	typedef map<unsigned int,ZxGraphNode> ZxGraphNodeSet;
}