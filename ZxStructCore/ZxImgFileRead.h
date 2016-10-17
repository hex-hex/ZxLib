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
// 			ZxImgBase::ZxImgIOParamBase* _ReadOption); //ʡ���ְ�ȫ���,��ÿͨ��8λ���ļ����ٶ���4ͨ���ڴ�ͼ��;
// 		void DoQuickRead(ZxImg24Bit* _pImg,
// 			ZxImgBase::ZxImgIOParamBase* _ReadOption); //ʡ���ְ�ȫ���,��ÿͨ��8λ���ļ����ٶ���3ͨ���ڴ�ͼ��;
// 		void DoQuickRead(ZxImg64Bit* _pImg,
// 			ZxImgBase::ZxImgIOParamBase* _ReadOption); //ʡ���ְ�ȫ���,��ÿͨ��16λ���ļ����ٶ���16λ4ͨ���ڴ�ͼ��;



		bool DoSafeRead(ZxImgBase* _pImg, ZxImgBase::ZxImgIOParamBase* _ReadOption);//�д��Ľ�
		void DoQuickReadMatrix(ZxMatrix& _Mat, const ZxInt2DPOINT& _HeaderPoint, int _Band);
		// 		void DoFullRead(ZxImgBase* _pImg);
	};

}
