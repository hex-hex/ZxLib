#include "StdAfx.h"
#include "ZxSolveModelBase.h"


Solve::ZxSolveModelBase::ZxSolveModelBase(void)
	:m_pParam(NULL)
{
	const char* strName = _T("Base Model");
	strcpy_s(m_ModelName,256,strName);
}


Solve::ZxSolveModelBase::~ZxSolveModelBase(void)
{
}

bool Solve::ZxSolveModelBase::IsReady() const
{
	return m_pParam->IsReady();
}


bool Solve::ZxSolveModelBase::SetStarter(ZxSolveModelParamBase* _pStarter)
{
	if (!_pStarter)
		return false;
	else if(strcmp(_pStarter->m_ParamName,m_ModelName))
		return false;
	m_pParam = _pStarter;
	return true;
}

