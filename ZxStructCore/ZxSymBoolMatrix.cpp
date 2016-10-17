#include "StdAfx.h"
#include "ZxSymBoolMatrix.h"


Graph::ZxSymBoolMatrix::ZxSymBoolMatrix(void)
	:m_MemSize(0)
	,m_Size(0)
	,m_pData(NULL)
{
}

Graph::ZxSymBoolMatrix::~ZxSymBoolMatrix(void)
{
	if (m_pData != NULL)
	{
		delete[] m_pData;
	}
}

Graph::ZxSymBoolMatrix::ZxSymBoolMatrix(const ZxSymBoolMatrix& _Mat)
	:m_MemSize(_Mat.m_MemSize)
	,m_Size(_Mat.m_Size)
{
	if (_Mat.m_pData != NULL)
	{
		m_pData = new char[m_MemSize];
		memcpy_s(m_pData,sizeof(char) * m_MemSize, _Mat.m_pData, sizeof(char) * m_MemSize);
	}
	else
	{
		m_pData = NULL;
	}
}

Graph::ZxSymBoolMatrix& Graph::ZxSymBoolMatrix::operator= (const ZxSymBoolMatrix& _Mat)
{
	if (&_Mat != this)
	{	
		m_Size = _Mat.m_Size;

		if (_Mat.m_pData != NULL)
		{
			if(m_MemSize < _Mat.m_MemSize)
			{
				if (NULL != m_pData)
					delete[] m_pData;
				m_pData = new char[m_MemSize];
				m_MemSize = _Mat.m_MemSize;
			}
			memcpy_s(m_pData,sizeof(char) * m_MemSize, _Mat.m_pData, sizeof(char) * m_MemSize);
		}
		else
		{
			if (NULL != m_pData)
				delete[] m_pData;			
			m_pData = NULL;
		}
	}
	return *this;
}


bool Graph::ZxSymBoolMatrix::IsNull() const
{
	return m_pData == NULL;
}

bool Graph::ZxSymBoolMatrix::Create(unsigned int _Size)
{
	if (((_Size + 1)* _Size) / 2 <= m_MemSize * 8)
	{
		memset(m_pData,0,m_MemSize * sizeof(char));
		m_Size = m_Size;
		return true;
	}
	else
	{
		delete[] m_pData;
		int Request = ((_Size + 1)* _Size) / 2;
		m_MemSize = Request % 8 == 0? Request / 8: Request / 8 + 1;
		try
		{
			m_pData = new char[m_MemSize];
			memset(m_pData,0,m_MemSize * sizeof(char));
			m_Size = _Size;
			return true;
		}
		catch(...)
		{
			m_MemSize = 0;
			m_Size = 0;
			return false;
		}
	}
	return true;
}


bool Graph::ZxSymBoolMatrix::GetValue(unsigned int _x, unsigned int _y) const
{
	if (_x < GetSize() && _y < GetSize())
	{
		if (_x < _y)
		{
			return GetValue(_y,_x);
		}
		else
		{
			unsigned int Loc = m_Size * _y - _y * (_y + 1) / 2  + _x;
			char Val = *(m_pData + Loc / 8);
			return (Val >> (7 - Loc % 8)) & 1;
		}
	}
	else
		return false;
}


void Graph::ZxSymBoolMatrix::SetValue(unsigned int _x,unsigned int _y, bool _Val)
{
	if(_x < GetSize() && _y < GetSize())
	{
		if (_x < _y)
		{
			return SetValue(_y,_x,_Val);
		}
		else
		{
			unsigned int Loc = m_Size * _y - _y * (_y + 1) / 2  + _x;
			unsigned char Val = 1 << (7 - Loc % 8);
			if (_Val)
			{
				*(m_pData + Loc / 8) |= Val;
			}
			else
			{
				*(m_pData + Loc / 8) &= ~(Val);
			}
		}
	}
}

unsigned int Graph::ZxSymBoolMatrix::GetSize(void) const
{
	return m_Size;
}