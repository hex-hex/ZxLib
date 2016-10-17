#pragma once
#include "Resource.h"

// ZxAboutWindow dialog

class ZxAboutWindow : public CDialogEx
{
	DECLARE_DYNAMIC(ZxAboutWindow)
private:
	RECT m_DeskRect;
	const CSize m_Size;
public:
	ZxAboutWindow(CWnd* pParent = NULL);   // standard constructor
	virtual ~ZxAboutWindow();

// Dialog Data
	enum { IDD = IDD_ZXABOUTWINDOW };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
};
