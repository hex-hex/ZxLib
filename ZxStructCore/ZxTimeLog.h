#pragma once
namespace Experience
{
	class ZXSTRUCT_API ZxTimeLog
	{
	private:
	double m_dbClick;
	public:
		ZxTimeLog(void);
		~ZxTimeLog(void);
		void BeginClick();
		double LogPoint();//获得开始计时或上次记录点到现在为止的时间间隔;
	};
}

