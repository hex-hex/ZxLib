#include "StdAfx.h"
#include "ZxTimeNode.h"


GeoReference::ZxTimeNode::ZxTimeNode(void)
	:m_UTC(0)
	,m_Year(0)
	,m_Month(0)
	,m_Day(0)
	,m_Hour(0)
	,m_Minute(0)
	,m_Second(0)
{
}


GeoReference::ZxTimeNode::~ZxTimeNode(void)
{
}


GeoReference::ZxTimeNode::ZxTimeNode(const ZxTimeNode& rhs)
	:m_UTC(rhs.m_UTC)
	,m_Year(rhs.m_Year)
	,m_Month(rhs.m_Month)
	,m_Day(rhs.m_Day)
	,m_Hour(rhs.m_Hour)
	,m_Minute(rhs.m_Minute)
	,m_Second(rhs.m_Second)
{

}

GeoReference::ZxTimeNode& GeoReference::ZxTimeNode::operator= (const ZxTimeNode& rhs)
{
	if (&rhs != this)
	{
		m_Year = rhs.m_Year;
		m_Month = rhs.m_Month;
		m_Day = rhs.m_Day;
		m_Hour = rhs.m_Hour;
		m_Minute = rhs.m_Minute;
		m_Second = rhs.m_Second;
		m_UTC = rhs.m_UTC;
	}
	return *this;
}


void GeoReference::ZxTimeNode::Reset()
{
	m_UTC = 0;
	m_Year = 0;
	m_Month = 0;
	m_Day = 0;
	m_Hour = 0;
	m_Minute = 0;
	m_Second = 0;
}

double GeoReference::ZxTimeNode::OffSet(ZxTimeNode& _TimeOff)
{
	double fOff(0);
	if(m_UTC == 0)
	{
		int DiffMin,DiffH,DiffD,DiffM,DiffY;
		fOff = _TimeOff.m_Second - m_Second;

		DiffMin = _TimeOff.m_Minute - m_Minute;
		DiffH = _TimeOff.m_Hour - m_Hour;
		DiffD = _TimeOff.m_Day - m_Day;
		DiffM = _TimeOff.m_Month - m_Month;
		DiffY = _TimeOff.m_Year - m_Year;

		if (DiffY)
		{
			DiffM += DiffY*12;
		}

		if (DiffM)
		{
			DiffD += DiffM * GetDayCount(m_Month,IsLeap(m_Year));
		}

		if (DiffD)
		{
			DiffH += DiffD * 24;
		}

		if (DiffH)
		{
			DiffM += DiffH * 60;
		}

		if (DiffMin)
		{
			fOff += DiffMin * 60;
		}
		return fOff;
	}
	else
	{
		if (_TimeOff.m_UTC == 0)
			return 0;
		else
			return _TimeOff.m_UTC - m_UTC;
	}
}

bool GeoReference::ZxTimeNode::IsLeap(int _Year)
{
	if(_Year%400 == 0 || _Year%100 != 0 && _Year % 4 == 0)
		return true;
	else
		return false;
}


int GeoReference::ZxTimeNode::GetDayCount(int _Month, bool _IsLeap)
{
	switch(_Month)
	{
	case 1:
	case 3:
	case 5:
	case 7:
	case 8:
	case 10:
	case 12:
		return 31;
		break;
	case 4:
	case 6:
	case 9:
	case 11:
		return 30;
		break;
	case 2:
		if (_IsLeap)
		{
			return 29;
		}
		else
		{
			return 28;
		}
		break;
	default:
		return 0;
	}
}
