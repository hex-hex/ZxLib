// ZxDeviceManagerUI.cpp : implementation file
//

#include "stdafx.h"
#include "ZxDeviceManagerUI.h"
#include "afxdialogex.h"
#include "ZxAboutWindow.h"

#define DRAW_TIMER_ID 663499

// ZxDeviceManagerUI dialog

IMPLEMENT_DYNAMIC(ZxDeviceManagerUI, CDialogEx)

ZxDeviceManagerUI::ZxDeviceManagerUI(CWnd* pParent /*=NULL*/)
	: CDialogEx(ZxDeviceManagerUI::IDD, pParent)
	, m_pDiplayDevice(NULL)
	, m_Size(169,27)
	, m_bLBDown(false)
	, m_bMouseTrack(TRUE)
	, m_bAboutDown(false)
	, m_bOptionDown(false)
{
	SystemParametersInfo(SPI_GETWORKAREA,NULL,&m_DeskRect,0);
	m_DeskRect.bottom -= 1;
}

ZxDeviceManagerUI::~ZxDeviceManagerUI()
{
	if (m_pDiplayDevice)
	{
		delete m_pDiplayDevice;
	}
}

void ZxDeviceManagerUI::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(ZxDeviceManagerUI, CDialogEx)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_TIMER()
	ON_WM_MOUSELEAVE()
END_MESSAGE_MAP()


// ZxDeviceManagerUI message handlers


void ZxDeviceManagerUI::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	if (point.y > 2 && point.y < 24)
	{
		if (point.x > 145 && point.x < 166)
		{
			m_bAboutDown = true;
		}
		else if (point.x > 120 && point.x < 142)
		{
			m_bOptionDown = true;
		}
	}

	m_pointLBDown = point;
	m_bLBDown = true;
	SetCapture();
	CDialogEx::OnLButtonDown(nFlags, point);
}


void ZxDeviceManagerUI::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	if (m_bAboutDown)
	{
		if (point.y > 2 && point.y < 24 && point.x > 145 && point.x < 166)
		{
			ZxAboutWindow AboutDlg;
			AboutDlg.DoModal();
		}
	}
	else if (m_bOptionDown)
	{
		if (point.y > 2 && point.y < point.x > 120 && point.x < 142)
		{
/////////////////////////////////////////////////////////////////////ÏìÓ¦µã»÷OPTION°´¼ü/////
		}
	}
	m_bLBDown = false;
	m_bOptionDown = false;
	m_bAboutDown = false;
	ReleaseCapture();
	CDialogEx::OnLButtonUp(nFlags, point);
}


void ZxDeviceManagerUI::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	if (m_bMouseTrack)
	{
		TRACKMOUSEEVENT csTME;
		csTME.cbSize = sizeof(csTME);
		csTME.dwFlags = TME_LEAVE|TME_HOVER;
		csTME.hwndTrack = m_hWnd;
		csTME.dwHoverTime = 10;
		::_TrackMouseEvent(&csTME);
		m_bMouseTrack=FALSE;
	}

	if (m_bAboutDown || m_bOptionDown)
	{
	}
	else if(m_bLBDown)
	{
		RECT BarRect;
		CPoint vector = point - m_pointLBDown;
		GetWindowRect(&BarRect);
		vector.x += BarRect.left;
		if(vector.x + m_Size.cx > m_DeskRect.right)
			vector.x = m_DeskRect.right - m_Size.cx;
		if (vector.x < 0) 
			vector.x = 0;

		vector.y += BarRect.top;
		if (vector.y + m_Size.cy > m_DeskRect.bottom)
			vector.y = m_DeskRect.bottom - m_Size.cy;
		if (vector.y < 0)
			vector.y = 0;
		this->MoveWindow(vector.x,vector.y,m_Size.cx,m_Size.cy);
	}
	else
	{
		if (point.y > 2 && point.y < 24)
		{
			if (point.x > 145 && point.x < 166)
			{
				SetBackgroundImage(IDB_BITMAP_MANAGERGUI_A);
			}
			else if (point.x > 120 && point.x < 142)
			{
				SetBackgroundImage(IDB_BITMAP_MANAGERGUI_O);
			}
			else
			{
				SetBackgroundImage(IDB_BITMAP_MANAGERGUI);
			}
		}
		else
		{
			SetBackgroundImage(IDB_BITMAP_MANAGERGUI);
		}
	}

	CDialogEx::OnMouseMove(nFlags, point);
}


void ZxDeviceManagerUI::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: Add your message handler code here and/or call default
	switch (nIDEvent)
	{
	case  DRAW_TIMER_ID:
		m_pDiplayDevice->DoDraw();
		break;
	}
	CDialogEx::OnTimer(nIDEvent);
}


BOOL ZxDeviceManagerUI::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  Add extra initialization here
	m_pDiplayDevice = new Display2D::ZxDevice2D;
	m_pDiplayDevice->Initialize(true);
	
	SetTimer(DRAW_TIMER_ID, 20, NULL);
	SetBackgroundImage(IDB_BITMAP_MANAGERGUI);
	int loc = m_DeskRect.right - 32 - m_Size.cx;
	SetWindowPos(&wndTopMost,loc,32,m_Size.cx,m_Size.cy,SWP_SHOWWINDOW);
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}


Display2D::ZxDevice2D* ZxDeviceManagerUI::GetDevice2D()
{
	return m_pDiplayDevice;
}


void ZxDeviceManagerUI::OnMouseLeave()
{
	// TODO: Add your message handler code here and/or call default
	SetBackgroundImage(IDB_BITMAP_MANAGERGUI);
	m_bMouseTrack = TRUE;
	CDialogEx::OnMouseLeave();
}
