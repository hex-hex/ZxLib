#include "StdAfx.h"
#include "ZxDisplay2D.h"

Display2D::ZxDisplay2D::ZxDisplay2D(void)
	: m_pRenderTarget(NULL)
	,m_TopBitmapGroup(NULL)
	,m_TopBitmapShowOrder(NULL)
{
	m_Origin.x = m_Origin.y = 0;
	m_BitmapGroupList.clear();
	m_GraphGroupList.clear();
	m_TopGraphGroup.clear();
	m_TopBitmapGroup = new ZxDisplay2D_BitmapGroup;
	SetBackGround();
}

Display2D::ZxDisplay2D::~ZxDisplay2D(void)
{
	ClearAllBitmapGroup();
	ClearAllBitmapGroup();
	ClearAllTopLayer();
}

int Display2D::ZxDisplay2D::GetNewGroupIndex(bool _bImg, bool _Top/* = false*/)
{
	int newIndex(0);

	if(_bImg)
	{
		do 
		{
			newIndex = rand();
		} while (m_BitmapGroupList.find(newIndex) != m_BitmapGroupList.end());
		return newIndex;
	}
	else
	{
		if (_Top)
		{
			do 
			{
				newIndex = rand();
			} while (m_GraphGroupList.find(newIndex) != m_GraphGroupList.end());
			return newIndex;
		}
		else
		{
			do 
			{
				newIndex = rand();
			} while (m_TopGraphGroup.find(newIndex) != m_TopGraphGroup.end());
			return newIndex;
		}
	}
}

void Display2D::ZxDisplay2D::ClearAllTopLayer()
{
	delete m_TopBitmapGroup;
	m_TopBitmapGroup = NULL;
	for(ZxDisplay2D_GraphGroup_Map::iterator pGroup = m_TopGraphGroup.begin();
		pGroup != m_TopGraphGroup.end(); pGroup++)
	{
		delete pGroup->second;
	}
	m_TopGraphGroup.clear();
}

void Display2D::ZxDisplay2D::ClearAllBitmapGroup()
{
	for(ZxDisplay2D_BitmapGroup_Map::iterator pGroup = m_BitmapGroupList.begin();
		pGroup != m_BitmapGroupList.end(); pGroup++)
	{
		delete pGroup->second;
	}
	m_BitmapGroupList.clear();
	m_BitmapShowOrder.clear();
}

void Display2D::ZxDisplay2D::ClearAllGraphGroup()
{
	for(ZxDisplay2D_GraphGroup_Map::iterator pGroup = m_GraphGroupList.begin();
		pGroup != m_GraphGroupList.end(); pGroup++)
	{
		delete pGroup->second;
	}
	m_GraphGroupList.clear();
	m_GraphShowOrder.clear();
}


void Display2D::ZxDisplay2D::ClearBitmapGroup(unsigned int _Index)
{
	if (m_BitmapGroupList.find(_Index) != m_BitmapGroupList.end())
	{
		m_BitmapGroupList[_Index]->Clear();
		m_BitmapGroupList.erase(_Index);
		m_BitmapShowOrder.remove(_Index);
	};
}


void Display2D::ZxDisplay2D::ClearGraphGroup(unsigned int _Index)
{
	if (m_GraphGroupList.find(_Index) != m_GraphGroupList.end())
	{
		m_GraphGroupList[_Index]->Clear();
		m_GraphGroupList.erase(_Index);
		m_GraphShowOrder.remove(_Index);
	}
}


void Display2D::ZxDisplay2D::MoveBitmapBy(unsigned int _IndexGroup, float _x, float _y)
{
	if ( m_BitmapGroupList.find(_IndexGroup ) !=  m_BitmapGroupList.end())
	{
		m_BitmapGroupList.at(_IndexGroup)->MoveBy(_x,_y);
	}
}

void Display2D::ZxDisplay2D::MoveBitmapTo(unsigned int _IndexGroup, float _x, float _y)
{
	if (m_BitmapGroupList.find(_IndexGroup ) !=  m_BitmapGroupList.end())
	{
		*(m_BitmapGroupList.at(_IndexGroup)->GetTransformPara(31)) = - _x;
		*(m_BitmapGroupList.at(_IndexGroup)->GetTransformPara(32)) = - _y;
	}
}

float* Display2D::ZxDisplay2D::GetBitmapTransformPara(unsigned int _IndexGroup, int _ij)
{
	if (m_BitmapGroupList.find(_IndexGroup ) !=  m_BitmapGroupList.end())
	{
		return m_BitmapGroupList.at(_IndexGroup)->GetTransformPara(_ij);
	}
	else
		return NULL;
}

float* Display2D::ZxDisplay2D::GetGraphTransformPara(unsigned int _IndexGroup, int _ij)
{
	if (m_GraphGroupList.find(_IndexGroup) != m_GraphGroupList.end())
	{
		return m_GraphGroupList.at(_IndexGroup)->GetTransformPara(_ij);
	}
	else
		return NULL;
}

