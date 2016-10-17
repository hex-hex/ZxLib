#include "StdAfx.h"
#include "ZxSolveElement.h"


Solve::ZxSolveElement::ZxSolveElement(void)
{
}


Solve::ZxSolveElement::~ZxSolveElement(void)
{
}

bool Solve::ZxSolveElement::PtrResidualLess(const ZxSolveElement* _plhs, const ZxSolveElement* _prhs)
{
	return _plhs->GetMeanResidual() < _prhs->GetMeanResidual();
}


bool Solve::ZxSolveElement::ResidualLess(const ZxSolveElement& _lhs, const ZxSolveElement& _rhs)
{
	return _lhs.GetMeanResidual() < _rhs.GetMeanResidual();
}

bool Solve::ZxSolveElement::PtrResidualMore(const ZxSolveElement* _plhs, const ZxSolveElement* _prhs)
{
	return _plhs->GetMeanResidual() > _prhs->GetMeanResidual();
}


bool Solve::ZxSolveElement::ResidualMore(const ZxSolveElement& _lhs, const ZxSolveElement& _rhs)
{
	return _lhs.GetMeanResidual() > _rhs.GetMeanResidual();
}