// ZxAboutWindow.cpp : implementation file
//

#include "stdafx.h"
#include "ZxAboutWindow.h"
#include "afxdialogex.h"


// ZxAboutWindow dialog

IMPLEMENT_DYNAMIC(ZxAboutWindow, CDialogEx)

ZxAboutWindow::ZxAboutWindow(CWnd* pParent /*=NULL*/)
	: CDialogEx(ZxAboutWindow::IDD, pParent)
	, m_Size(555,177)
{
	SystemParametersInfo(SPI_GETWORKAREA,NULL,&m_DeskRect,0);
}

ZxAboutWindow::~ZxAboutWindow()
{
}

void ZxAboutWindow::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(ZxAboutWindow, CDialogEx)
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()


// ZxAboutWindow message handlers


BOOL ZxAboutWindow::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  Add extra initialization here
	SetBackgroundImage(IDB_BITMAP_ZEBRASYS_ABOUT);
	
	SetWindowPos(&wndTopMost,
		m_DeskRect.left + (m_DeskRect.right - m_DeskRect.left - m_Size.cx)/2,
		m_DeskRect.top + (m_DeskRect.bottom - m_DeskRect.top - m_Size.cy)/2,
		m_Size.cx,m_Size.cy,SWP_SHOWWINDOW);
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}


void ZxAboutWindow::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default

	//CDialogEx::OnLButtonDown(nFlags, point);
	CDialogEx::OnOK();
}
