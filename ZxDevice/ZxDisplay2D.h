#pragma once
#include "ZxDisplay2D_BitmapGroup.h"
#include "ZxDisplay2D_GraphGroup.h"
#include <map>
#include <list>
using namespace std;
namespace Display2D
{
	typedef map<int,ZxDisplay2D_BitmapGroup*> ZxDisplay2D_BitmapGroup_Map;
	typedef map<int,ZxDisplay2D_GraphGroup*> ZxDisplay2D_GraphGroup_Map;
	typedef list<int> ZxDisplay2D_ShowOrderlist;

	class ZXDEVICE_API ZxDisplay2D
	{
	protected:
		D2D1_COLOR_F m_BackGroud;

		ID2D1Factory* m_ptrFactoty;
		ZxDisplay2D_BitmapGroup_Map m_BitmapGroupList;
		ZxDisplay2D_ShowOrderlist m_BitmapShowOrder;
		ZxDisplay2D_GraphGroup_Map m_GraphGroupList;
		ZxDisplay2D_ShowOrderlist m_GraphShowOrder;

		ZxDisplay2D_BitmapGroup* m_TopBitmapGroup;
		ZxDisplay2D_ShowOrderlist* m_TopBitmapShowOrder;
		ZxDisplay2D_GraphGroup_Map m_TopGraphGroup;
		ZxDisplay2D_ShowOrderlist m_TopGraphShowOrder;

		ID2D1RenderTarget *m_pRenderTarget;
		D2D1_POINT_2F m_Origin;
		struct
		{
			HWND m_hWnd;
			D2D1_SIZE_U m_Size;
		};
		virtual void OnDraw();
		void ClearAllTopLayer();
	public:
		ZxDisplay2D(void);
		~ZxDisplay2D(void);
//////////////////////////////////////////////////////////////////////////
		virtual HRESULT Initialize(HWND _hWnd, ID2D1Factory* _pFactory);
		virtual ID2D1RenderTarget* GetRenderTarget();
		void SetBackGround(float _r = 0, float _g = 0,float _b = 0);
		virtual HRESULT OnRender();
		virtual void Resize(ZxInt2DPOINT& _Size);
		virtual int AddTopGraphGroup(int _Index, int _Type);//初始化后立刻设置,一般只控制显示，不彻底清理
//////////////////////////////////////////////////////////////////////////
		int GetNewGroupIndex(bool _bImg, bool _Top = false);
		void ClearAllBitmapGroup();
		void ClearAllGraphGroup();

		void ClearBitmapGroup(unsigned int _Index);
		void ClearGraphGroup(unsigned int _Index);

		virtual int AddBitmapGroup(int _Index);
		virtual int AddGraphGroup(int _Index, int _Type);

		int GetLastBitmapGroupID(void);
		int GetLastGraphGroupID(void);

		virtual HRESULT AddBitmap(int _Index, ZxImgBase* _pImage, 
			DXGI_FORMAT _PixelFormat,D2D1_ALPHA_MODE _Mode,bool _bDraw);

		virtual HRESULT RefreshBitmap(int _IndexGroup, int _IndexImg,
			ZxImgBase* _pImage, const ZxIntRECT& _dstrRect, bool _bDraw);
		
		virtual HRESULT AddGraphy(int _Index, ZxDisplay2D_GraphBase* _pGraphy);
		void SetBitmapInterpolationMode(int,D2D1_BITMAP_INTERPOLATION_MODE);

		void RemoveGraph(ZxDisplay2D_GraphBase* _pGraphy);
		void SetGraphShow(int _IndexGroup, bool _bShow);

		virtual ZxDisplay2D_Bitmap* GetBitmap(int _IndexGroup, int _IndexImg);
		virtual D2D1_POINT_2F GetOrigin(unsigned int _IndexGroup);

		float* GetBitmapTransformPara(unsigned int _IndexGroup, int _ij);
		float* GetGraphTransformPara(unsigned int _IndexGroup, int _ij);
		void SetGraphicTransform(unsigned int _IndexGroup, D2D1::Matrix3x2F& _matTranform);
		void SetBitmapTransform(unsigned int _IndexGroup, D2D1::Matrix3x2F& _matTranform);

		virtual void ZoomBitmap(unsigned int _IndexGroup, float _Scale);
		virtual void ZoomGraph(unsigned int _IndexGroup, float _Scale);

		virtual void MoveBitmapBy(unsigned int _IndexGroup, float _x, float _y);
		virtual void MoveBitmapTo(unsigned int _IndexGroup, float _x, float _y);
		virtual void MoveGraphBy(unsigned int _IndexGroup, float _x, float _y);
		virtual void MoveGraphTo(unsigned int _IndexGroup, float _x, float _y);
	};
}

