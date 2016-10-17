#include "StdAfx.h"
#include "ZxImgMonochrome.h"


Raster::ZxImgMonochrome::ZxImgMonochrome(void)
{
	m_Channel = 1;
}


Raster::ZxImgMonochrome::~ZxImgMonochrome(void)
{
}

unsigned char* Raster::ZxImgMonochrome::GetLocation(unsigned int _X, unsigned int _Y)
{
	return GetImgData() + GetWidthStep() * _Y + _X;
}

bool Raster::ZxImgMonochrome::CreateImg(unsigned int _Width,unsigned  int _Height,unsigned int _BitPerPixel/* = 8*/)
{
	return ZxImgBase::CreateImg(_Width, _Height, 8);
}

void Raster::ZxImgMonochrome::MakeMonochrome(int _BandID/* = 0*/)
{
	//本来就是黑白的;
}

void Raster::ZxImgMonochrome::GetValue(ZxDN* _poutVal, double _dbX, double _dbY, int _BandID) const
{
	if(_dbX < 0 || _dbX > GetWidth() 
		|| _dbY < 0 || _dbY > GetHeight())
	{
		memset(_poutVal,0,sizeof(ZxDN));
		return;
	}

	int locX[2];
	int locY[2];
	double Val[4];

	locX[0] = static_cast<int>(floor(_dbX));
	locX[1] = static_cast<int>(ceil(_dbX));
	_dbX -= locX[0];
	locY[0] = static_cast<int>(floor(_dbY));
	locY[1] = static_cast<int>(ceil(_dbY));
	_dbY -= locY[0];

	Val[0] = *(GetImgData() + locY[0] * GetWidthStep() + locX[0]);
	Val[1] = *(GetImgData() + locY[0] * GetWidthStep() + locX[1]);
	Val[2] = *(GetImgData() + locY[1] * GetWidthStep() + locX[1]);
	Val[3] = *(GetImgData() + locY[1] * GetWidthStep() + locX[0]);
	_poutVal->m_ExportDouble[0] = 
		((Val[0] * (1 - _dbX) * ( 1 - _dbY) +
		Val[1] * _dbX * (1 - _dbY) +
		Val[2] * _dbX * _dbY +
		Val[3] * (1 - _dbX) * _dbY));
}

void Raster::ZxImgMonochrome::GetValue(int _X, int _Y, int _BandID, ZxDN* _poutVal) const
{
	memcpy_s(_poutVal->m_ExportByte, sizeof(char), GetImgData() + _Y * GetWidthStep() + _X, sizeof(char));
}

void Raster::ZxImgMonochrome::SetValue(int _X, int _Y, int _BandID, const ZxDN* _pinVal)
{
	memcpy_s(GetImgData() + _Y * GetWidthStep() + _X, sizeof(char), _pinVal->m_ExportByte, sizeof(char));
}

void Raster::ZxImgMonochrome::SetBackground(ZxDN* _Val)
{
	if (_Val == NULL)
		return;
	else
		memset(GetImgData(), _Val->m_ExportByte[0], GetMemSize() * sizeof(unsigned char));
}

Raster::ZxDN Raster::ZxImgMonochrome::GetMean() const
{
	cv::Mat current_img(m_Height,m_Width,CV_8UC1,m_imgData,m_Widthstep);
	cv::Scalar mean_color = cv::mean(current_img);
	ZxDN mean_dn;
	mean_dn.m_ExportByte[0] = static_cast<int>(mean_color[0]);
	return mean_dn;
}