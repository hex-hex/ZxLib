#pragma once
#include "ZxSolveModelParamIndexElement.h"
namespace Solve
{
	class ZXSTRUCT_API ZxSolveModelParamBase
		//�������붨���Ӧ��ģ����Ϊ����Ԫ��;
	{
	friend class ZxSolveModelBase;
	protected:
		unsigned int m_ParamCount;
		char m_ParamName[256];
		bool m_bReady;
		ZxSolveModelParamIndex m_ParamIndex;//��������й��캯���г�ʼ����;
		virtual bool IsReady() const;
		void ResetParamCount(unsigned int _ParamCount);
	public:
		ZxSolveModelParamBase(unsigned int _ParamCount);
		virtual ~ZxSolveModelParamBase(void);
		ZxSolveModelParamBase(const ZxSolveModelParamBase& _Params);
		virtual ZxSolveModelParamBase& operator= (const ZxSolveModelParamBase& _Params);
		ZxSolveModelParamIndexElementPtr operator[](unsigned int _Index) const;
		void SetReady(bool _bReady);//��ģ�����ã���Ҫ��ʹ�����Լ�����;
		virtual void Reset() = 0;
		unsigned int GetParamCount() const;
		unsigned int GetEngagedCount() const;
		virtual void ExportParams(const char* _ParamsFileName);
		virtual bool ImportParams(const char* _ParamsFileName);
	};
}

