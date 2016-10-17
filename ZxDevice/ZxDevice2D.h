#pragma once
#include "ZxDisplay2D.h"
#include <vector>
using namespace std;

namespace Display2D
{
	typedef vector<ZxDisplay2D*> ZxDisplay2D_List;
	class ZXDEVICE_API ZxDevice2D
	{
	protected:
		ID2D1Factory *m_pD2DFactory;
		ZxDisplay2D_List m_DisplayList;
	public:
		ZxDevice2D(void);
		~ZxDevice2D(void);
		bool Initialize(bool _bMultiThread = false);
		void Clear(void);
		bool AddDisplay(HWND _hWnd);
		void DoDraw(void);
		ZxDisplay2D* GetDisplay(int _Index);
	};
}
