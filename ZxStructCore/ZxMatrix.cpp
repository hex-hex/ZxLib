#include "StdAfx.h"
#include "ZxMatrix.h"


Solve::ZxMatrix::ZxMatrix(void)
	:m_dbData(NULL)
	,m_Mat(NULL)
	,m_bManaged(true)
	,m_DataSize(0)
{
}


Solve::ZxMatrix::ZxMatrix(const ZxMatrix& _Mat)
	:m_bManaged(_Mat.m_bManaged)
	,m_DataSize(_Mat.m_DataSize)
{
	if(_Mat.m_dbData != NULL)
	{
		m_Mat = (void*)cvCreateMatHeader(_Mat.GetRow(),_Mat.GetCol(),CV_64F);
		if (_Mat.m_bManaged)
		{
			m_dbData = new double[m_DataSize];
			memcpy_s(m_dbData,sizeof(double) * m_DataSize, _Mat.m_dbData, sizeof(double) * m_DataSize);
		}
		else
		{
			m_dbData = _Mat.m_dbData;
		}
		((CvMat*)m_Mat)->data.db = m_dbData;
	}
	else
	{
		m_Mat = NULL;
		m_dbData = NULL;
	}
}


Solve::ZxMatrix& Solve::ZxMatrix::operator= (const ZxMatrix& _Mat)
{
	if (&_Mat != this)
	{
		m_bManaged = _Mat.m_bManaged;
		m_DataSize = _Mat.m_DataSize;
		if(_Mat.m_dbData != NULL)
		{
			if(m_Mat == NULL)
				m_Mat = (void*)cvCreateMatHeader(_Mat.GetRow(),_Mat.GetCol(),CV_64F);
			else
			{
				cvInitMatHeader((CvMat*)m_Mat,_Mat.GetRow(),_Mat.GetCol(),CV_64F);
				delete[] m_dbData;
			}
			if (m_bManaged)
			{
				m_dbData = new double[m_DataSize];
				memcpy_s(m_dbData,sizeof(double) * m_DataSize, _Mat.m_dbData, sizeof(double) * m_DataSize);
			}
			else
			{
				m_dbData = _Mat.m_dbData;
			}
			((CvMat*)m_Mat)->data.db = m_dbData;
		}
		else
		{
			m_Mat = NULL;
			m_dbData = NULL;
		}
	}
	return *this;
}


Solve::ZxMatrix::~ZxMatrix(void)
{
	if (m_Mat)
	{
		((CvMat*)m_Mat)->data.db = NULL;
		if (m_bManaged)
		{
			delete[] m_dbData;
			cvReleaseMatHeader((CvMat**)(&m_Mat));
		}
		else
		{
			cvReleaseMatHeader((CvMat**)(&m_Mat));
		}		
	}
	m_dbData = NULL;
}


bool Solve::ZxMatrix::Create(int _Row, int _Col)
{
	if (_Row == GetRow() && _Col == GetCol())
	{
		return true;
	}

	if (m_Mat)
		cvInitMatHeader((CvMat*)m_Mat,_Row,_Col,CV_64F);
	else
		m_Mat = (void*)cvCreateMatHeader(_Row,_Col,CV_64F);

	if(_Col * _Row > m_DataSize)
	{
		if(m_bManaged)
		{
			if(m_dbData)
				delete[] m_dbData;
		}
		m_DataSize = _Col * _Row;
		m_dbData = new double[m_DataSize];
		if (m_dbData == NULL)
		{
			return false;
		}
	};
	((CvMat*)m_Mat)->data.db = m_dbData;
	m_bManaged = true;
	return true;
}

void Solve::ZxMatrix::BindingData(double* _pdbData,int _Row, int _Col)
{
	if (m_Mat)
		cvInitMatHeader((CvMat*)m_Mat,_Row,_Col,CV_64F,_pdbData);
	else
	{
		m_Mat = (void*)cvCreateMatHeader(_Row,_Col,CV_64F);
		((CvMat*)m_Mat)->data.db = _pdbData;
	}
	if (m_bManaged)
	{
		delete[] m_dbData;
		m_DataSize = 0;
	}
	m_dbData = _pdbData;
	m_bManaged = false;
}

void Solve::ZxMatrix::Tranpose(void)
{
	cvTranspose((CvMat*)m_Mat,(CvMat*)m_Mat);
}


int Solve::ZxMatrix::GetRow(void) const
{
	if (m_Mat)
	{
		return ((CvMat*)m_Mat)->rows;
	}
	else
		return 0;
}


int Solve::ZxMatrix::GetCol(void) const
{
	if (m_Mat)
	{
		return ((CvMat*)m_Mat)->cols;
	}
	else
		return 0;
}


double* Solve::ZxMatrix::GetData(void) const
{
	return m_dbData;
}