void Display2D::ZxDisplay2D::ZoomBitmap(unsigned int _IndexGroup,float _Scale)
{
	if (m_BitmapGroupList.find(_IndexGroup ) !=  m_BitmapGroupList.end())
	{
		m_BitmapGroupList.at(_IndexGroup)->Zoom(_Scale);
	}
}

void Display2D::ZxDisplay2D::ZoomGraph(unsigned int _IndexGroup, float _Scale)
{
	if (m_GraphGroupList.find(_IndexGroup) != m_GraphGroupList.end())
	{
		m_GraphGroupList.at(_IndexGroup)->Zoom(_Scale);
	}
}

D2D1_POINT_2F Display2D::ZxDisplay2D::GetOrigin(unsigned int _IndexGroup)
{
	D2D1_POINT_2F point;
	if (m_BitmapGroupList.find(_IndexGroup ) !=  m_BitmapGroupList.end())
	{
		point = m_BitmapGroupList.at(_IndexGroup)->GetOrigin();
	}
	else
	{
		point.x = point.y = 0;
	}
	return point;
}

HRESULT Display2D::ZxDisplay2D::AddBitmap(int _Index, ZxImgBase* _pImage, 
	DXGI_FORMAT _PixelFormat,D2D1_ALPHA_MODE _Mode,bool _bDraw)
{
	if (m_BitmapGroupList.find(_Index) == m_BitmapGroupList.end())
	{
		m_BitmapGroupList[_Index] = new ZxDisplay2D_BitmapGroup;
		m_BitmapShowOrder.push_back(_Index);
	}
	return m_BitmapGroupList[_Index]->AddBitmap(
		m_ptrFactoty,m_pRenderTarget,_pImage,_PixelFormat,_Mode,_bDraw);
}


HRESULT Display2D::ZxDisplay2D::RefreshBitmap(int _IndexGroup, int _IndexImg, ZxImgBase* _pImage, 
	 const ZxIntRECT& _dstrRect,bool _bDraw)
{
	ZxDisplay2D_Bitmap* pImg = GetBitmap(_IndexGroup,_IndexImg);
	if (pImg == NULL)
		return S_FALSE;
	else 
	{
		pImg->SetDraw(false);
		if(!pImg->CreatBitmap(m_pRenderTarget,_pImage))
			return S_FALSE;
		pImg->SetDstRect(_dstrRect.m_Left,_dstrRect.m_Top,
			_dstrRect.m_Width,_dstrRect.m_Height);
		pImg->SetDraw(_bDraw);
	}
	return S_OK;
}


Display2D::ZxDisplay2D_Bitmap* Display2D::ZxDisplay2D::GetBitmap(int _IndexGroup, int _IndexImg)
{
	if (m_BitmapGroupList.find(_IndexGroup) != m_BitmapGroupList.end())
	{
		return m_BitmapGroupList[_IndexGroup]->GetBitmap(_IndexImg);
	}
	else
		return NULL;
}

ID2D1RenderTarget* Display2D::ZxDisplay2D::GetRenderTarget()
{
	return m_pRenderTarget;
}

void Display2D::ZxDisplay2D::SetBackGround(float _r, float _g,float _b)
{
	m_BackGroud.r = _r;
	m_BackGroud.g = _g;
	m_BackGroud.b = _b;
	m_BackGroud.a = 1;
}

void Display2D::ZxDisplay2D::SetGraphShow(int _IndexGroup, bool _bShow)
{
	m_GraphGroupList.at(_IndexGroup)->SetShow(_bShow);
}

HRESULT Display2D::ZxDisplay2D::Initialize(HWND _hWnd, ID2D1Factory* _pFactory)
{
	RECT rect;
	m_hWnd = _hWnd;
	GetClientRect(m_hWnd, &rect);
	m_Size = D2D1::SizeU(
		rect.right - rect.left,
		rect.bottom - rect.top );
	if (_pFactory)
	{
		m_ptrFactoty = _pFactory;
		return m_ptrFactoty->CreateHwndRenderTarget(
			D2D1::RenderTargetProperties(),
			D2D1::HwndRenderTargetProperties(m_hWnd,
			m_Size), (ID2D1HwndRenderTarget**)(&m_pRenderTarget)
			);
	}
	else
		return S_FALSE;
}

void Display2D::ZxDisplay2D::OnDraw()
{
	for (ZxDisplay2D_ShowOrderlist::iterator pIndex = m_BitmapShowOrder.begin();
		pIndex != m_BitmapShowOrder.end(); pIndex++)
	{
		m_BitmapGroupList[*pIndex]->DoDraw(m_pRenderTarget);
	}

	for (ZxDisplay2D_ShowOrderlist::iterator pIndex = m_GraphShowOrder.begin();
		pIndex != m_GraphShowOrder.end(); pIndex++)
	{
		m_GraphGroupList[*pIndex]->DoDraw(m_pRenderTarget);
	}

	if(m_TopBitmapGroup)
		m_TopBitmapGroup->DoDraw(m_pRenderTarget);

	for (ZxDisplay2D_ShowOrderlist::iterator pIndex = m_TopGraphShowOrder.begin();
		pIndex != m_TopGraphShowOrder.end(); pIndex++)
	{
		m_TopGraphGroup[*pIndex]->DoDraw(m_pRenderTarget);
	}
}

