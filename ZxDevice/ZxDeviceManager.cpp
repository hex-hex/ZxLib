#include "StdAfx.h"
#include "ZxDeviceManager.h"
#include "ZxDeviceManagerUI.h"


ZxDeviceManager::ZxDeviceManager(void)
{
}


ZxDeviceManager::~ZxDeviceManager(void)
{
}


ZxDeviceManager::AutoPtrManager::AutoPtrManager()
	:m_pUIManager(NULL)
{

}

ZxDeviceManager::AutoPtrManager::~AutoPtrManager()
{
	if (m_pUIManager)
	{
		delete m_pUIManager;
	}
}


ZxDeviceManager::AutoPtrManager ZxDeviceManager::m_pManager = ZxDeviceManager::AutoPtrManager();


ZxDeviceManagerUI* ZxDeviceManager::GetManager(void)
{
	if (m_pManager.m_pUIManager == NULL)
	{
		m_pManager.m_pUIManager = new ZxDeviceManagerUI();
		m_pManager.m_pUIManager->Create(IDD_ZxDeviceManagerUI);
		m_pManager.m_pUIManager->ShowWindow(SW_SHOW);
	}
	return m_pManager.m_pUIManager;
}


Display2D::ZxDevice2D* ZxDeviceManager::GetDevice2D()
{
	return GetManager()->GetDevice2D();
}