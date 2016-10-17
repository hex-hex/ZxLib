#pragma once
namespace Solve
{
	class ZXSTRUCT_API ZxSolveElement
	{
	public:
		ZxSolveElement(void);
		virtual ~ZxSolveElement(void);
		virtual double GetMeanResidual() const = 0;
		static bool PtrResidualLess(const ZxSolveElement* _plhs, const ZxSolveElement* _prhs);
		static bool ResidualLess(const ZxSolveElement& _lhs, const ZxSolveElement& _rhs);
		static bool PtrResidualMore(const ZxSolveElement* _plhs, const ZxSolveElement* _prhs);
		static bool ResidualMore(const ZxSolveElement& _lhs, const ZxSolveElement& _rhs);
	};
}
