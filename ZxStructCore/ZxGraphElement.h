#pragma once
#include <vector>
#include <stack>
using namespace std;
namespace Graph
{
	class ZXSTRUCT_API ZxGraphElement
	{
	public:
		class ZXSTRUCT_API ZxGraphElementPtr
		{
		private:
			class ZxGraphElementAutoMemory
			{
			private:
				CRITICAL_SECTION m_IOLock;
				vector<ZxGraphElement>* m_pGraphElementSet;
				stack<int>* m_pGraphElementRecycle;
			public:
				ZxGraphElementAutoMemory();
				~ZxGraphElementAutoMemory();
				ZxGraphElement& ElementAt(int _Index);
				ZxGraphElementPtr CreateEdge(unsigned int _Index);
				void DestroyEdge(ZxGraphElementPtr&);
				void ClearEdges(bool _bSure = false);
			};
			static ZxGraphElementAutoMemory g_AutoMemory;
			static const ZxGraphElementPtr g_Null;
			int m_Index;
			ZxGraphElementPtr(int _Index);
		public:
			ZxGraphElementPtr();
			ZxGraphElementPtr(const ZxGraphElementPtr& _Ptr);
			~ZxGraphElementPtr();
			ZxGraphElementPtr& operator =(const ZxGraphElementPtr& _Ptr);
			ZxGraphElement& operator*();
			ZxGraphElement* operator->();
			bool IsNull();
			static const ZxGraphElementPtr& NullPtr();
			static ZxGraphElementPtr CreateEdge(unsigned int _Index);
			static void DestroyEdge(ZxGraphElementPtr&);
			static void ClearEdges(bool _bSure);
		};

	protected:
		union
		{
			unsigned int m_Index[2];//0节点的唯一标识;1为了方便合并;
			double m_dbIndex;//为了索引方便;
		};
		ZxGraphElementPtr m_Ptr[4];
	public:
		ZxGraphElement(unsigned int _Index);
		ZxGraphElement(const ZxGraphElement& _Element);
		const ZxGraphElement& operator=(const ZxGraphElement& _Element);
		virtual ~ZxGraphElement(void);
		virtual bool operator==(const ZxGraphElement& _Element);

		ZxGraphElementPtr& GetRight();
		ZxGraphElementPtr& GetLower();
		void SetRight(const ZxGraphElementPtr& _Ptr);
		void SetLower(const ZxGraphElementPtr& _Ptr);


		//////////////////////////////////////////////////////////////////////////为了方便删除;
		ZxGraphElementPtr& GetLeft();
		ZxGraphElementPtr& GetUpper();
		void SetLeft(const ZxGraphElementPtr& _Ptr);
		void SetUpper(const ZxGraphElementPtr& _Ptr);
		//////////////////////////////////////////////////////////////////////////
	
		unsigned int GetIndex() const;
		unsigned int GetIndex2() const;
		const double& GetDbIndex() const;
		void SetIndex(unsigned int _Index);
		void SetIndex2(unsigned int _Index);
	};
}
