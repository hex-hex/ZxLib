#pragma once
namespace Experience
{
	class ZXSTRUCT_API ZxProgress//用于记录进度值
	{
	private:
		double m_Value;
		CRITICAL_SECTION m_Lock;
	public:
		ZxProgress(void);
		~ZxProgress(void);
		double GetVal(void);
		void Reset();
		void SetVal(double _Val);
		void AddVal(double _Val);
		void MulVal(double _Val);
	};
}

