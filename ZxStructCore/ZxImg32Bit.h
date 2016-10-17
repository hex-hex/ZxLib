#pragma once
#include "ZxImg24Bit.h"
#include "ZxColorBase.h"

namespace Raster
{
/////////////////////////四通道32位图像/////////////////////////////////////////////
	class ZXSTRUCT_API ZxImg32Bit:
		public ZxImgBase
	{
	public:
		ZxImg32Bit(void);
		~ZxImg32Bit(void);
		
		virtual unsigned char* GetLocation(unsigned int _X, unsigned int _Y);
		virtual bool CreateImg(unsigned int _Width,unsigned  int _Height,unsigned int _Channel = 4);
		virtual void MakeMonochrome(int _BandID/* = 0*/);
		virtual void GetValue(ZxDN* _poutVal, double _dbX, double _dbY, int _BandID) const;//双线性线性内插取值;
		virtual void GetValue(int _X, int _Y, int _BandID, ZxDN* _poutVal) const;//无视通道号，全取出来;
		virtual void SetValue(int _X, int _Y, int _BandID, const ZxDN* _pinVal);//通道号为负值时，全写进去;
		virtual void SetBackground(ZxDN* _Val);
		virtual ZxDN GetMean() const;//当作4通道8位图处理
		//////////////////////////////////////////////////////////////////////////
		static void StandardImport(ZxImg32Bit* _pImg32, ZxImg24Bit* _pImg24);
		static void StandardExport(ZxImg32Bit* _pImg32, ZxImg24Bit* _pImg24);
		//////////////////////////////////////////////////////////////////////////图像处理封装
		static bool WaterShed(ZxImgStandard* _pInput, ZxImg32Bit* _pOutput);
	};
	typedef ZxImg32Bit ZxImgDisplay;
}
