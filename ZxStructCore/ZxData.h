#pragma once
#include "ZxColorBase.h"
using namespace Raster;

namespace Classify
{
	class ZXSTRUCT_API ZxData
	{
	private:
		int		m_DataSize;//实际管理的数据尺寸
		void*	m_pHead;//CvMat的头：记录对外的数据尺寸;
		float*	m_pfData;
		int		m_TypeSize;//实际管理的类别尺寸
		float*	m_pfType;//记录类别;

	public:
		ZxData(void);
		~ZxData(void);
		ZxData(const ZxData& _Data);
		ZxData& operator= (const ZxData& _Data);
		bool Create(int _Dimension, int _Amount, bool _bReserve);
		//_bReserve标记是否保留之前的数值,其不保证新建数据范围以外的数据有效;

		void SetValue(int _Count, ZxDN* _pdnVal);//向第_Count个元素的数据，逐个float赋_pdnVal中的byte值;
		void SetType(int _Count, float  _type);
		void Clear();
		int GetDimension() const;//列数;
		int GetAmount() const;//行数;
		float* GetData(void) const;
		float* GetType(void) const;
	};
}

