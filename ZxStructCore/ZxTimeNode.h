#pragma once
namespace GeoReference
{
	class ZXSTRUCT_API ZxTimeNode
	{
	private:
		static bool IsLeap(int _Year);
		static int GetDayCount(int _Month, bool _IsLeap = false);
	public:
		ZxTimeNode(void);
		~ZxTimeNode(void);
		ZxTimeNode(const ZxTimeNode& rhs);
		virtual ZxTimeNode& operator= (const ZxTimeNode& rhs);
		void Reset();
		double OffSet(ZxTimeNode& _TimeOff);
		int m_Year;
		int m_Month;
		int m_Day;
		int m_Hour;
		int m_Minute;
		double m_Second;
		double m_UTC;
	};
}

