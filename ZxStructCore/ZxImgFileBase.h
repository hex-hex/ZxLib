#pragma once

#include "zxfilebase.h"
#include "ZxImgBase.h"
#include "ZxGeoRef.h"
#include "Zx2DPoint.h"
#include "Zx3DPoint.h"
#include "ZxRectangle.h"

using namespace Geometry;
using namespace GeoReference;
using namespace File;

namespace Raster
{
	class ZXSTRUCT_API ZxImgFileBase :
		public ZxFileBase
	{
	protected:
		CRITICAL_SECTION&	m_IOLock;//��Ƕ�дΪ�ٽ��;
		void*		m_pDataSet;
		void*		m_pDriver;
		double		m_GeoTransformInv[6];//����ͼ��;
		double		m_GeoTransform[6];//ͼ�񵽵���;
		ZxGeoRef	m_GeoRef;
		void MakeInvTransPara();
	public:
		struct ZxIOParamPair
		{
			ZxImgFileBase* m_pFile;
			ZxImgBase::ZxImgIOParamBase* m_pIOParam;
		};
		ZxImgFileBase(CRITICAL_SECTION&);
		virtual ~ZxImgFileBase(void);
		bool IsPointIn(Zx2DPoint _point);//���ص��Ƿ���ͼ����,��ĵ�λ����ͼ�񸽼Ӳο��ĵ�λ����
		const double* GetTransformPara(bool _IsForewardPam = true);
		ZxGeoRef& GetGeoRef();
		char* GetWKT();

		virtual int GetBandCount(void);
		virtual int GetImageWidth(void);
		virtual int GetImageHeight(void);
		virtual int GetDataType(void);
		virtual int GetBPC(void);//Bit per Channel
	};

}
