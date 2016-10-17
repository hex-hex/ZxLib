#pragma once
#include "ZxSolveModelParamBase.h"
#include "ZxSolveElement.h"

namespace Solve
{
	class ZXSTRUCT_API ZxSolveModelBase
	{
	protected:
		char m_ModelName[256];
		ZxSolveModelParamBase* m_pParam;//�ô���Ϊ���ã��������ڴ棬�����й�������������������;
	public:
		ZxSolveModelBase(void);
		virtual ~ZxSolveModelBase(void);
		virtual bool IsReady() const;
		virtual bool SetStarter(ZxSolveModelParamBase* _pStarter);
	};
}

