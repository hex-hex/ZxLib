#pragma once
#include "ZxData.h"

namespace Classify
{
	class ZXSTRUCT_API ZxClassifierBase
	{
	protected:
		void* m_pData;
	public:
		ZxClassifierBase(void);
		~ZxClassifierBase(void);
		virtual bool Learn(ZxData& _matData) = 0;//输入类别也需要是float
		virtual float Classify(ZxData& _matData) = 0;//很确定是float型
		virtual void Clear() = 0;
	};
}
