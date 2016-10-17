#include "StdAfx.h"
#include "ZxTimeLog.h"


Experience::ZxTimeLog::ZxTimeLog(void)
	:m_dbClick(0)
{
}


Experience::ZxTimeLog::~ZxTimeLog(void)
{
}

void Experience::ZxTimeLog::BeginClick()
{
	m_dbClick = GetTickCount();
}


double Experience::ZxTimeLog::LogPoint()
{
	double dbPoint(GetTickCount() - m_dbClick);
	m_dbClick = GetTickCount();
	return dbPoint;
}