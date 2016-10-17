#pragma once
#include "zxclassifierbase.h"

namespace Classify
{
	class ZXSTRUCT_API ZxClassifierKNearest :
		public ZxClassifierBase
	{
	private:
		int m_K;
	public:
		ZxClassifierKNearest(void);
		ZxClassifierKNearest(int _K);
		~ZxClassifierKNearest(void);
		bool Set_K(int _intK);
		virtual bool Learn(ZxData& _matData);
		virtual float Classify(ZxData& _matData);
		virtual void Clear();
	};
}

