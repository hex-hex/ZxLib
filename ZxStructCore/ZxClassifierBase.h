#pragma once
#include "ZxData.h"

namespace Classify
{
	class ZXSTRUCT_API ZxClassifierBase
	{
	protected:
		void* m_pData;
	public:
		ZxClassifierBase(void);
		~ZxClassifierBase(void);
		virtual bool Learn(ZxData& _matData) = 0;//�������Ҳ��Ҫ��float
		virtual float Classify(ZxData& _matData) = 0;//��ȷ����float��
		virtual void Clear() = 0;
	};
}
