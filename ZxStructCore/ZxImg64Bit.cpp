#include "StdAfx.h"
#include "ZxImg64Bit.h"


Raster::ZxImg64Bit::ZxImg64Bit(void)
{
	m_Channel = 4;
}


Raster::ZxImg64Bit::~ZxImg64Bit(void)
{
}


unsigned char* Raster::ZxImg64Bit::GetLocation(unsigned int _X, unsigned int _Y)
{
	return GetImgData() + GetWidthStep() * _Y + _X * 8;
}

bool Raster::ZxImg64Bit::CreateImg(unsigned int _Width,unsigned  int _Height,unsigned int _Channel)
{
	if(_Channel == 4 || _Channel == 1 || _Channel == 2)
	{
		m_Channel = _Channel;
		return ZxImgBase::CreateImg(_Width,_Height,64);
	}
	else
		return false;
}

void Raster::ZxImg64Bit::MakeMonochrome(int _BandID/* = 0*/)
{

}

void Raster::ZxImg64Bit::GetValue(ZxDN* _poutVal, double _dbX, double _dbY, int _BandID) const
{
	
}

void Raster::ZxImg64Bit::GetValue(int _X, int _Y, int _BandID, ZxDN* _poutVal) const
{
	memcpy_s(_poutVal->m_ExportDouble,sizeof(char) * 8,GetImgData() + _Y * GetWidthStep() + _X * 8,sizeof(char) * 8);
}

void Raster::ZxImg64Bit::SetValue(int _X, int _Y, int _BandID, const ZxDN* _pinVal)
{
	if (_BandID > m_Channel)
	{
		return;
	}
	else if (_BandID < 0)
	{
		memcpy_s(GetImgData() + _Y * GetWidthStep() + (_X << 3), sizeof(char) << 3 , _pinVal->m_ExportByte, sizeof(char) << 3);
	}
	else
	{
		memcpy_s(GetImgData() + _Y * GetWidthStep() + (_X << 3) + _BandID, sizeof(char) << 3 / m_Channel, _pinVal->m_ExportByte,sizeof(char) << 3 / m_Channel);
	}
}

void Raster::ZxImg64Bit::SetBackground(ZxDN* _Val)
{

}

const unsigned int Raster::ZxImg64Bit::GetBand(void) const
{
	return m_Channel;
}

Raster::ZxDN Raster::ZxImg64Bit::GetMean() const
{
	cv::Mat current_img(m_Height,m_Width,CV_64FC1,m_imgData,m_Widthstep);
	cv::Scalar mean_color = cv::mean(current_img);
	ZxDN mean_dn;
	mean_dn.m_ExportDouble[0] = mean_color[0];
	return mean_dn;
}


void Raster::ZxImg64Bit::Convert2Display(ZxImgDisplay* _pImg)
{
	if (_pImg == NULL)
		return;
	_pImg->CreateImg(GetWidth(),GetHeight(),4);
	cv::Mat img32(GetHeight(),GetWidth(),CV_8UC4,_pImg->GetImgData(),_pImg->GetWidthStep());
	if (GetBand() == 4)
	{
		cv::Mat img64(GetHeight(),GetWidth(),CV_16UC4,GetImgData(),GetWidthStep());
		cv::normalize(img64,img32,0,255,CV_MINMAX,CV_8UC4);
	}
	else if (GetBand() == 1)
	{
		cv::Mat img64(GetHeight(),GetWidth(),CV_64FC1,GetImgData(),GetWidthStep());
		cv::normalize(img64,img32,0,255,CV_MINMAX,CV_8UC4);
	}
// 	int intThreads = omp_get_num_procs()*4;
// 	omp_set_num_threads(intThreads);
// 	int* BlockLine[2];
// 	BlockLine[0] = new int[intThreads];
// 	BlockLine[1] = new int[intThreads];
// 	for (int i = 0; i != intThreads; i++)
// 	{
// 		BlockLine[0][i] = GetHeight() / intThreads * i;
// 		BlockLine[1][i] = GetHeight() / intThreads * (i + 1);
// 	}
// 	BlockLine[1][intThreads - 1] = GetHeight();
// #pragma omp parallel
// 	{
// 		int iID = omp_get_thread_num();
// 		for (unsigned int j = BlockLine[0][iID]; j != BlockLine[1][iID]; j++)
// 		{
// 			for (unsigned int i = 0; i != GetWidth(); i++ )
// 			{
// 				Compress16Bit8((unsigned short*)this->GetLocation(i,j), _pImg->GetLocation(i,j));
// 			}
// 		}
// 	}
}

void Raster::ZxImg64Bit::DifferPixels(ZxImg64Bit* _pOutput,  int _Drection)
{

}

bool Raster::ZxImg64Bit::Convert2Real(ZxImgBase* _pInput, ZxImg64Bit* _pOutput, int _nChannel)
{
	if (_pInput == NULL)
		return false;
	if (_pInput->GetBand() > _nChannel)
		return false;
	if (_pOutput == NULL)
		_pOutput = new ZxImg64Bit();
	ZxDN transBuffer;

	_pOutput->CreateImg(_pInput->GetWidth(),_pInput->GetHeight(),1);
	switch(_pInput->GetDepth())
	{
	case 24:
		for (int i = 0; i != _pInput->GetWidth(); i++)
			{
				for (int j = 0; j != _pInput->GetHeight(); j++)
				{
					_pInput->GetValue(j,i,0,&transBuffer);
					transBuffer.m_ExportDouble[0] = transBuffer.m_ExportByte[_nChannel];
					_pOutput->SetValue(j,i,-1,&transBuffer); 
				}
			}
		return true;
	case 32:
		switch(_pInput->GetBand())
		{
		case 1:
			for (int i = 0; i != _pInput->GetWidth(); i++)
			{
				for (int j = 0; j != _pInput->GetHeight(); j++)
				{	
					_pInput->GetValue(j,i,0,&transBuffer);
					transBuffer.m_ExportDouble[0] = transBuffer.m_ExportInt32[0];
					_pOutput->SetValue(j,i,-1,&transBuffer); 
				}
			}
			return true;
		case 2:
			for (int i = 0; i != _pInput->GetWidth(); i++)
			{
				for (int j = 0; j != _pInput->GetHeight(); j++)
				{	
					_pInput->GetValue(j,i,0,&transBuffer);
					transBuffer.m_ExportDouble[0] = transBuffer.m_ExportInt16[_nChannel];
					_pOutput->SetValue(j,i,-1,&transBuffer); 
				}
			}
			return true;
		case 4:
			for (int i = 0; i != _pInput->GetWidth(); i++)
			{
				for (int j = 0; j != _pInput->GetHeight(); j++)
				{	
					_pInput->GetValue(j,i,0,&transBuffer);
					transBuffer.m_ExportDouble[0] = transBuffer.m_ExportInt32[_nChannel];
					_pOutput->SetValue(j,i,-1,&transBuffer); 
				}
			}
			return true;
		default:
			return false;
		}
	default:
		return false;
	}
}