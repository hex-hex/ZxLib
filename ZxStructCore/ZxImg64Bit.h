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
		virtual void GetValue(ZxDN* _poutVal, double _dbX, double _dbY, int _BandID) const;//˫���������ڲ�ȡֵ;
		virtual void GetValue(int _X, int _Y, int _BandID, ZxDN* _poutVal) const;//����ͨ���ţ�ȫȡ����;
		virtual void SetValue(int _X, int _Y, int _BandID, const ZxDN* _pinVal);//ͨ����Ϊ��ֵʱ��ȫд��ȥ;
		virtual void SetBackground(ZxDN* _Val);
		virtual const unsigned int GetBand(void) const;
		virtual ZxDN GetMean() const;//����double���ؾ�ֵ
		//////////////////////////////////////////////////////////////////////////
		void Convert2Display(ZxImgDisplay* _pImg);
		void DifferPixels(ZxImg64Bit* _pOutput,  int _Drection);
		static bool Convert2Real(ZxImgBase* _pInput, ZxImg64Bit* _pOutput, int _nChannel);//��ʱ֧��ת��24bit��32bit����
	};
}