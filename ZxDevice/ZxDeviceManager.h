#pragma once
#include "ZxDevice2D.h"
class ZxDeviceManagerUI;

class ZXDEVICE_API ZxDeviceManager
{
private:
	class AutoPtrManager
	{
	public:
		AutoPtrManager();
		~AutoPtrManager();
		ZxDeviceManagerUI* m_pUIManager;
	};
	static AutoPtrManager m_pManager;
	static ZxDeviceManagerUI* GetManager(void);
public:
	ZxDeviceManager(void);
	~ZxDeviceManager(void);
	static Display2D::ZxDevice2D* GetDevice2D();
};

