#include "StdAfx.h"
#include "Zx2DPoint.h"

Geometry::Zx2DPoint::Zx2DPoint()
{

}

Geometry::Zx2DPoint::Zx2DPoint(double _XVal, double _YVal)
	:m_X(_XVal)
	,m_Y(_YVal)
{
}

Geometry::Zx2DPoint::Zx2DPoint(double _InitVal)
	:m_X(_InitVal)
	,m_Y(_InitVal)
{
}

Geometry::Zx2DPoint Geometry::Zx2DPoint::operator + (Zx2DPoint& _point)
{
	Zx2DPoint point;
	point.m_X = m_X + _point.m_X;
	point.m_Y = m_Y + _point.m_Y;
	return point;
}

Geometry::Zx2DPoint Geometry::Zx2DPoint::operator - (Zx2DPoint& _point)
{
	Zx2DPoint point;
	point.m_X = m_X - _point.m_X;
	point.m_Y = m_Y - _point.m_Y;
	return point;
}

Geometry::Zx2DPoint Geometry::Zx2DPoint::operator * (Zx2DPoint& _point)
{
	Zx2DPoint point;
	point.m_X = m_X * _point.m_X;
	point.m_Y = m_Y * _point.m_Y;
	return point;
}

Geometry::Zx2DPoint Geometry::Zx2DPoint::operator / (Zx2DPoint& _point)
{
	Zx2DPoint point;
	point.m_X = m_X / _point.m_X;
	point.m_Y = m_Y / _point.m_Y;
	return point;
}

Geometry::Zx2DPoint Geometry::Zx2DPoint::operator * (int _val)
{
	Zx2DPoint point;
	point.m_X = m_X * _val;
	point.m_Y = m_Y * _val;
	return point;
}

Geometry::Zx2DPoint Geometry::Zx2DPoint::operator * (double _val)
{
	Zx2DPoint point;
	point.m_X = m_X * _val;
	point.m_Y = m_Y * _val;
	return point;
}

Geometry::Zx2DPoint Geometry::Zx2DPoint::operator / (int _val)
{
	Zx2DPoint point;
	point.m_X = m_X / _val;
	point.m_Y = m_Y / _val;
	return point;
}

double Geometry::Zx2DPoint::GetGeoMean() const
{
	return sqrt(m_X* m_X + m_Y * m_Y);
}

bool Geometry::Zx2DPoint::operator ==(const Zx2DPoint& _point)
{
	return _point.m_X == m_X && _point.m_Y == m_Y;
}


double Geometry::Zx2DPoint::GetDistance(Zx2DPoint& _point)
{
	return sqrt((m_X - _point.m_X)* (m_X - _point.m_X) + (m_Y - _point.m_Y) * (m_Y - _point.m_Y));
}

void Geometry::Zx2DPoint::AffineTrans(Zx2DPoint& _point,const double* _pPara)
{
	Zx2DPoint point;
	point.m_X =_pPara[0] + _point.m_X * _pPara[1] + _point.m_Y * _pPara[2];
	point.m_Y =_pPara[3] + _point.m_X * _pPara[4] + _point.m_Y * _pPara[5];
	_point.m_X = point.m_X;
	_point.m_Y = point.m_Y;
}

Geometry::Zx2DPoint& Geometry::Zx2DPoint::operator +=(const Zx2DPoint& _point)
{
	this->m_X += _point.m_X;
	this->m_Y += _point.m_Y;
	return *this;
}

Geometry::Zx2DPoint& Geometry::Zx2DPoint::operator +=(const ZxInt2DPOINT& _point)
{
	this->m_X += _point.m_X;
	this->m_Y += _point.m_Y;
	return *this;
}
