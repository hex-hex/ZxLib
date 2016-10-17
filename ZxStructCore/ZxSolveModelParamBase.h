#pragma once
#include "ZxSolveModelParamIndexElement.h"
namespace Solve
{
	class ZXSTRUCT_API ZxSolveModelParamBase
		//参数类须定义对应的模型类为其友元类;
	{
	friend class ZxSolveModelBase;
	protected:
		unsigned int m_ParamCount;
		char m_ParamName[256];
		bool m_bReady;
		ZxSolveModelParamIndex m_ParamIndex;//务必在所有构造函数中初始化它;
		virtual bool IsReady() const;
		void ResetParamCount(unsigned int _ParamCount);
	public:
		ZxSolveModelParamBase(unsigned int _ParamCount);
		virtual ~ZxSolveModelParamBase(void);
		ZxSolveModelParamBase(const ZxSolveModelParamBase& _Params);
		virtual ZxSolveModelParamBase& operator= (const ZxSolveModelParamBase& _Params);
		ZxSolveModelParamIndexElementPtr operator[](unsigned int _Index) const;
		void SetReady(bool _bReady);//让模型设置，不要再使用中自己设置;
		virtual void Reset() = 0;
		unsigned int GetParamCount() const;
		unsigned int GetEngagedCount() const;
		virtual void ExportParams(const char* _ParamsFileName);
		virtual bool ImportParams(const char* _ParamsFileName);
	};
}

