#pragma once
namespace Graph
{
	class ZXSTRUCT_API ZxBoolMatrix
	{
	private:
		unsigned int m_MemSize;
		char* m_pData;
		unsigned int m_Width;
		unsigned int m_Height;
	public:
		ZxBoolMatrix(void);
		ZxBoolMatrix(const ZxBoolMatrix& _Mat);
		ZxBoolMatrix& operator= (const ZxBoolMatrix& _Mat);
		~ZxBoolMatrix(void);
		bool IsNull() const;
		bool Create(unsigned int _Width, unsigned int _Height);
		bool GetValue(unsigned int _x, unsigned int _y) const;
		virtual void SetValue(unsigned int _x,unsigned int _y, bool _Val);
		unsigned int GetCol(void) const;
		unsigned int GetRow(void) const;
	};
}

