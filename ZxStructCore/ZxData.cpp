#include "StdAfx.h"
#include "ZxData.h"


Classify::ZxData::ZxData(void)
	:m_pfData(NULL)
	,m_pHead(NULL)
	,m_pfType(NULL)
	,m_DataSize(0)
	,m_TypeSize(0)
{
}


Classify::ZxData::~ZxData(void)
{
	if (m_pHead)
	{
		((CvMat*)m_pHead)->data.fl = NULL;
		delete[] m_pfData;
		delete[] m_pfType;
		cvReleaseMatHeader((CvMat**)(&m_pHead));
	}
	m_pfData = NULL;
}

void Classify::ZxData::Clear()
{
	if (m_pHead)
	{
		((CvMat*)m_pHead)->data.fl = NULL;
		delete[] m_pfData;
		delete[] m_pfType;
		cvReleaseMatHeader((CvMat**)(&m_pHead));
	}
	m_pHead = NULL;
	m_pfData = NULL;
	m_pfType = NULL;
	m_DataSize = 0;
	m_TypeSize = 0;
}

Classify::ZxData::ZxData(const ZxData& _Data)
{
	if(_Data.m_pfData != NULL)
	{
		m_DataSize = _Data.m_DataSize;
		m_TypeSize = _Data.m_TypeSize;
		m_pHead = (void*)cvCreateMatHeader(_Data.GetAmount(),_Data.GetDimension(),CV_32F);
		m_pfData = new float[m_DataSize];
		m_pfType = new float[m_TypeSize];
		memcpy_s(m_pfData,sizeof(float) * m_DataSize, _Data.m_pfData, sizeof(float) * m_DataSize);
		((CvMat*)m_pHead)->data.fl = m_pfData;
	}
	else
	{
		m_pHead = NULL;
		m_pfData = NULL;
	}
}

Classify::ZxData& Classify::ZxData::operator= (const ZxData& _Data)
{
	if (&_Data != this)
	{
		if(_Data.m_pfData != NULL)
		{
			/*
			if(m_pHead == NULL)
			{
				m_pHead = (void*)cvCreateMatHeader(_Data.GetAmount(),_Data.GetDimension(),CV_64F);
				m_pfData = new float[m_DataSize];
				m_pfType = new float[_Data.GetAmount()];
				m_TypeSize = _Data.GetAmount();
				m_DataSize = _Data.m_DataSize;
			}
			else
			{
				if (m_TypeSize < _Data.GetAmount())
				{
					delete[] m_pfType;
					m_pfType = new float[_Data.GetAmount()];
					m_TypeSize = _Data.GetAmount();
				}
				cvInitMatHeader((CvMat*)m_pHead,_Data.GetAmount(),_Data.GetDimension(),CV_32F);
				if(m_DataSize < _Data.GetAmount() * _Data.GetDimension())
				{
					delete[] m_pfData;
					m_pfData = new float[m_DataSize];
					m_DataSize = _Data.GetAmount() * _Data.GetDimension();
				}
			}
			((CvMat*)m_pHead)->data.fl = m_pfData;
			*/
			Create(_Data.GetDimension(),_Data.GetAmount(),false);
			memcpy_s(m_pfData, sizeof(float) * m_DataSize, _Data.m_pfData, sizeof(float) * m_DataSize);
			memcpy_s(m_pfType, sizeof(float) * GetAmount(), _Data.m_pfType, _Data.GetAmount() * sizeof(float));
		}
		else
		{
			if (m_pHead)
			{
				((CvMat*)m_pHead)->data.fl = NULL;
				delete[] m_pfData;
				delete[] m_pfType;
				cvReleaseMatHeader((CvMat**)(&m_pHead));
				m_pfData = NULL;
				m_pfType = NULL;
				m_DataSize = 0;
				m_TypeSize = 0;
			}
		}
	}
	return *this;
}


bool Classify::ZxData::Create(int _Dimension, int _Amount, bool _bReserve)
{
	if (_Dimension == GetDimension() && _Amount == GetAmount())
	{
		return true;
	}

	if (m_pHead)
	{
		if(_bReserve)
		{
			int amountFormer(GetAmount());
			if (_Dimension == GetDimension())
			{
				if (_Amount * _Dimension > m_DataSize)
				{
					m_DataSize = _Amount * _Dimension;
					m_pfData = new float[m_DataSize];
					memcpy_s(m_pfData, m_DataSize * sizeof(float),
						((CvMat*)m_pHead)->data.fl, amountFormer * _Dimension* sizeof(float));
					delete[] ((CvMat*)m_pHead)->data.fl;
				}
			}
			else
			{
				int dimensionFormer(GetDimension());
				m_DataSize = _Amount * _Dimension;
				m_pfData = new float[m_DataSize];
				int amountLess(_Amount > amountFormer? amountFormer : _Amount);
				int dimensionLess(_Dimension > dimensionFormer? dimensionFormer : _Dimension);
				for (int i = 0; i != amountLess; i++)
					for (int j = 0; j != dimensionLess; j ++)
						*(m_pfData + i * _Dimension + j) = *(((CvMat*)m_pHead)->data.fl + i * dimensionFormer + j);
				delete[] ((CvMat*)m_pHead)->data.fl;
			}

			if(_Amount > amountFormer)
			{
				float* pFormerType = m_pfType;
				m_TypeSize = _Amount;
				m_pfType = new float[m_TypeSize];
				memcpy_s(m_pfType, m_TypeSize * sizeof(float),
					pFormerType, amountFormer * sizeof(float));
				delete[] pFormerType;
			}
		}
		else
		{
			if(_Dimension * _Amount > m_DataSize)
			{

				delete[] m_pfData;
				m_DataSize = _Dimension * _Amount;
				m_pfData = new float[m_DataSize];
				if (m_pfData == NULL)
					return false;
			};

			if(_Amount > m_TypeSize)
			{
				delete[] m_pfType;
				m_TypeSize = _Amount;
				m_pfType = new float[m_TypeSize];
				if (m_pfType == NULL)
					return false;
			}
		}
		cvInitMatHeader((CvMat*)m_pHead,_Amount,_Dimension,CV_32F);
	}
	else
	{
		m_pfType = new float[_Amount];
		m_TypeSize = _Amount;
		m_DataSize = _Dimension * _Amount;
		m_pfData = new float[m_DataSize];
		if (m_pfData == NULL)
			return false;
		m_pHead = (void*)cvCreateMatHeader(_Amount,_Dimension,CV_32F);
	}
	((CvMat*)m_pHead)->data.fl = m_pfData;
	return true;
}


int Classify::ZxData::GetDimension() const
{
	if (m_pHead)
	{
		return ((CvMat*)m_pHead)->cols;
	}
	else
		return 0;
}

int Classify::ZxData::GetAmount() const
{
	if (m_pHead)
	{
		return ((CvMat*)m_pHead)->rows;
	}
	else
		return 0;
}

float* Classify::ZxData::GetData(void) const
{
	return m_pfData;
}

float* Classify::ZxData::GetType(void) const
{
	return m_pfType;
}

void Classify::ZxData::SetValue(int _Count, ZxDN* _pdnVal)
{
	for (int i = 0; i != GetDimension(); i++)
	{
		*(m_pfData + _Count * GetDimension() + i) = static_cast<float>(_pdnVal->m_ExportByte[i]);
	}
}

void Classify::ZxData::SetType(int _Count, float  _type)
{
	m_pfType[_Count] = _type; 
}