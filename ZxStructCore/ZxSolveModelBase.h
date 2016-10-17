#pragma once
#include "ZxSolveModelParamBase.h"
#include "ZxSolveElement.h"

namespace Solve
{
	class ZXSTRUCT_API ZxSolveModelBase
	{
	protected:
		char m_ModelName[256];
		ZxSolveModelParamBase* m_pParam;//该处仅为引用，不管理内存，请自行管理参数对象的生命周期;
	public:
		ZxSolveModelBase(void);
		virtual ~ZxSolveModelBase(void);
		virtual bool IsReady() const;
		virtual bool SetStarter(ZxSolveModelParamBase* _pStarter);
	};
}

