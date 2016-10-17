#include "StdAfx.h"
#include "ZxDevice2D.h"


Display2D::ZxDevice2D::ZxDevice2D(void)
	:m_pD2DFactory(NULL)
{
	Clear();
}


Display2D::ZxDevice2D::~ZxDevice2D(void)
{
	Clear();
}


bool Display2D::ZxDevice2D::Initialize(bool _bMultiThread)
{
	D2D1_FACTORY_TYPE factoryType;
	if (_bMultiThread)
	{
		factoryType = D2D1_FACTORY_TYPE_MULTI_THREADED;
	}
	else
	{
		factoryType = D2D1_FACTORY_TYPE_SINGLE_THREADED;
	}
	if(FAILED(D2D1CreateFactory(factoryType, &m_pD2DFactory)))
		return false;

	return true;
}


void Display2D::ZxDevice2D::Clear(void)
{
	if(m_DisplayList.size() > 0)
	{
		for(ZxDisplay2D_List::iterator ppDsply = m_DisplayList.begin();
			ppDsply != m_DisplayList.end(); ppDsply++)
		{
			delete (*ppDsply);
		}
		m_DisplayList.clear();
	}
	SAFE_RELEASE(m_pD2DFactory);
}


bool Display2D::ZxDevice2D::AddDisplay(HWND _hWnd)
{
	if (!m_pD2DFactory)
	{
		return false;
	}
	ZxDisplay2D* pDisplay2D = new ZxDisplay2D;
	if(pDisplay2D->Initialize(_hWnd,m_pD2DFactory) != S_OK)
	{
		delete pDisplay2D;
		return false;;
	}
	m_DisplayList.push_back(pDisplay2D);
	return true;
}


void Display2D::ZxDevice2D::DoDraw(void)
{
	if(m_DisplayList.size() > 0)
	{
		for(ZxDisplay2D_List::iterator ppDsply = m_DisplayList.begin();
			ppDsply != m_DisplayList.end(); ppDsply++)
		{
			(*ppDsply)->OnRender();
		}
	}
}


Display2D::ZxDisplay2D* Display2D::ZxDevice2D::GetDisplay(int _Index)
{
	if(_Index < 0)
	{
		return *(--m_DisplayList.end());
	}

	else if (static_cast<unsigned int>(_Index) < m_DisplayList.size())
	{
		return m_DisplayList.at(_Index);
	}
	else
		return NULL;
}