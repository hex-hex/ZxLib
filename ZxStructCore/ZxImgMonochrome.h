#pragma once
#include "zximgbase.h"

namespace Raster
{
	class ZXSTRUCT_API ZxImgMonochrome :
		public ZxImgBase
	{
	public:
		ZxImgMonochrome(void);
		~ZxImgMonochrome(void);

		virtual unsigned char* GetLocation(unsigned int _X, unsigned int _Y);
		virtual bool CreateImg(unsigned int _Width,unsigned  int _Height,unsigned int _BitPerPixel = 8);
		virtual void MakeMonochrome(int _BandID/* = 0*/);//已经是黑白的了
		virtual void GetValue(ZxDN* _poutVal, double _dbX, double _dbY, int _BandID) const;
		virtual void GetValue(int _X, int _Y, int _BandID, ZxDN* _poutVal) const;//无论怎样只有一个通道;
		virtual void SetValue(int _X, int _Y, int _BandID, const ZxDN* _pinVal);//无论怎样只有一个通道;
		virtual void SetBackground(ZxDN* _Val);
		virtual ZxDN GetMean() const;//
//////////////////////////////////////////////////////////////////////////
	};

}
