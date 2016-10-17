#include "StdAfx.h"
#include "ZxDisplay2D_GraphGroup.h"


Display2D::ZxDisplay2D_GraphGroup::ZxDisplay2D_GraphGroup(int _Type)
	:m_Type(_Type)
{
	Clear();
	m_matDisplayTransform = D2D1::Matrix3x2F::Identity();
}


Display2D::ZxDisplay2D_GraphGroup::~ZxDisplay2D_GraphGroup(void)
{
	Clear();
}


void Display2D::ZxDisplay2D_GraphGroup::Clear()
{
	for (ZxDisplay2D_Graph_List::iterator ppGraphy = m_GraphyList.begin();
		ppGraphy != m_GraphyList.end(); ppGraphy ++)
	{
		delete *ppGraphy;
	}
	m_GraphyList.clear();
}


bool Display2D::ZxDisplay2D_GraphGroup::DoDraw(ID2D1RenderTarget* _pRenderTarget)
{
	if (!ZxDisplay2D_Layer::DoDraw(_pRenderTarget))
		return false;

	for (ZxDisplay2D_Graph_List::iterator ppGraphy = m_GraphyList.begin();
		ppGraphy != m_GraphyList.end(); ppGraphy++)
	{
		(*ppGraphy)->DoDraw(_pRenderTarget);
	}
	return true;
}

HRESULT Display2D::ZxDisplay2D_GraphGroup::AddGraphy(ZxDisplay2D_GraphBase* _pGraphy)
{
	if (_pGraphy != NULL) 
	{
		if (m_Type == _pGraphy->GetType())
		{
			m_GraphyList.push_back(_pGraphy);
			return S_OK;
		}
		else
			return S_FALSE;
	}
	else
		return S_FALSE;
}

void Display2D::ZxDisplay2D_GraphGroup::RemoveGraph(ZxDisplay2D_GraphBase* _pGraphy)
{
	for (ZxDisplay2D_Graph_List::iterator pGraph = m_GraphyList.begin();
		pGraph != m_GraphyList.end(); pGraph++)
	{
		if (*pGraph == _pGraphy)
		{
			delete _pGraphy;
			m_GraphyList.erase(pGraph);
			return;
		}
	}
}


int Display2D::ZxDisplay2D_GraphGroup::GetType() const
{
	return m_Type;
}

void Display2D::ZxDisplay2D_GraphGroup::Zoom(float _Scale)
{
	m_bShow = false;
	if (m_Type == ZXDISPLAY2D_GRAPH_POINT)
	{
		for (ZxDisplay2D_Graph_List::iterator pGraph = m_GraphyList.begin();
			pGraph != m_GraphyList.end(); pGraph++)
		{
			(*pGraph)->Zoom(_Scale);
		}
	}
	else
	{
		m_matDisplayTransform._11 = _Scale;
		m_matDisplayTransform._22 = _Scale;
	}
	m_bShow = true;
}

