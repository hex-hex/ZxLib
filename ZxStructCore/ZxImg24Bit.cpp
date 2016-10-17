#include "StdAfx.h"
#include "ZxImg24Bit.h"


Raster::ZxImg24Bit::ZxImg24Bit(void)
{
	m_Channel = 3;
}


Raster::ZxImg24Bit::~ZxImg24Bit(void)
{
}


bool Raster::ZxImg24Bit::CreateImg(unsigned int _Width,unsigned  int _Height,unsigned int _BitPerPixel/* = 24*/)
{
	return ZxImgBase::CreateImg(_Width,_Height,24);
}


void Raster::ZxImg24Bit::MakeMonochrome(int _BandID/* = 0*/)
{
	if(_BandID == 0 || _BandID == 1 || _BandID == 2)
	{
		for (int i = 0; i != GetHeight();i++)
		{
			for(int j = 0; j != GetWidth(); j++)
			{
				for (int k = 0; k < 3; k++)
				{
					memcpy(GetImgData() + i * GetWidthStep() + j * 3 + k ,GetImgData() + i * GetWidthStep() + j * 3 + _BandID, 1);
				}
			}
		}
	}
}


unsigned char* Raster::ZxImg24Bit::GetLocation(unsigned int _X, unsigned int _Y)
{
	return GetImgData() + GetWidthStep() * _Y + _X * 3;
}


void Raster::ZxImg24Bit::GetValue(ZxDN* _poutVal, double _dbX, double _dbY, int _BandID) const
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

	Val[0] = *(GetImgData() + locY[0] * GetWidthStep() + locX[0] * 3 + _BandID);
	Val[1] = *(GetImgData() + locY[0] * GetWidthStep() + locX[1] * 3 + _BandID);
	Val[2] = *(GetImgData() + locY[1] * GetWidthStep() + locX[1] * 3 + _BandID);
	Val[3] = *(GetImgData() + locY[1] * GetWidthStep() + locX[0] * 3 + _BandID);
	_poutVal->m_ExportDouble[0] = 
		((Val[0] * (1 - _dbX) * ( 1 - _dbY) +
		Val[1] * _dbX * (1 - _dbY) +
		Val[2] * _dbX * _dbY +
		Val[3] * (1 - _dbX) * _dbY));
}


void Raster::ZxImg24Bit::GetValue(int _X, int _Y, int _BandID, ZxDN* _poutVal) const
{
	memcpy_s(_poutVal->m_ExportByte,sizeof(char) * 3,GetImgData() + _Y * GetWidthStep() + _X * 3,sizeof(char) * 3);
}


void Raster::ZxImg24Bit::SetValue(int _X, int _Y, int _BandID, const ZxDN* _pinVal)
{
	if (_BandID < 0)
	{
		memcpy_s(GetImgData() + _Y * GetWidthStep() + _X * 3,sizeof(char) * 3,_pinVal->m_ExportByte,sizeof(char) * 3);
	}
	else
	{
		assert(_BandID < 4);
		memcpy_s(GetImgData() + _Y * GetWidthStep() + _X * 3 + _BandID, sizeof(char), _pinVal->m_ExportByte,sizeof(char));
	}
}


void Raster::ZxImg24Bit::SetBackground(ZxDN* _Val)
{
	if (_Val == NULL)
		return;
	else
		memset(GetImgData(),_Val->m_ExportByte[0],GetMemSize() * sizeof(unsigned char));
}

Raster::ZxDN Raster::ZxImg24Bit::GetMean() const
{
	cv::Mat current_img(m_Height,m_Width,CV_8UC3,m_imgData,m_Widthstep);
	cv::Scalar mean_color = cv::mean(current_img);
	ZxDN mean_dn;
	mean_dn.m_ExportByte[0] = static_cast<int>(mean_color[0]);
	mean_dn.m_ExportByte[1] = static_cast<int>(mean_color[1]);
	mean_dn.m_ExportByte[2] = static_cast<int>(mean_color[2]);
	return mean_dn;
}


bool Raster::ZxImg24Bit::ConvertColor(ZxImg24Bit* _pInput, ZxColorType _TypeInput, 
	ZxImg24Bit* _pOutput, ZxColorType _TypeOutput)
{
	if(!_pOutput->CreateImg(_pInput->GetWidth(),_pInput->GetHeight()))
		return false;

	cv::Mat Input(_pInput->GetHeight(),	_pInput->GetWidth(), CV_8UC3, _pInput->GetImgData(), _pInput->GetWidthStep());
	cv::Mat Output(_pOutput->GetHeight(), _pOutput->GetWidth(), CV_8UC3, _pOutput->GetImgData(), _pInput->GetWidthStep());

	if (_TypeInput == ZxRGB)
	{
		if (_TypeOutput == ZxHSV)
		{
			cv::cvtColor(Input,Output,CV_BGR2HSV);
		}
		else if (_TypeOutput == ZxXYZ)
		{
			cv::cvtColor(Input,Output,CV_BGR2XYZ);
		}
		else if (_TypeOutput == ZxLab)
		{
			cv::cvtColor(Input,Output,CV_BGR2Lab);
		}
		else if (_TypeOutput == ZxLuv)
		{
			cv::cvtColor(Input,Output,CV_BGR2Luv);
		}
		else if (_TypeOutput == ZxRGB)
		{
			memcpy_s(_pOutput->GetImgData(),_pInput->GetWidthStep()*_pInput->GetHeight(),_pInput->GetImgData(),_pOutput->GetWidthStep()*_pOutput->GetHeight());
		}
	}
	else if (_TypeOutput == ZxRGB)
	{
		if (_TypeInput == ZxHSV)
		{
			cv::cvtColor(Input,Output,CV_HSV2BGR);
		}
		else if(_TypeInput = ZxLab)
		{
			cv::cvtColor(Input,Output,CV_Lab2BGR);
		}
		else if(_TypeInput == ZxLuv)
		{
			cv::cvtColor(Input,Output,CV_Luv2BGR);
		}
	}
	return true;
}

