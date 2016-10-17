#pragma once
#include "ZxImg32Bit.h"
namespace Raster
{
	class ZXSTRUCT_API ZxImg64Bit :
		public ZxImgBase
	{
	public:
		ZxImg64Bit(void);
		~ZxImg64Bit(void);
		
		virtual unsigned char* GetLocation(unsigned int _X, unsigned int _Y);
		virtual bool CreateImg(unsigned int _Width,unsigned  int _Height,unsigned int _Channel);
		virtual void MakeMonochrome(int _BandID/* = 0*/);
		virtual void GetValue(ZxDN* _poutVal, double _dbX, double _dbY, int _BandID) const;//双线性线性内插取值;
		virtual void GetValue(int _X, int _Y, int _BandID, ZxDN* _poutVal) const;//无视通道号，全取出来;
		virtual void SetValue(int _X, int _Y, int _BandID, const ZxDN* _pinVal);//通道号为负值时，全写进去;
		virtual void SetBackground(ZxDN* _Val);
		virtual const unsigned int GetBand(void) const;
		virtual ZxDN GetMean() const;//当作double返回均值
		//////////////////////////////////////////////////////////////////////////
		void Convert2Display(ZxImgDisplay* _pImg);
		void DifferPixels(ZxImg64Bit* _pOutput,  int _Drection);
		static bool Convert2Real(ZxImgBase* _pInput, ZxImg64Bit* _pOutput, int _nChannel);//暂时支持转换24bit与32bit数据
	};
}