HRESULT Display2D::ZxDisplay2D::OnRender()
{
	m_pRenderTarget->BeginDraw();
	m_pRenderTarget->Clear(m_BackGroud);
	OnDraw();
	HRESULT RenderResult = m_pRenderTarget->EndDraw();
	return RenderResult;
}

void Display2D::ZxDisplay2D::MoveGraphBy(unsigned int _IndexGroup, float _x, float _y)
{
	if (m_GraphGroupList.find(_IndexGroup) != m_GraphGroupList.end())
	{
		m_GraphGroupList.at(_IndexGroup)->MoveBy(_x,_y);
	}
}

void Display2D::ZxDisplay2D::MoveGraphTo(unsigned int _IndexGroup, float _x, float _y)
{
	if (m_GraphGroupList.find(_IndexGroup) != m_GraphGroupList.end())
	{
		*(m_GraphGroupList.at(_IndexGroup)->GetTransformPara(31)) = - _x;
		*(m_GraphGroupList.at(_IndexGroup)->GetTransformPara(32)) = - _y;
	}
}

HRESULT Display2D::ZxDisplay2D::AddGraphy(
	int _Index, ZxDisplay2D_GraphBase* _pGraphy)
{
	if (m_GraphGroupList.find(_Index) == m_GraphGroupList.end())
	{
		m_GraphGroupList[_Index] = new ZxDisplay2D_GraphGroup(_pGraphy->GetType());
		m_GraphShowOrder.push_back(_Index);
	}
	return m_GraphGroupList[_Index]->AddGraphy(_pGraphy);
}

int Display2D::ZxDisplay2D::AddBitmapGroup(int _Index)
{
	if(m_BitmapGroupList.find(_Index) == m_BitmapGroupList.end())
		m_BitmapGroupList[_Index] = new ZxDisplay2D_BitmapGroup;
	m_BitmapShowOrder.push_back(_Index);
	return m_BitmapGroupList.size();
}

int Display2D::ZxDisplay2D::AddGraphGroup(int _Index, int _Type)
{
	if(m_GraphGroupList.find(_Index) == m_GraphGroupList.end())
		m_GraphGroupList[_Index] = new ZxDisplay2D_GraphGroup(_Type);
	m_GraphShowOrder.push_back(_Index);
	return m_GraphGroupList.size();
}

int Display2D::ZxDisplay2D::AddTopGraphGroup(int _Index, int _Type)
{
	if(m_TopGraphGroup.find(_Index) == m_GraphGroupList.end())
	{
		m_TopGraphGroup[_Index] = new ZxDisplay2D_GraphGroup(_Type);
		m_TopGraphShowOrder.push_back(_Index);
	}
	return m_TopGraphGroup.size();
}

void Display2D::ZxDisplay2D::SetGraphicTransform(
	unsigned int _IndexGroup, D2D1::Matrix3x2F& _matTranform)
{
	if (m_GraphGroupList.find(_IndexGroup) != m_GraphGroupList.end())
	{
		m_GraphGroupList[_IndexGroup]->SetGraphicTransform(_matTranform);
	}
}

void Display2D::ZxDisplay2D::SetBitmapTransform(
	unsigned int _IndexGroup, D2D1::Matrix3x2F& _matTranform)
{
	if (m_BitmapGroupList.find(_IndexGroup ) !=  m_BitmapGroupList.end())
	{
		m_BitmapGroupList.at(_IndexGroup)->SetGraphicTransform(_matTranform);
	}
}


void Display2D::ZxDisplay2D::Resize(ZxInt2DPOINT& _Size)
{
	((ID2D1HwndRenderTarget*)m_pRenderTarget)->Resize(D2D1::SizeU(_Size.m_X,_Size.m_Y));
}


int Display2D::ZxDisplay2D::GetLastBitmapGroupID(void)
{
	return *(--m_BitmapShowOrder.end());
}


int Display2D::ZxDisplay2D::GetLastGraphGroupID(void)
{
	return *(--m_GraphShowOrder.end());
}

void Display2D::ZxDisplay2D::SetBitmapInterpolationMode(int _Index,D2D1_BITMAP_INTERPOLATION_MODE _Mode)
{
	if(m_BitmapGroupList.find(_Index) != m_BitmapGroupList.end())
	{
		m_BitmapGroupList.at(_Index)->SetInterpolationMode(_Mode);
	}
}

void Display2D::ZxDisplay2D::RemoveGraph(ZxDisplay2D_GraphBase* _pGraphy)
{
	for (ZxDisplay2D_GraphGroup_Map::iterator ppGroup = m_GraphGroupList.begin();
		ppGroup != m_GraphGroupList.end(); ppGroup++)
	{
		ppGroup->second->RemoveGraph(_pGraphy);
	}
}