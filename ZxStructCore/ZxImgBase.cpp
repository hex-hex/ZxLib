#include "StdAfx.h"
#include "ZxImgBase.h"


Raster::ZxImgBase::ZxImgBase(void)
	:m_imgData(NULL)
	,m_Height(0)
	,m_Width(0)
	,m_Widthstep(0)
	,m_BitPerPixel(0)
	,m_imgMemSize(0)
{
}


Raster::ZxImgBase::ZxImgBase(const ZxImgBase& _img)
	:m_Height(_img.m_Height)
	,m_Width(_img.m_Width)
	,m_Widthstep(_img.m_Widthstep)
	,m_BitPerPixel(_img.m_BitPerPixel)
	,m_imgMemSize(_img.m_imgMemSize)
{
	if(_img.m_imgMemSize != 0)
	{
		m_imgData = new unsigned char[_img.m_imgMemSize];
		memcpy_s(m_imgData,_img.m_imgMemSize * sizeof(char),_img.m_imgData,m_imgMemSize * sizeof(char));
	}
}


Raster::ZxImgBase& Raster::ZxImgBase::operator = (const ZxImgBase& _img)
{
	if (&_img != this)
	{
		m_Height = _img.m_Height;
		m_Width = _img.m_Width;
		m_Widthstep = _img.m_Widthstep;
		m_BitPerPixel = _img.m_BitPerPixel;
		if (m_imgMemSize < _img.m_imgMemSize)
		{
			if (m_bManaged)
				if (m_imgData != NULL)
					delete m_imgData;

			m_imgData = new unsigned char[_img.m_imgMemSize];
			m_imgMemSize = _img.m_imgMemSize;
			memcpy_s(m_imgData,_img.m_imgMemSize * sizeof(char),_img.m_imgData,m_imgMemSize * sizeof(char));
		}
		else
		{
			memcpy_s(m_imgData,_img.m_imgMemSize * sizeof(char),_img.m_imgData,m_imgMemSize * sizeof(char));
		}
	}
	return *this;
}


Raster::ZxImgBase::~ZxImgBase(void)
{	
	if(m_bManaged)
	{
		if(m_imgData)
		{
			delete[] m_imgData;
			m_imgData = NULL;
		}
	}
}

const unsigned int Raster::ZxImgBase::GetBand(void) const
{
	return m_Channel;
}

bool Raster::ZxImgBase::CreateImg(unsigned int _Width,unsigned  int _Height,unsigned int _BitPerPixel)
{
	m_Width = _Width;
	_Width = (_Width * _BitPerPixel) / 8;//¸Ä±äº¬Òå//

	int remainder = _Width % 4;
	if(remainder != 0)
	{
		_Width += 4 - remainder;
	}

	unsigned int size = _Width * _Height;
	if (size <= m_imgMemSize)
	{
		m_Height = _Height;
		m_BitPerPixel = _BitPerPixel;
		m_Widthstep = _Width;
		return true;
	}
	else
	{
		if (m_imgData != NULL && m_bManaged)
		{
			delete[] m_imgData;
		}
		m_bManaged = true;
		m_imgData = new unsigned char[size];
		if (m_imgData == NULL)
		{
			m_Height = 0;
			m_Width = 0;
			m_Widthstep = 0;
			m_BitPerPixel = 0;
			m_imgMemSize = 0;
			return false;
		}
		else
		{
			m_Height = _Height;
			m_BitPerPixel = _BitPerPixel;
			m_Widthstep = _Width;
			m_imgMemSize = size;
			return true;
		}
	}
}


const unsigned int Raster::ZxImgBase::GetWidth() const
{
	return m_Width;
}


const unsigned int Raster::ZxImgBase::GetHeight() const
{
	return m_Height;
}


const unsigned int Raster::ZxImgBase::GetWidthStep(void) const
{
	return m_Widthstep;
}


unsigned char* Raster::ZxImgBase::GetImgData(void) const
{
	return m_imgData;
}


const bool Raster::ZxImgBase::IsManaged(void) const
{
	return m_bManaged;
}

const unsigned int Raster::ZxImgBase::GetDepth(void) const
{
	return m_BitPerPixel;
}

const unsigned int Raster::ZxImgBase::GetMemSize(void) const
{
	return m_imgMemSize;
}

void Raster::ZxImgBase::DetachManagement(void)
{
	m_bManaged = false;
}


void  Raster::ZxImgBase::SetValue(int _X, int _Y, int _BandID, const ZxDN* _pinVal)
{
	if (_BandID < 0)
		return;
	if (_BandID < GetBand())
	{
		int BPC = GetDepth() / GetBand();
		switch(BPC)
		{
		case 8:
			memcpy_s(GetImgData() + _Y * GetWidthStep() + _X * GetDepth() / 8 + _BandID,sizeof(char),_pinVal->m_ExportByte,sizeof(char));
			break;
		case 32:
			memcpy_s(GetImgData() + _Y * GetWidthStep() + _X * GetDepth() / 8  + _BandID * 4,sizeof(int),_pinVal->m_ExportInt32,sizeof(int));
			break;
		case 64:
			memcpy_s(GetImgData() + _Y * GetWidthStep() + _X * GetDepth() / 8  + _BandID * 8,sizeof(double),_pinVal->m_ExportDouble,sizeof(double));
			break;
		}
	}
	else
		return;
}


void Raster::ZxImgBase::GetValue(int _X, int _Y, int _BandID, ZxDN* _poutVal) const
{
	if (_BandID < GetBand())
	{
		if (_BandID < 0)
		{
			_BandID = 0;
		}
		int BitPC = GetDepth() / GetBand();
		switch(BitPC)
		{
		case 8:
			memcpy_s(_poutVal->m_ExportByte,sizeof(char),GetImgData() + _Y * GetWidthStep() + _X * GetDepth() / 8  + _BandID,sizeof(char));
			break;
		case 24:
			memcpy_s(_poutVal->m_ExportByte,sizeof(char),GetImgData() + _Y * GetWidthStep() + _X * GetDepth() / 8  + _BandID * 3, sizeof(char) * 3);
			break;
		case 32:
			memcpy_s(_poutVal->m_ExportInt32,sizeof(int),GetImgData() + _Y * GetWidthStep() + _X * GetDepth() / 8  + _BandID * 4, sizeof(int));
			break;
		case 64:
			memcpy_s(_poutVal->m_ExportDouble,sizeof(double),GetImgData() + _Y * GetWidthStep() + _X * GetDepth() / 8  + _BandID * 8,sizeof(double));
			break;
		}
	}
}


Raster::ZxImgBase::ZxImgIOParamBase::ZxImgIOParamBase()
	:m_pRegion(NULL)
	,m_ChannelVal(66051)
{

}


Raster::ZxImgBase::ZxImgIOParamBase::~ZxImgIOParamBase()
{
	if (m_pRegion != NULL)
	{
		delete m_pRegion;
		m_pRegion = NULL;
	}
}

int Raster::ZxImgBase::ZxImgIOParamBase::GetMaxBand()
{
	return MAX(MAX(MAX(m_Channel[0],m_Channel[1]),m_Channel[2]),m_Channel[3]);
}

int Raster::ZxImgBase::ZxImgIOParamBase::GetMaxChannel()
{
	int intChannel(3);
	while(!m_Channel[intChannel])
	{
		intChannel --;
	}
	return intChannel + 1;
}