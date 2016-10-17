#pragma once
#include "ZxColorBase.h"
using namespace Raster;

namespace Classify
{
	class ZXSTRUCT_API ZxData
	{
	private:
		int		m_DataSize;//ʵ�ʹ�������ݳߴ�
		void*	m_pHead;//CvMat��ͷ����¼��������ݳߴ�;
		float*	m_pfData;
		int		m_TypeSize;//ʵ�ʹ�������ߴ�
		float*	m_pfType;//��¼���;

	public:
		ZxData(void);
		~ZxData(void);
		ZxData(const ZxData& _Data);
		ZxData& operator= (const ZxData& _Data);
		bool Create(int _Dimension, int _Amount, bool _bReserve);
		//_bReserve����Ƿ���֮ǰ����ֵ,�䲻��֤�½����ݷ�Χ�����������Ч;

		void SetValue(int _Count, ZxDN* _pdnVal);//���_Count��Ԫ�ص����ݣ����float��_pdnVal�е�byteֵ;
		void SetType(int _Count, float  _type);
		void Clear();
		int GetDimension() const;//����;
		int GetAmount() const;//����;
		float* GetData(void) const;
		float* GetType(void) const;
	};
}

