#include "StdAfx.h"
#include "ZxSolveModelParamBase.h"


Solve::ZxSolveModelParamBase::ZxSolveModelParamBase(unsigned int _ParamCount)
	:m_ParamCount(_ParamCount)
	,m_bReady(false)
{
	m_ParamIndex.resize(_ParamCount);
	for (unsigned int i = 0; i != m_ParamCount; i++)
	{
		m_ParamIndex[i] = NULL;
	}
	const char* strName = _T("Base Model");
	strcpy_s(m_ParamName,256,strName);
}


Solve::ZxSolveModelParamBase::~ZxSolveModelParamBase(void)
{
	for (unsigned int i = 0; i != m_ParamCount; i++)
	{
		if (m_ParamIndex[i])
			delete m_ParamIndex.at(i);
	}
	m_ParamIndex.clear();
}


unsigned int Solve::ZxSolveModelParamBase::GetEngagedCount() const
{
	if (m_ParamIndex[0] != NULL)
	{
		int iCount(0);
		for (unsigned int i = 0; i != m_ParamCount; i++)
		{
			if (m_ParamIndex[i]->m_Engaged)
				iCount++;
		}
		return iCount;
	}
	else
		return 0;
}


void Solve::ZxSolveModelParamBase::ResetParamCount(unsigned int _ParamCount)
{
	m_ParamCount = _ParamCount;
	if (m_ParamIndex.size())
	{
		for (unsigned int i = 0; i != m_ParamCount; i++)
		{
			delete m_ParamIndex.at(i);
		}	
	}
	m_ParamIndex.resize(_ParamCount);
}


Solve::ZxSolveModelParamBase::ZxSolveModelParamBase(const ZxSolveModelParamBase& _Params)
	:m_ParamCount(_Params.m_ParamCount)
	,m_bReady(_Params.m_bReady)
{
	strcpy_s(m_ParamName,256,_Params.m_ParamName);
	m_ParamIndex.resize(_Params.m_ParamCount);
	for (int i = 0; i != m_ParamCount; i++)
	{
		m_ParamIndex[i] = new ZxSolveModelParamIndexElement(*(m_ParamIndex[i]));
	}
}


Solve::ZxSolveModelParamBase& Solve::ZxSolveModelParamBase::operator= (const ZxSolveModelParamBase& _Params)
{
	if (&_Params != this)
	{
		m_ParamCount = _Params.m_ParamCount;
		m_bReady = _Params.m_bReady;
		strcpy_s(m_ParamName,256,_Params.m_ParamName);

		m_ParamIndex.resize(_Params.m_ParamCount);
		for (int i = 0; i != m_ParamCount; i++)
		{
			m_ParamIndex[i] = new ZxSolveModelParamIndexElement(*(m_ParamIndex[i]));
		}
	}
	return *this;
}

bool Solve::ZxSolveModelParamBase::IsReady() const
{
	return m_bReady;
}

unsigned int Solve::ZxSolveModelParamBase::GetParamCount() const
{
	return m_ParamCount;
}


void Solve::ZxSolveModelParamBase::SetReady(bool _bReady)
{
	m_bReady = _bReady;
}


void Solve::ZxSolveModelParamBase::ExportParams(const char* _ParamsFileName)
{
	//Do nothing
}

bool Solve::ZxSolveModelParamBase::ImportParams(const char* _ParamsFileName)
{
	//Do nothing
	return false;
}

Solve::ZxSolveModelParamIndexElementPtr Solve::ZxSolveModelParamBase::operator[](unsigned int _Index) const
{
	if (_Index < m_ParamCount)
		return m_ParamIndex.at(_Index);
	else
		return NULL;
}