bool Raster::ZxImg24Bit::MedianFilter(ZxImg24Bit* _pInput, ZxImg24Bit* _pOutput, int _Range)
{
	if (!_pOutput->CreateImg(_pInput->GetWidth(),_pInput->GetHeight()))
		return false;
	if (!(_Range % 2))
		_Range += 1;
	
	cv::Mat Input(_pInput->GetHeight(),	_pInput->GetWidth(), CV_8UC3, _pInput->GetImgData(), _pInput->GetWidthStep());
	cv::Mat Output(_pOutput->GetHeight(), _pOutput->GetWidth(), CV_8UC3, _pOutput->GetImgData(), _pOutput->GetWidthStep());
	cv::medianBlur(Input,Output,_Range);
	return true;
}


bool Raster::ZxImg24Bit::MeanShiftFilter(ZxImg24Bit* _pInput, ZxImg24Bit* _pOutput,  double _sp, double _sr)
{
	if (!_pOutput->CreateImg(_pInput->GetWidth(),_pInput->GetHeight()))
		return false;
	cv::Mat Input(_pInput->GetHeight(),	_pInput->GetWidth(), CV_8UC3, _pInput->GetImgData(), _pInput->GetWidthStep());
	cv::Mat Output(_pOutput->GetHeight(), _pOutput->GetWidth(), CV_8UC3, _pOutput->GetImgData(), _pOutput->GetWidthStep());
	cv::pyrMeanShiftFiltering(Input, Output, _sp, _sr);
	return true;
}


bool Raster::ZxImg24Bit::BilateralFilter(ZxImg24Bit* _pInput, ZxImg24Bit* _pOutput, int _d,
	double _sigmaColor, double _sigmaSpace, int _borderType)
{
	if (!_pOutput->CreateImg(_pInput->GetWidth(),_pInput->GetHeight()))
		return false;
	cv::Mat Input(_pInput->GetHeight(),	_pInput->GetWidth(), CV_8UC3, _pInput->GetImgData(), _pInput->GetWidthStep());
	cv::Mat Output(_pOutput->GetHeight(), _pOutput->GetWidth(), CV_8UC3, _pOutput->GetImgData(), _pOutput->GetWidthStep());
	cv::bilateralFilter(Input,Output,_d,_sigmaColor,_sigmaSpace,_borderType);
	return true;
}


bool Raster::ZxImg24Bit::Laplacian(ZxImg24Bit* _pInput, ZxImg24Bit* _pOutput)
{
	if (!_pOutput->CreateImg(_pInput->GetWidth(),_pInput->GetHeight()))
		return false;
	cv::Mat Input(_pInput->GetHeight(),	_pInput->GetWidth(), CV_8UC3, _pInput->GetImgData(), _pInput->GetWidthStep());
	cv::Mat Output(_pOutput->GetHeight(), _pOutput->GetWidth(), CV_8UC3, _pOutput->GetImgData(), _pOutput->GetWidthStep());
	cv::Laplacian(Input,Output,24);
	return true;
}


void Raster::ZxImg24Bit::Mean(double* _pMean, ZxImg24Bit* _pInput)
{
	cv::Mat Input(_pInput->GetHeight(),	_pInput->GetWidth(), CV_8UC3, _pInput->GetImgData(), _pInput->GetWidthStep());
	*((CvScalar*)(_pMean)) = cv::mean(Input);
	
}

void Raster::ZxImg24Bit::DrawRotatedRectangle(ZxImg24Bit* _pInput, const ZxIntRECT& _Rectangle)
{
	cv::Mat Input(_pInput->GetHeight(),	_pInput->GetWidth(), CV_8UC3, _pInput->GetImgData(), _pInput->GetWidthStep());
	cv::RotatedRect rRect(*((CvBox2D32f*)(&_Rectangle)));
	cv::Point2f vertices[4];
	rRect.points(vertices);
	for (int i = 0; i < 4; i++)
		cv::line(Input, vertices[i], vertices[(i+1)%4], cv::Scalar(0,255,0));
}