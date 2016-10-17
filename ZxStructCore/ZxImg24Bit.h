#pragma once
#include "zximgbase.h"

namespace Raster
{
	class ZXSTRUCT_API ZxImg24Bit :
		public ZxImgBase
	{

	public:
		ZxImg24Bit(void);
		~ZxImg24Bit(void);

		virtual unsigned char* GetLocation(unsigned int _X, unsigned int _Y);
		virtual bool CreateImg(unsigned int _Width,unsigned  int _Height,unsigned int _BitPerPixel = 24);
		virtual void MakeMonochrome(int _BandID/* = 0*/);
		virtual void GetValue(ZxDN* _poutVal, double _dbX, double _dbY, int _BandID) const;
		virtual void GetValue(int _X, int _Y, int _BandID, ZxDN* _poutVal) const;//����ͨ���ţ���ͨ��ȫȡ����;
		virtual void SetValue(int _X, int _Y, int _BandID, const ZxDN* _pinVal);//ͨ����Ϊ��ֵʱ����ͨ��ȫд��ȥ;
		virtual ZxDN GetMean() const;
		virtual void SetBackground(ZxDN* _Val);//�����û�ɫ��������Byte[0]��Ч;
//////////////////////////////////////////////////////////////////////////ͼ�����װ
		static bool ConvertColor(ZxImg24Bit* _pInput, ZxColorType _TypeInput, 
			ZxImg24Bit* _pOutput, ZxColorType _TypeOutput);
		static bool MedianFilter(ZxImg24Bit* _pInput, ZxImg24Bit* _pOutput, int _Range);
		static bool MeanShiftFilter(ZxImg24Bit* _pInput, ZxImg24Bit* _pOutput,  double _sp, double _sr);
		static bool BilateralFilter(ZxImg24Bit* _pInput, ZxImg24Bit* _pOutput, int _d,
			double _sigmaColor, double _sigmaSpace, int _borderType = 4);//ֱ�ӷ�װOPENCV
		static bool Laplacian(ZxImg24Bit* _pInput, ZxImg24Bit* _pOutput);
		static void Mean(double* _pMean, ZxImg24Bit* _pInput);//_pMean������double[4];
		static void DrawRotatedRectangle(ZxImg24Bit* _pInput, const ZxIntRECT& _Rectangle);
	};

	typedef ZxImg24Bit ZxImgStandard;
}

