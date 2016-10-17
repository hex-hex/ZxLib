#pragma once
#include <vector>
#include "ZxSolveElementFilter.h"

using namespace std;
namespace Solve
{
	typedef class ZXSTRUCT_API ZxSolveModelParamIndexElement
	{
	private:
		ZxSolveElementFilter* m_pFilter;
	public:
		double& m_ParamRef;
		double m_Accuracy;
		bool m_Engaged;
		int IsValid(ZxSolveElement* _pElement)
		{
			return m_pFilter->IsValid(_pElement);
		}
		ZxSolveModelParamIndexElement(double& _Param,ZxSolveElementFilter* _pFilter = NULL,double _Accuracy = 0);
		ZxSolveModelParamIndexElement(const ZxSolveModelParamIndexElement &_Param);
		ZxSolveModelParamIndexElement& operator = (const ZxSolveModelParamIndexElement &_Param);
		virtual ~ZxSolveModelParamIndexElement(void);
		const ZxSolveElementFilter* GetFilter();
	}*ZxSolveModelParamIndexElementPtr;
	typedef vector<ZxSolveModelParamIndexElementPtr> ZxSolveModelParamIndex;
}

