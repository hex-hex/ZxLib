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
		CRITICAL_SECTION&	m_IOLock;//标记读写为临界段;
		void*		m_pDataSet;
		void*		m_pDriver;
		double		m_GeoTransformInv[6];//地理到图像;
		double		m_GeoTransform[6];//图像到地理;
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
		bool IsPointIn(Zx2DPoint _point);//返回点是否在图像内,点的单位按照图像附加参考的单位处理
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
