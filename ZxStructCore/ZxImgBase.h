#pragma once
#include "ZxRectangle.h"
#include "ZxColorBase.h"

using namespace Geometry;
namespace Raster
{
	class ZXSTRUCT_API ZxImgBase
	{
	protected:
		unsigned int	m_Channel;
		unsigned int	m_Height;
		unsigned int	m_Width;
		unsigned int	m_Widthstep;
		unsigned int	m_BitPerPixel;
		unsigned int	m_imgMemSize;
		unsigned char*	m_imgData;
		bool	m_bManaged;	//标记内存是否由该对象管理，若托管则析构时不释放内存;
	public:
		class ZXSTRUCT_API ZxImgIOParamBase
		{
		public:
			ZxImgIOParamBase();
			virtual ~ZxImgIOParamBase();
			int GetMaxBand();
			int GetMaxChannel();//1,2,3,4;
			ZxIntRECT* m_pRegion;
			union
			{
				int  m_ChannelVal; 
				unsigned char m_Channel[4];
			};
		};
		ZxImgBase(void);
		ZxImgBase(const ZxImgBase& _img);
		ZxImgBase& operator = (const ZxImgBase& _img); //完整复制，而非仅复制地址
		virtual ~ZxImgBase(void);
		virtual bool CreateImg(unsigned int _Width,unsigned  int _Height,unsigned int _BitPerPixel = 32);
		virtual const unsigned int GetWidth() const;
		virtual const unsigned int GetHeight() const;
		virtual const unsigned int GetWidthStep(void) const;
		virtual const unsigned int GetDepth(void) const;//总色深，一般为32bit
		virtual const unsigned int GetMemSize(void) const;
		
		virtual unsigned char* GetLocation(unsigned int _X, unsigned int _Y) = 0;
		virtual const unsigned int GetBand(void) const;
		virtual void SetBackground(ZxDN* _Val) = 0;
		virtual void GetValue(ZxDN* _poutVal, double _dbX, double _dbY, int _BandID) const = 0;//_BandID以0为起点
		virtual void GetValue(int _X, int _Y, int _BandID, ZxDN* _poutVal) const;
		virtual void SetValue(int _X, int _Y, int _BandID, const ZxDN* _pinVal);
		virtual void MakeMonochrome(int _BandID = 0) = 0;//从0开始
		virtual ZxDN GetMean() const = 0;

		unsigned char* GetImgData(void) const;
		const bool IsManaged(void) const;
		void DetachManagement(void);

		void SetAdditionalData(const void* _lpData, int _DataLength);
	};
}

