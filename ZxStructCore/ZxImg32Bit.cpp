#include "StdAfx.h"
#include "ZxImg32Bit.h"


Raster::ZxImg32Bit::ZxImg32Bit(void)
{
	m_Channel = 4;
}



Raster::ZxImg32Bit::~ZxImg32Bit(void)
{

}

void Raster::ZxImg32Bit::SetBackground(ZxDN* _Val)
{
	if (_Val == NULL)
		return;
	else
		memset(GetImgData(),_Val->m_ExportInt32[0],GetMemSize() * sizeof(unsigned char));
}

bool Raster::ZxImg32Bit::CreateImg(unsigned int _Width,unsigned  int _Height,unsigned int _Channel)
{
	m_Channel = _Channel;
	return ZxImgBase::CreateImg(_Width,_Height,32);
}



void Raster::ZxImg32Bit::MakeMonochrome(int _BandID/* = 0*/)
{
	if(_BandID < 0 || _BandID > 3)
		return;

	for (int i = 0; i != GetHeight();i++)
	{
		for(int j = 0; j != GetWidth(); j++)
		{
			for (int k = 0; k < 4; k++)
			{
				memcpy(GetImgData() + i * GetWidthStep() + j * 4 + k ,GetImgData() + i * GetWidthStep() + j * 4 + _BandID, 1);
			}
		}
	}
}

unsigned char* Raster::ZxImg32Bit::GetLocation(unsigned int _X, unsigned int _Y)
{
	return GetImgData() + GetWidthStep() * _Y + _X * 4;
}

void Raster::ZxImg32Bit::GetValue(ZxDN* _poutVal, double _dbX, double _dbY, int _BandID) const 
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

	Val[0] = *(GetImgData() + locY[0] * GetWidthStep() + locX[0] * 4 + _BandID);
	Val[1] = *(GetImgData() + locY[0] * GetWidthStep() + locX[1] * 4 + _BandID);
	Val[2] = *(GetImgData() + locY[1] * GetWidthStep() + locX[1] * 4 + _BandID);
	Val[3] = *(GetImgData() + locY[1] * GetWidthStep() + locX[0] * 4 + _BandID);
	_poutVal->m_ExportByte[0] = static_cast<unsigned char>
		((Val[0] * (1 - _dbX) * ( 1 - _dbY) +
		Val[1] * _dbX * (1 - _dbY) +
		Val[2] * _dbX * _dbY +
		Val[3] * (1 - _dbX) * _dbY));
}


void Raster::ZxImg32Bit::GetValue(int _X, int _Y, int _BandID, ZxDN* _poutVal) const
{
	memcpy_s(_poutVal->m_ExportByte,sizeof(char) * 4,GetImgData() + _Y * GetWidthStep() + _X * 4,sizeof(char) * 4);
}


void Raster::ZxImg32Bit::SetValue(int _X, int _Y, int _BandID, const ZxDN* _pinVal)
{
	if (_BandID < 0)
	{
		memcpy_s(GetImgData() + _Y * GetWidthStep() + _X * 4, sizeof(char) * 4, _pinVal->m_ExportByte, sizeof(char) * 4);
	}
	else
	{
		memcpy_s(GetImgData() + _Y * GetWidthStep() + _X * 4 + _BandID,sizeof(char),_pinVal->m_ExportByte,sizeof(char));
	}
}

Raster::ZxDN Raster::ZxImg32Bit::GetMean() const
{
	cv::Mat current_img(m_Height,m_Width,CV_8UC4,m_imgData,m_Widthstep);
	cv::Scalar mean_color = cv::mean(current_img);
	ZxDN mean_dn;
	mean_dn.m_ExportByte[0] = static_cast<int>(mean_color[0]);
	mean_dn.m_ExportByte[1] = static_cast<int>(mean_color[1]);
	mean_dn.m_ExportByte[2] = static_cast<int>(mean_color[2]);
	mean_dn.m_ExportByte[3] = static_cast<int>(mean_color[3]);
	return mean_dn;
}

void Raster::ZxImg32Bit::StandardImport(ZxImg32Bit* _pImg32, ZxImg24Bit* _pImg24)
{
	_pImg32->CreateImg(_pImg24->GetWidth(),_pImg24->GetHeight());
	unsigned char* pSrc = _pImg24->GetImgData();
	unsigned char* pDst = _pImg32->GetImgData();
	for (int i = 0 ; i != _pImg24->GetWidth(); i++)
	{
		for(int j = 0; j != _pImg24->GetHeight(); j++)
		{
			pSrc += 3;
			pDst += 4;
			memcpy(pDst,pSrc,3);
		}
	}
}


void Raster::ZxImg32Bit::StandardExport(ZxImg32Bit* _pImg32, ZxImg24Bit* _pImg24)
{
	_pImg24->CreateImg(_pImg32->GetWidth(),_pImg32->GetHeight());
	unsigned char* pSrc = _pImg32->GetImgData();
	unsigned char* pDst = _pImg24->GetImgData();
	for (int i = 0 ; i != _pImg24->GetWidth(); i++)
	{
		for(int j = 0; j != _pImg24->GetHeight(); j++)
		{
			pSrc += 4;
			pDst += 3;
			memcpy(pDst,pSrc,3);
		}
	}
}

bool Raster::ZxImg32Bit::WaterShed(ZxImgStandard* _pInput, ZxImg32Bit* _pOutput)
{
	if (!_pOutput->CreateImg(_pInput->GetWidth(),_pInput->GetHeight()))
		return false;
	cv::Mat Input(_pInput->GetHeight(),	_pInput->GetWidth(), CV_8UC3, _pInput->GetImgData(), _pInput->GetWidthStep());
	cv::Mat Output(_pOutput->GetHeight(), _pOutput->GetWidth(), CV_32SC1, _pOutput->GetImgData(), _pOutput->GetWidthStep());
	cv::watershed(Input,Output);
	return true;
}