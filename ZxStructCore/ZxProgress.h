#pragma once
namespace Experience
{
	class ZXSTRUCT_API ZxProgress//���ڼ�¼����ֵ
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

