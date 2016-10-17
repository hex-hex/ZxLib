#include "StdAfx.h"
#include "ZxDisplay2D_GraphCharacters.h"

IDWriteFactory* Display2D::ZxDisplay2D_GraphCharacters::ms_pDWriteFactory = NULL;
unsigned int Display2D::ZxDisplay2D_GraphCharacters::ms_RefpDWriteFactory = 0;

Display2D::ZxDisplay2D_GraphCharacters::ZxDisplay2D_GraphCharacters(void)
	:m_wcsContent(NULL)
	,m_nStrLen(0)
	,m_nMemStrLen(0)
{
	m_Type = ZXDISPLAY2D_GRAPH_POINT;
	if (!ms_pDWriteFactory)
	{
		DWriteCreateFactory(
			DWRITE_FACTORY_TYPE_SHARED,
			__uuidof(IDWriteFactory),
			reinterpret_cast<IUnknown**>(&ms_pDWriteFactory));
	}
	ms_RefpDWriteFactory ++;

	ms_pDWriteFactory->CreateTextFormat(L"Caliri",
		NULL,
		DWRITE_FONT_WEIGHT_REGULAR,
		DWRITE_FONT_STYLE_NORMAL,
		DWRITE_FONT_STRETCH_NORMAL,
		12.0f,
		L"en-us",
		&m_pWriteTextFormat);
}


Display2D::ZxDisplay2D_GraphCharacters::~ZxDisplay2D_GraphCharacters(void)
{
	ms_RefpDWriteFactory--;
	SAFE_RELEASE(m_pWriteTextFormat);
	if (!ms_RefpDWriteFactory)
		SAFE_RELEASE(ms_pDWriteFactory);
}


void Display2D::ZxDisplay2D_GraphCharacters::DoDraw(ID2D1RenderTarget* _pRenderTarget)
{
	if (m_bDraw)
	{
		_pRenderTarget->DrawText(m_wcsContent,m_nStrLen,m_pWriteTextFormat,m_WriteRegion,m_pFillBrush);
	}
}

void Display2D::ZxDisplay2D_GraphCharacters::RefreshFeature(Zx2DPoint& _Point)
{
	m_WriteRegion.left = m_Location.m_X + 7;
	m_WriteRegion.top = m_Location.m_Y + 7;
	m_WriteRegion.right = m_WriteRegion.left + m_nStrLen * 7;
	m_WriteRegion.bottom = m_WriteRegion.top + 15;
}

void Display2D::ZxDisplay2D_GraphCharacters::SetString(const char* _strContent)
{
	int nLen = strlen(_strContent) + 1;
	m_nStrLen = MultiByteToWideChar(CP_ACP, 0, _strContent, nLen, NULL, 0);
	if (m_wcsContent && m_nStrLen > m_nMemStrLen)
	{
		delete[] m_wcsContent;
		m_wcsContent = new WCHAR[m_nStrLen];
		m_nMemStrLen = m_nStrLen;
	}
	else if(m_wcsContent == NULL)
	{
		m_wcsContent = new WCHAR[m_nStrLen];
		m_nMemStrLen = m_nStrLen;
	}
	MultiByteToWideChar(CP_ACP, 0, _strContent, nLen, m_wcsContent, m_nStrLen); 
}