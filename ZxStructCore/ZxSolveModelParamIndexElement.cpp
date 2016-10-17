#include "StdAfx.h"
#include "ZxSolveModelParamIndexElement.h"


Solve::ZxSolveModelParamIndexElement::ZxSolveModelParamIndexElement(double& _Param,ZxSolveElementFilter* _pFilter /*= NULL*/,double _Accuracy/* = 0*/)
	:m_ParamRef(_Param)
	,m_Accuracy(_Accuracy)
	,m_Engaged(false)
	,m_pFilter(_pFilter)
{

}

Solve::ZxSolveModelParamIndexElement::ZxSolveModelParamIndexElement(const ZxSolveModelParamIndexElement &_Param)
	:m_Accuracy(_Param.m_Accuracy)
	,m_ParamRef(_Param.m_ParamRef)
	,m_Engaged(_Param.m_Engaged)
{
	if(_Param.m_pFilter)
		m_pFilter = _Param.m_pFilter->Clone();
}


Solve::ZxSolveModelParamIndexElement& Solve::ZxSolveModelParamIndexElement::operator = (const ZxSolveModelParamIndexElement &_Param)
{
	if (&_Param != this)
	{
		m_ParamRef = _Param.m_ParamRef;
		m_Accuracy = _Param.m_Accuracy;
		m_Engaged = _Param.m_Engaged;
		if(_Param.m_pFilter)
			m_pFilter = _Param.m_pFilter->Clone();
	}
	return *this;
}


Solve::ZxSolveModelParamIndexElement::~ZxSolveModelParamIndexElement(void)
{
	if (m_pFilter)
	{
		delete m_pFilter;
	}
}

const Solve::ZxSolveElementFilter* Solve::ZxSolveModelParamIndexElement::GetFilter()
{
	return m_pFilter;
}