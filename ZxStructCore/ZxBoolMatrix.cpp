#include "StdAfx.h"
#include "ZxBoolMatrix.h"

Graph::ZxBoolMatrix::ZxBoolMatrix(void)
	:m_MemSize(0)
	,m_Width(0)
	,m_Height(0) 
	,m_pData(NULL)
{
}

Graph::ZxBoolMatrix::ZxBoolMatrix(const ZxBoolMatrix& _Mat)
	:m_MemSize(_Mat.m_MemSize)
	,m_Width(_Mat.m_Width)
	,m_Height(_Mat.m_Height)
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

Graph::ZxBoolMatrix& Graph::ZxBoolMatrix::operator= (const ZxBoolMatrix& _Mat)
{
	if (&_Mat != this)
	{	
		m_Width = _Mat.m_Width;
		m_Height = _Mat.m_Height;

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


Graph::ZxBoolMatrix::~ZxBoolMatrix(void)
{
	if (m_pData != NULL)
	{
		delete[] m_pData;
	}
}

bool Graph::ZxBoolMatrix::IsNull() const
{
	return m_pData == NULL;
}

bool Graph::ZxBoolMatrix::Create(unsigned int _Width, unsigned int _Height)
{
	if (_Height * _Width <= m_MemSize * 8)
	{
		memset(m_pData,0,m_MemSize * sizeof(char));
		m_Height = _Height;
		m_Width = _Width;
		return true;
	}
	else
	{
		delete[] m_pData;
		int Request = _Height * _Width;
		m_MemSize = Request % 8 == 0? Request / 8: Request / 8 + 1;
		m_pData = new char[m_MemSize];
		if (m_pData == NULL)
		{
			m_MemSize = 0;
			m_Height = 0;
			m_Width = 0;
			return false;
		}
		else
		{
			memset(m_pData,0,m_MemSize * sizeof(char));
			m_Height = _Height;
			m_Width = _Width;
			return true;
		}
	}
}


bool Graph::ZxBoolMatrix::GetValue(unsigned int _x,unsigned int _y) const
{
	if (_x < GetCol() && _y < GetRow())
	{
		unsigned int Loc = _x + GetCol() * _y;
		char Val = *(m_pData + Loc / 8);
		return (Val >> (7 - Loc % 8)) & 1;
	}
	else
		return false;
}


void Graph::ZxBoolMatrix::SetValue(unsigned int _x,unsigned int _y, bool _Val)
{
	if(_x < GetCol() && _y < GetRow())
	{
		unsigned int Loc = _x + GetCol() * _y;
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

unsigned int Graph::ZxBoolMatrix::GetCol(void) const
{
	return m_Width;
}

unsigned int Graph::ZxBoolMatrix::GetRow(void) const
{
	return m_Height;
}