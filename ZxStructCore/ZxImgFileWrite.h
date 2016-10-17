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
			ZxImgBase::ZxImgIOParamBase* _WiriteOption);//有待改进;
		bool DoFullWrite(ZxImgBase* _pImg);//还没写完;
		void DoQuickWriteMatrix(ZxMatrix& _Mat, const ZxInt2DPOINT& _HeaderPoint, int _Band);

// 		void DoQuickWrite(ZxImg32Bit* _pImg, 
// 			ZxImgBase::ZxImgIOParamBase* _WiriteOption); //省略安全检测,将4通道内存图像快速存入8位图像文件;
// 		void DoQuickWrite(ZxImg24Bit* _pImg, 
// 			ZxImgBase::ZxImgIOParamBase* _WiriteOption); //省略安全检测,将3通道内存图像快速存入8位图像文件;
// 		void DoQuickWrite(ZxImg64Bit* _pImg,
// 			ZxImgBase::ZxImgIOParamBase* _WiriteOption); //省略种安全检测,将每通道16位的文件快速存入16位4通道内存图像;

	};
}
