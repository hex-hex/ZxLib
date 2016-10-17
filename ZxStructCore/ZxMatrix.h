#pragma once
namespace Solve
{
	class ZXSTRUCT_API ZxMatrix
	{
	private:
		int		m_DataSize;
		bool	m_bManaged;
		void*	m_Mat;
		double* m_dbData;
	public:
		ZxMatrix(void);
		~ZxMatrix(void);
		ZxMatrix(const ZxMatrix& _Mat);
		ZxMatrix& operator= (const ZxMatrix& _Params);

		bool Create(int _Row, int _Col);
		void BindingData(double* _pdbData,int _Row, int _Col);//可以不Create直接绑定;

		int GetRow(void) const;
		int GetCol(void) const;
		double* GetData(void) const;

		void CloneFrom(const ZxMatrix& _Mat);
		bool IsSquare(void) const;
		void SetZero(void);
		void SetIdentity(void);

		void Invert(void);
		void Tranpose(void);
		void MulTransposed2(ZxMatrix& _DstMat, bool _Order = true);//true为左项转置，false为右项转置;
		void MulTransposed(ZxMatrix& _MatA,ZxMatrix& _MatB);
		bool MatMul(ZxMatrix& _MatLeft, ZxMatrix& _MatRight);
		double GetElement(int _Row, int _Col) const;
		void SetElement(double _dbValue, int _Row, int _Col);
		void ExportMat(const char* _FileName);

		void SolveEquation(ZxMatrix& _matA, ZxMatrix& _matb);
		void Add(ZxMatrix& _mat2Add);
		void Sum(ZxMatrix& _matAdd1,ZxMatrix& _matAdd2);
		void Sub(ZxMatrix& _matMinuend,ZxMatrix& _matSubtrahend);

		static ZxMatrix* GaussianTemplate(double _Size);
	};
}

