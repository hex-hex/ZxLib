#include "StdAfx.h"
#include "Zx3DPoint.h"


Geometry::Zx3DPoint::Zx3DPoint()
{

}

Geometry::Zx3DPoint::Zx3DPoint(double _XVal, double _YVal, double _ZVal)
	:m_X(_XVal)
	,m_Y(_YVal)
	,m_Z(_ZVal)

{
}

Geometry::Zx3DPoint::Zx3DPoint(double _InitVal)
	:m_X(_InitVal)
	,m_Y(_InitVal)
	,m_Z(_InitVal)
{
}

Geometry::Zx3DPoint::Zx3DPoint(Zx2DPoint& _point)
	:m_X(_point.m_X)
	,m_Y(_point.m_Y)
	,m_Z(0)
{

}

void Geometry::Zx3DPoint::CopyTo2D(Geometry::Zx2DPoint& _2Dpoint)
{
	_2Dpoint.m_X = m_X;
	_2Dpoint.m_Y = m_Y;
}

void Geometry::Zx3DPoint::CopyFrom2D(Geometry::Zx2DPoint& _2Dpoint)
{
	m_X = _2Dpoint.m_X;
	m_Y = _2Dpoint.m_Y;
	m_Z = 0;
}

Geometry::Zx2DPoint Geometry::Zx3DPoint::Get2D()
{
	return Zx2DPoint(m_X,m_Y);
}

bool Geometry::Zx3DPoint::Xmorethan(Zx3DPoint& _point1, Zx3DPoint& _point2)
{
	return _point1.m_X > _point2.m_X;
}

bool Geometry::Zx3DPoint::pXmorethan(Zx3DPoint* _point1,Zx3DPoint* _point2)
{
	return _point1->m_X > _point2->m_X;
}


const bool Geometry::Zx3DPoint::operator ==(const Zx3DPoint& _point)
{
	return (m_X == _point.m_X 
		&& m_Y == _point.m_Y 
		&& m_Z == _point.m_Z);
}

double Geometry::Zx3DPoint::GetGeoMean() const
{
	return sqrt(m_X * m_X + m_Y * m_Y + m_Z * m_Z);
}


Geometry::Zx3DPoint Geometry::Zx3DPoint::operator - (Geometry::Zx3DPoint& _point)
{
	Zx3DPoint point;
	point.m_X = m_X - _point.m_X;
	point.m_Y = m_Y - _point.m_Y;
	point.m_Z = m_Z - _point.m_Z;
	return point;
}


Geometry::Zx3DPoint Geometry::Zx3DPoint::operator + (Geometry::Zx3DPoint& _point)
{
	Zx3DPoint point;
	point.m_X = m_X + _point.m_X;
	point.m_Y = m_Y + _point.m_Y;
	point.m_Z = m_Z + _point.m_Z;
	return point;
}

Geometry::Zx3DPoint Geometry::Zx3DPoint::operator * (Geometry::Zx3DPoint& _point)
{
	Zx3DPoint point;
	point.m_X = m_X * _point.m_X;
	point.m_Y = m_Y * _point.m_Y;
	point.m_Z = m_Z * _point.m_Z;
	return point;
}


Geometry::Zx3DPoint Geometry::Zx3DPoint::operator / (Geometry::Zx3DPoint& _point)
{
	Zx3DPoint point;
	point.m_X = m_X / _point.m_X;
	point.m_Y = m_Y / _point.m_Y;
	point.m_Z = m_Z / _point.m_Z;
	return point;
}

Geometry::Zx3DPoint Geometry::Zx3DPoint::operator * (int _Val)
{
	Zx3DPoint point;
	point.m_X = m_X * _Val;
	point.m_Y = m_Y * _Val;
	point.m_Z = m_Z * _Val;
	return point;
}


Geometry::Zx3DPoint Geometry::Zx3DPoint::operator / (int _Val)
{
	Zx3DPoint point;
	point.m_X = m_X / _Val;
	point.m_Y = m_Y / _Val;
	point.m_Z = m_Z / _Val;
	return point;
}

void Geometry::Zx3DPoint::AffineTrans(Geometry::Zx3DPoint& _point,const double* _pPara)
{
	Zx2DPoint point;
	point.m_X =_pPara[0] + _point.m_X * _pPara[1] + _point.m_Y * _pPara[2];
	point.m_Y =_pPara[3] + _point.m_X * _pPara[4] + _point.m_Y * _pPara[5];
	_point.m_X = point.m_X;
	_point.m_Y = point.m_Y;
}

/*
Geometry::Zx3DPoint& Geometry::Zx3DPoint::operator=(const Zx3DPoint& _Point)
{
	if (&_Point != this)
		memcpy(&m_X, &(_Point.m_X), sizeof(double) * 3);
	return *this;
}*/
