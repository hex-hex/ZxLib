#pragma once

namespace Display2D
{
	class ZXDEVICE_API ZxDisplay2D_GraphicSolidBase	//表明其可填充
	{
	protected:
		ID2D1Brush* m_pFillBrush;
		bool m_bManagedBrush;
	public:
		ZxDisplay2D_GraphicSolidBase(void);
		~ZxDisplay2D_GraphicSolidBase(void);
		bool SetFillBrush(ID2D1Brush* _pBrush, bool _bManaged = false);//_bManaged表示之后其是否会自行释放内存
	};

}
