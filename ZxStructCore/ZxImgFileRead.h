#pragma once
#include "zximgfilebase.h"
#include "ZxImgMonochrome.h"
#include "ZxImg64Bit.h"
#include "ZxMatrix.h"
using namespace Solve;

namespace Raster
{
	class ZXSTRUCT_API ZxImgFileRead :
		public ZxImgFileBase
	{
	private:
		bool Read8U(ZxImgBase* _pImg, ZxImgBase::ZxImgIOParamBase* _ReadOption);
		bool Read16U(ZxImgBase* _pImg, ZxImgBase::ZxImgIOParamBase* _ReadOption);
		bool Read32U(ZxImgBase* _pImg, ZxImgBase::ZxImgIOParamBase* _ReadOption);
	public:
		ZxImgFileRead(CRITICAL_SECTION& _Lock);
		~ZxImgFileRead(void);
		virtual bool SetFilePath(const char* _FileName);
// 		void DoQuickRead(ZxImg32Bit* _pImg, 
// 			ZxImgBase::ZxImgIOParamBase* _ReadOption); //省略种安全检测,将每通道8位的文件快速读入4通道内存图像;
// 		void DoQuickRead(ZxImg24Bit* _pImg,
// 			ZxImgBase::ZxImgIOParamBase* _ReadOption); //省略种安全检测,将每通道8位的文件快速读入3通道内存图像;
// 		void DoQuickRead(ZxImg64Bit* _pImg,
// 			ZxImgBase::ZxImgIOParamBase* _ReadOption); //省略种安全检测,将每通道16位的文件快速读入16位4通道内存图像;



		bool DoSafeRead(ZxImgBase* _pImg, ZxImgBase::ZxImgIOParamBase* _ReadOption);//有待改进
		void DoQuickReadMatrix(ZxMatrix& _Mat, const ZxInt2DPOINT& _HeaderPoint, int _Band);
		// 		void DoFullRead(ZxImgBase* _pImg);
	};

}