void Solve::ZxMatrix::CloneFrom(const ZxMatrix& _Mat)
{
	if (GetRow() == _Mat.GetRow() && GetCol() == _Mat.GetCol())
	{
		memcpy(m_dbData,_Mat.GetData(),
			((CvMat*)m_Mat)->rows * ((CvMat*)m_Mat)->cols * sizeof(double));
	}
	else
	{
		Create(_Mat.GetRow(),_Mat.GetCol());
		memcpy(m_dbData,_Mat.GetData(),
			((CvMat*)m_Mat)->rows * ((CvMat*)m_Mat)->cols * sizeof(double));
	}
}


void Solve::ZxMatrix::Invert(void)
{
	if (m_Mat)
	{
		if (GetCol() == GetRow())
		{
			cvInvert((CvMat*)m_Mat,(CvMat*)m_Mat);
		}
	}
}


void Solve::ZxMatrix::MulTransposed2(ZxMatrix& _DstMat,bool _Order)
{
	if (_Order)
	{
		if (GetCol() != _DstMat.GetCol() || !_DstMat.IsSquare())
		{
			_DstMat.Create(GetCol(),GetCol());
		}
		cvMulTransposed((CvMat*)m_Mat,(CvMat*)(_DstMat.m_Mat),1);
	}
	else
	{
		if (GetRow() != _DstMat.GetRow() || !_DstMat.IsSquare())
		{
			_DstMat.Create(GetRow(),GetRow());
		}
		cvMulTransposed((CvMat*)m_Mat,(CvMat*)(_DstMat.m_Mat),0);
	}
}


bool Solve::ZxMatrix::IsSquare(void) const
{
	return GetCol() == GetRow();
}


bool Solve::ZxMatrix::MatMul(ZxMatrix& _MatLeft, ZxMatrix& _MatRight)
{
	if (_MatLeft.GetCol() != _MatRight.GetRow())
	{
		return false;
	}
	
	if (_MatLeft.GetRow() != GetRow() || _MatRight.GetCol() != GetCol())
	{
		Create(_MatLeft.GetRow(), _MatRight.GetCol());
	}
	cvMatMul((CvMat*)(_MatLeft.m_Mat),(CvMat*)(_MatRight.m_Mat),(CvMat*)m_Mat);
	return true;
}


void Solve::ZxMatrix::SetZero(void)
{
	if (m_Mat)
	{
		cvZero((CvMat*)m_Mat);
	}
}


void Solve::ZxMatrix::SetIdentity(void)
{
	if (m_Mat)
	{
		cvSetIdentity((CvMat*)m_Mat);
	}
}


double Solve::ZxMatrix::GetElement(int _Row, int _Col) const
{
	if (m_Mat)
	{
		return *(m_dbData + ((CvMat*)m_Mat)->cols * _Row + _Col);
	}
	else
	{
		return DBL_MAX;
	}
}

void Solve::ZxMatrix::SetElement(double _dbValue, int _Row, int _Col)
{
	if (m_Mat)
		*(m_dbData + ((CvMat*)m_Mat)->cols * _Row + _Col) = _dbValue;
}

void Solve::ZxMatrix::ExportMat(const char* _FileName)
{
	if (m_Mat == NULL)
	{
		return;
	}
	CStdioFile fileTXT;
	CString strNum;
	if(fileTXT.Open(_FileName,CFile::modeCreate | CFile::modeWrite))
	{
		for (int i = 0; i < ((CvMat*)m_Mat)->rows; i++)
		{
			for (int j = 0; j < ((CvMat*)m_Mat)->cols; j++)
			{
				strNum.Format("%.10f\t",((CvMat*)m_Mat)->data.db[i * ((CvMat*)m_Mat)->cols + j]);
				fileTXT.WriteString(strNum);
			}
			strNum.Format("\n");
			fileTXT.WriteString(strNum);
		}
		fileTXT.Close();
	}
}


void Solve::ZxMatrix::SolveEquation(ZxMatrix& _matA, ZxMatrix& _matb)
{
	cvSolve((CvMat*)(_matA.m_Mat),(CvMat*)(_matb.m_Mat),(CvMat*)m_Mat);
}

void Solve::ZxMatrix::Add(ZxMatrix& _mat2Add)
{
	cvAdd((CvMat*)m_Mat,(CvMat*)(_mat2Add.m_Mat),(CvMat*)m_Mat);
}

void Solve::ZxMatrix::Sum(ZxMatrix& _matAdd1,ZxMatrix& _matAdd2)
{
	cvAdd((CvMat*)(_matAdd1.m_Mat),(CvMat*)(_matAdd2.m_Mat),(CvMat*)m_Mat);
}

void Solve::ZxMatrix::MulTransposed(ZxMatrix& _MatA,ZxMatrix& _MatB)
{
	cvGEMM((CvMat*)(_MatA.m_Mat),(CvMat*)(_MatB.m_Mat),1,NULL,0,(CvMat*)m_Mat,CV_GEMM_A_T);
}

void Solve::ZxMatrix::Sub(ZxMatrix& _matMinuend,ZxMatrix& _matSubtrahend)
{
	cvSub((CvMat*)(_matMinuend.m_Mat),(CvMat*)(_matSubtrahend.m_Mat),(CvMat*)m_Mat);
}


Solve::ZxMatrix* Solve::ZxMatrix::GaussianTemplate(double _Size)
{
	return NULL;
}