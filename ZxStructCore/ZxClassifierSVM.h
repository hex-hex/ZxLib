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
		virtual bool Learn(ZxData& _matData);//输入类别也需要是float
		virtual float Classify(ZxData& _matData);//很确定是float型
		virtual void Clear();
	};
}
