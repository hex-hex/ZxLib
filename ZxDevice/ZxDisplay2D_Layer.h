#pragma once

namespace Display2D
{
	class ZxDisplay2D_DisplayObject
	{
	protected:
		bool m_bDraw;
	public:
		ZxDisplay2D_DisplayObject();
		virtual ~ZxDisplay2D_DisplayObject();
		void SetDraw(bool _bDraw = true);
	};

	class ZxDisplay2D_Layer
	{
	protected:
		bool m_bShow;
		D2D1::Matrix3x2F m_matDisplayTransform;
	public:
		ZxDisplay2D_Layer(void);
		virtual ~ZxDisplay2D_Layer(void);
		void MoveBy(float _x, float _y);
		void SetGraphicTransform(D2D1::Matrix3x2F& _matTranform);
		float* GetTransformPara(int _ij);
		void SetShow(bool _bShow);
		virtual bool DoDraw(ID2D1RenderTarget* _pRenderTarget);
	};

}

