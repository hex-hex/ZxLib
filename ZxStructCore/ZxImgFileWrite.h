#pragma once
#include "ZxImgFileBase.h"
#include "ZxImg64Bit.h"
#include "ZxMatrix.h"
using namespace Solve;

namespace Raster
{
	class ZXSTRUCT_API ZxImgFileWrite :
		public ZxImgFileBase
	{
	private:
		bool Write8U(ZxImgBase* _pImg, ZxImgBase::ZxImgIOParamBase* _WiriteOption);
		bool Write16U(ZxImgBase* _pImg, ZxImgBase::ZxImgIOParamBase* _WiriteOption);
		bool Write32U(ZxImgBase* _pImg, ZxImgBase::ZxImgIOParamBase* _WiriteOption);
	/*protected:*/
		void* m_pDriver;
		void SetTransPara(const double*);
	public:
		ZxImgFileWrite(CRITICAL_SECTION& _Lock);
		~ZxImgFileWrite(void);
		virtual bool SetFilePath(const char* _FileName);
		bool CreateByte(int _Height, int _Width, int _BandCount);
		bool CreateUInteger16(int _Height, int _Width, int _BandCount);
		bool CreateUInteger32(int _Height, int _Width, int _BandCount);
		bool CreateDouble(int _Height, int _Width, int _BandCount);
		bool SetProjection(const double* _pTransformParam, const ZxGeoRef& _GeoRef);

		bool DoSafeWrite(ZxImgBase* _pImg,
			ZxImgBase::ZxImgIOParamBase* _WiriteOption);//�д��Ľ�;
		bool DoFullWrite(ZxImgBase* _pImg);//��ûд��;
		void DoQuickWriteMatrix(ZxMatrix& _Mat, const ZxInt2DPOINT& _HeaderPoint, int _Band);

// 		void DoQuickWrite(ZxImg32Bit* _pImg, 
// 			ZxImgBase::ZxImgIOParamBase* _WiriteOption); //ʡ�԰�ȫ���,��4ͨ���ڴ�ͼ����ٴ���8λͼ���ļ�;
// 		void DoQuickWrite(ZxImg24Bit* _pImg, 
// 			ZxImgBase::ZxImgIOParamBase* _WiriteOption); //ʡ�԰�ȫ���,��3ͨ���ڴ�ͼ����ٴ���8λͼ���ļ�;
// 		void DoQuickWrite(ZxImg64Bit* _pImg,
// 			ZxImgBase::ZxImgIOParamBase* _WiriteOption); //ʡ���ְ�ȫ���,��ÿͨ��16λ���ļ����ٴ���16λ4ͨ���ڴ�ͼ��;

	};
}
