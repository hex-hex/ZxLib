#include "StdAfx.h"
#include "ZxRectangle.h"
using namespace Geometry;


ZxIntRECT::ZxIntRECT()
	:m_Angle(0)
{

}

ZxIntRECT::ZxIntRECT(int _Left, int _Top, int _Width, int _Height, float _Angle)
	:m_Height(_Height)
	,m_Left(_Left)
	,m_Top(_Top)
	,m_Width(_Width)
	,m_Angle(_Angle)
{

}

ZxIntRECT ZxIntRECT::QuickGetMinRect(const ZxInt2DPoints& _PointSet)
{
	cv::Mat PointSet(1, _PointSet.size(), CV_32SC2, (void*)(&(_PointSet[0])), static_cast<int>(_PointSet.size() * 8));
	return *((ZxIntRECT*)(&cv::minAreaRect(PointSet)));
}

ZxIntRECT::operator ZxIntImgRECT()
{
	ZxIntImgRECT rect;
	rect.m_Left = 0 > m_Left? 0 : m_Left;
	rect.m_Top = 0 > m_Top? 0 : m_Top;
	rect.m_Right = m_Width + m_Left;
	rect.m_Right = 0 > rect.m_Right ? 0 : rect.m_Right;
	rect.m_Bottom = m_Top + m_Height;
	rect.m_Bottom = 0 > rect.m_Bottom ? 0 : rect.m_Bottom;
	return rect;
}

void ZxIntRECT::SetOff(const ZxInt2DPOINT& _point, ZxIntRECT _rect)
{
	_rect.m_Left += _point.m_X;
	_rect.m_Top += _point.m_Y;
}

bool ZxIntRECT::IsInside(int _x, int _y)
{
	if (_x < m_Left || _x > m_Left + m_Width || _y < m_Top || _y > m_Top + m_Height)
		return false;
	else
		return true;
}

ZxRectangle::ZxRectangle(void)
{
}

ZxRectangle::~ZxRectangle(void)
{
}

ZxIntImgRECT::ZxIntImgRECT()
	:m_Bottom(0)
	,m_Left(UINT_MAX)
	,m_Right(0)
	,m_Top(UINT_MAX)
{

}

ZxIntImgRECT::operator ZxIntRECT()
{
	ZxIntRECT rect;
	rect.m_Left = m_Left;
	rect.m_Top = m_Top;
	rect.m_Width = m_Right - m_Left;
	rect.m_Height = m_Bottom - m_Top;
	return rect;
}


ZxRectangle::ZxRectangle(double _Left, double _Top, double _Right, double _Bottom)
	:m_Left(_Left)
	,m_Top(_Top)
	,m_Right(_Right)
	,m_Bottom(_Bottom)
{

}


