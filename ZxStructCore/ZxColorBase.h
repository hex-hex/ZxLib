#pragma once
#include <map>
namespace Raster
{
	enum ZxDNType
	{
		ZxByte,
		ZxInteger,
		ZxDouble,
		ZxFloat
	};

	union ZxDN
	{
		unsigned char m_ExportByte[8];
		unsigned int m_ExportInt32[2];
		unsigned short m_ExportInt16[4];
		float m_ExportFloat[2];
		double m_ExportDouble[1];
	};

	enum ZxColorType{
		ZxRGB,
		ZxHSV,
		ZxLab,
		ZxLuv,
		ZxXYZ
	};

	typedef std::map<float,ZxDN> ZxColorIndex;

	class ZXSTRUCT_API ZxColorBase
	{
	private:
		ZxColorType m_Type;
		struct
		{
			double m_dbVal0;
			double m_dbVal1;
			double m_dbVal2;
		};
	public:
		ZxColorBase(void);
		ZxColorBase(ZxDN& _DN);//∞¥’’GBR∂¡»Î
		ZxColorBase(const ZxColorBase& _Color);
		~ZxColorBase(void);
		void All2RGB();
		void RGB2HSV();
		void RGB2Lab();
		void RGB2XYZ();
		void RGB2Luv();
		static double DistHSV(const ZxColorBase& _Clr1, const ZxColorBase& _Clr2);
		static double DistSquare(const ZxColorBase& _Clr1, const ZxColorBase& _Clr2);
// 
// 		static ZxDN ZxDisplayColor2DN(ZxColorDisplay& _Color);
// 		static ZxDN ZxDisplayColor2DN(ZxColorDisplay* _pColor);
	};
}

