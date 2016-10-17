#pragma once
namespace Display2D
{
	class ZXDEVICE_API ZxDisplay2D_GraphicLineBase	//表明其有线划特性
	{
	protected:
		ID2D1Brush* m_pLineBrush;
		bool m_bManagedBrush;
		float m_strokeWidth;
		float m_strokeShowWidth;
		ID2D1StrokeStyle* m_pStyle;
		bool m_bManagedStyle;
	public:
		ZxDisplay2D_GraphicLineBase(void);
		~ZxDisplay2D_GraphicLineBase(void);
		void SetStrokeWidth(float _strokeWidth);
		bool SetLineBrush(ID2D1Brush* _pBrush, bool _bManaged = false);//_bManaged表示之后其是否会自行释放内存
	};
}

