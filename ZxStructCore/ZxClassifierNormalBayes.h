#pragma once
#include "zxclassifierbase.h"

namespace Classify
{
	class ZXSTRUCT_API ZxClassifierNormalBayes :
		public ZxClassifierBase
	{
	public:
		ZxClassifierNormalBayes(void);
		~ZxClassifierNormalBayes(void);
		virtual bool Learn(ZxData& _matData);
		virtual float Classify(ZxData& _matData);
		virtual void Clear();
	};
}
