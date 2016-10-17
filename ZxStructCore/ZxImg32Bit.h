#pragma once
#include "ZxImg24Bit.h"
#include "ZxColorBase.h"

namespace Raster
{
/////////////////////////��ͨ��32λͼ��/////////////////////////////////////////////
	class ZXSTRUCT_API ZxImg32Bit:
		public ZxImgBase
	{
	public:
		ZxImg32Bit(void);
		~ZxImg32Bit(void);
		
		virtual unsigned char* GetLocation(unsigned int _X, unsigned int _Y);
		virtual bool CreateImg(unsigned int _Width,unsigned  int _Height,unsigned int _Channel = 4);
		virtual void MakeMonochrome(int _BandID/* = 0*/);
		virtual void GetValue(ZxDN* _poutVal, double _dbX, double _dbY, int _BandID) const;//˫���������ڲ�ȡֵ;
		virtual void GetValue(int _X, int _Y, int _BandID, ZxDN* _poutVal) const;//����ͨ���ţ�ȫȡ����;
		virtual void SetValue(int _X, int _Y, int _BandID, const ZxDN* _pinVal);//ͨ����Ϊ��ֵʱ��ȫд��ȥ;
		virtual void SetBackground(ZxDN* _Val);
		virtual ZxDN GetMean() const;//����4ͨ��8λͼ����
		//////////////////////////////////////////////////////////////////////////
		static void StandardImport(ZxImg32Bit* _pImg32, ZxImg24Bit* _pImg24);
		static void StandardExport(ZxImg32Bit* _pImg32, ZxImg24Bit* _pImg24);
		//////////////////////////////////////////////////////////////////////////ͼ�����װ
		static bool WaterShed(ZxImgStandard* _pInput, ZxImg32Bit* _pOutput);
	};
	typedef ZxImg32Bit ZxImgDisplay;
}
