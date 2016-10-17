#include "StdAfx.h"
#include "ZxProgress.h"


Experience::ZxProgress::ZxProgress(void)
	:m_Value(0)
{
	InitializeCriticalSection(&m_Lock);
}


Experience::ZxProgress::~ZxProgress(void)
{
	DeleteCriticalSection(&m_Lock);
}

void Experience::ZxProgress::Reset()
{
	EnterCriticalSection(&m_Lock);
	m_Value = 0;
	LeaveCriticalSection(&m_Lock);
}

double Experience::ZxProgress::GetVal(void)
{
	double dbValue;
	EnterCriticalSection(&m_Lock);
	dbValue = m_Value;
	LeaveCriticalSection(&m_Lock);
	return dbValue;
}


void Experience::ZxProgress::SetVal(double _Val)
{
	EnterCriticalSection(&m_Lock);
	if(m_Value < _Val)
		m_Value = _Val;
	LeaveCriticalSection(&m_Lock);
}


void Experience::ZxProgress::AddVal(double _Val)
{
	EnterCriticalSection(&m_Lock);
	m_Value += _Val;
	LeaveCriticalSection(&m_Lock);
}


void Experience::ZxProgress::MulVal(double _Val)
{
	EnterCriticalSection(&m_Lock);
	m_Value *= _Val;
	LeaveCriticalSection(&m_Lock);
}
