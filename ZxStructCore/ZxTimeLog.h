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
		double LogPoint();//��ÿ�ʼ��ʱ���ϴμ�¼�㵽����Ϊֹ��ʱ����;
	};
}

