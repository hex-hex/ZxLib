#pragma once

namespace Display2D
{
	class ZXDEVICE_API ZxDisplay2D_GraphicSolidBase	//����������
	{
	protected:
		ID2D1Brush* m_pFillBrush;
		bool m_bManagedBrush;
	public:
		ZxDisplay2D_GraphicSolidBase(void);
		~ZxDisplay2D_GraphicSolidBase(void);
		bool SetFillBrush(ID2D1Brush* _pBrush, bool _bManaged = false);//_bManaged��ʾ֮�����Ƿ�������ͷ��ڴ�
	};

}
