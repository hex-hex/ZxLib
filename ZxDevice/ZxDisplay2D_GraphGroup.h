#pragma once
#include "ZxDisplay2D_Layer.h"
#include "ZxDisplay2D_GraphBase.h"
#include <vector>
using namespace std;

namespace Display2D
{
	typedef vector<ZxDisplay2D_GraphBase*> ZxDisplay2D_Graph_List;
	class ZxDisplay2D_GraphGroup 
		: public ZxDisplay2D_Layer
	{
	protected:
		int m_Type;// ∏¡ø¿‡–Õ
		ZxDisplay2D_Graph_List m_GraphyList;
	public:
		ZxDisplay2D_GraphGroup(int _Type);
		virtual ~ZxDisplay2D_GraphGroup(void);
		void Clear();
		virtual bool DoDraw(ID2D1RenderTarget* _pRenderTarget);
		int GetType() const;
		virtual HRESULT AddGraphy(ZxDisplay2D_GraphBase* _pGraphy);
		virtual void RemoveGraph(ZxDisplay2D_GraphBase* _pGraphy);
		void Zoom(float _Scale);
	};
}

