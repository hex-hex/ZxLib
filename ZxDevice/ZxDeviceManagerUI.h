#pragma once
#include "resource.h"
#include "ZxDevice2D.h"
// ZxDeviceManagerUI dialog

class ZxDeviceManagerUI : public CDialogEx
{
	DECLARE_DYNAMIC(ZxDeviceManagerUI)

public:
	ZxDeviceManagerUI(CWnd* pParent = NULL);   // standard constructor
	virtual ~ZxDeviceManagerUI();

// Dialog Data
	enum { IDD = IDD_ZxDeviceManagerUI };

private:
	const CSize m_Size;
	Display2D::ZxDevice2D* m_pDiplayDevice;

	RECT m_DeskRect;
	bool m_bLBDown;
	bool m_bAboutDown;
	bool m_bOptionDown;
	CPoint m_pointLBDown;
	BOOL m_bMouseTrack;
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	virtual BOOL OnInitDialog();
	Display2D::ZxDevice2D* GetDevice2D();
	afx_msg void OnMouseLeave();
};
