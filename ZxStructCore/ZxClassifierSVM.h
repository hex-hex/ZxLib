#pragma once
#include "zxclassifierbase.h"
namespace Classify
{
	class ZXSTRUCT_API ZxClassifierSVM :
		public ZxClassifierBase
	{
	public:
		ZxClassifierSVM(void);
		~ZxClassifierSVM(void);
		virtual bool Learn(ZxData& _matData);//�������Ҳ��Ҫ��float
		virtual float Classify(ZxData& _matData);//��ȷ����float��
		virtual void Clear();
	};
}
