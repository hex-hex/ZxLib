#pragma once
#include "Zx3DPoint.h"
#include "ZxGeoRef.h"
using namespace Geometry;
namespace GeoReference
{
	class ZXSTRUCT_API ZxGeoTrans
	{
	private:
		void* m_hGeoRefTemp;
		void PrepareTrans(void);
	protected:
		ZxGeoRef*	m_pSrc;
		ZxGeoRef*	m_pDst;
		void*		m_Trans;
	public:
		ZxGeoTrans(void);
		~ZxGeoTrans(void);
		bool DoTransSelf(Zx3DPoint* _pPoint);
		void SetSource(const ZxGeoRef* _pGeoRef);
		void SetTarget(const ZxGeoRef* _pGeoRef);
	};
}

