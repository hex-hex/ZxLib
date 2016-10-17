#pragma once
#include "ZxSolveElement.h"

namespace Solve
{
	class ZXSTRUCT_API ZxSolveElementFilter
	{
	public:
		ZxSolveElementFilter(void);
		virtual ZxSolveElementFilter& operator=(const ZxSolveElementFilter& _Filter);
		virtual ~ZxSolveElementFilter(void);
		virtual int IsValid(ZxSolveElement* _pElement) = 0;
	 	virtual ZxSolveElementFilter* Clone() = 0;
	};
}

