#pragma once
#include "zxboolmatrix.h"
namespace Graph
{
	class ZXSTRUCT_API ZxSymBoolMatrix
	{
	private:
		unsigned int m_MemSize;
		char* m_pData;//只记录右上三角阵;
		unsigned int m_Size;
	public:
		ZxSymBoolMatrix(void);
		~ZxSymBoolMatrix(void);
		ZxSymBoolMatrix(const ZxSymBoolMatrix& _Mat);
		ZxSymBoolMatrix& operator= (const ZxSymBoolMatrix& _Mat);
		bool IsNull() const;
		bool Create(unsigned int _Size);
		bool GetValue(unsigned int _x, unsigned int _y) const;
		void SetValue(unsigned int _x,unsigned int _y, bool _Val);
		unsigned int GetSize(void) const;
	};

}
