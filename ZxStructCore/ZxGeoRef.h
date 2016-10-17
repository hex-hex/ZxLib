#pragma once

namespace GeoReference
{
	enum ZxRefType
	{
		Projction,
		ECR,
		Orbit,
		None
	};
	const static double g_dbangleV(3.14159265358979323846 / (23.9344696 * 3600));//������ת���ٶ�
	const static double g_dbThirdPI(3.14159265358979323846 / 3);
	const static double g_dbHalfPI(3.14159265358979323846 / 2);
	const static double g_dbPI(3.14159265358979323846);
	class ZXSTRUCT_API ZxGeoRef
	{
	//friend class ZxGeoRef;
	protected:
		void*		m_pSR;
		ZxRefType	m_Mark;
		int			m_strLength;
	public:
		ZxGeoRef(void);
		ZxGeoRef(const ZxGeoRef& _Ref);
		~ZxGeoRef(void);
		ZxGeoRef& operator=(const ZxGeoRef& rhs);
		bool operator==(const ZxGeoRef& rhs);
		void CloneFrom(ZxGeoRef* _pGeoRef);
		void Reset(void);//����ΪWGS84��ͶӰ
		void* GetData();//����ZxGeoTransʹ��
		bool SetUTM(int _Zone);
		void SetNone();//����Ϊ�޲ο���Ϣ
		bool SetTransverseMercator( double  _dbCenterLat,  
			double  _dbCenterLong,  
			double  _dbScale = 0.9996,  
			double  _dbFalseEasting = 0,  
			double  _dbFalseNorthing = 0);
		void SetECR();
		void SetOrbit();
		ZxRefType GetType() const;
		void ImportWKT(char* _StringWKT);
		char* ExportWKT() const;//������delete�ַ������ڴ�
		void SetStrLength(int _Length);
	};
}

