#include "StdAfx.h"
#include "ZxBipartieNonweight.h"
#include "ZxImgFileManager.h"

Graph::ZxBipartieNonweight::ZxBipartieNonweight(void)
	:m_Link(NULL)
	,m_Useif(NULL)
{
}


Graph::ZxBipartieNonweight::~ZxBipartieNonweight(void)
{
}


bool Graph::ZxBipartieNonweight::ExportChart(const ZxBipartieNonweight& _Bipartie ,const char* _ImgFileName)
{
	
	Raster::ZxImgFileWrite* pIO = Raster::ZxImgFileManager::GetWriteFile(_ImgFileName);
	if (pIO == NULL)
		return false;
	pIO->CreateByte(_Bipartie.GetRow(),_Bipartie.GetCol(),3);

	Raster::ZxImg24Bit ImgChart;
	Raster::ZxDN pointColor;
	pointColor.m_ExportInt32[0]  = 0xFFFFFFFF;
	ImgChart.CreateImg(_Bipartie.GetCol(),_Bipartie.GetRow());
	ImgChart.SetBackground(&pointColor);
	Raster::ZxImgBase::ZxImgIOParamBase WriteOption;
	WriteOption.m_Channel[0] = 3;
	WriteOption.m_Channel[1] = 2;
	WriteOption.m_Channel[2] = 1;
	WriteOption.m_Channel[3] = 0;
	ZxIntRECT imgRegion(0,0,_Bipartie.GetCol(),_Bipartie.GetRow());
	WriteOption.m_pRegion = &imgRegion;
	pointColor.m_ExportInt32[0] = 0;
	for (int i = 0; i != _Bipartie.GetRow(); i++)
		for (int j = 0; j != _Bipartie.GetCol(); j++)
		{
			if (_Bipartie.GetValue(j,i))
			{
				ImgChart.SetValue(j,i,-1,&pointColor);
			}
		}	

	pIO->DoSafeWrite(&ImgChart,&WriteOption);
	return Raster::ZxImgFileManager::CloseWriteFile(_ImgFileName);
}


int Graph::ZxBipartieNonweight::DoMatch(unsigned int** _ppNonMatchIndexList,unsigned int** _ppMatchIndexList/* = NULL*/)
{
	if (IsNull())
	{
		return 0;
	}
	m_Useif = new char[GetRow()];
	m_Link = new unsigned int[GetRow()];

	memset(m_Link,0xFFFFFFFF,sizeof(unsigned int) * GetRow());
	unsigned int num(0);
	for(unsigned int i = 0;i< GetCol();i++)
	{
		memset(m_Useif,0,sizeof(char) * GetRow());
		if(Can(i))
			num++;
	}

	if (_ppNonMatchIndexList != NULL)
	{
		if(GetRow() != num)
		{
			*_ppNonMatchIndexList = new unsigned int[GetRow() - num];
			memset(*_ppNonMatchIndexList,0,sizeof(unsigned int) * (GetRow() - num));
			int ListIndex(0);
			for (int i = 0; i != GetRow(); i++)
			{
				if (m_Link[i] == 0xFFFFFFFF)
				{
					(*_ppNonMatchIndexList)[ListIndex] = i;
					ListIndex ++;
				}
			}
		}
		else
			*_ppNonMatchIndexList = NULL;
	}

	if (_ppMatchIndexList != NULL)
	{
		*_ppMatchIndexList = new unsigned int[GetRow()];
		memcpy(*_ppMatchIndexList,m_Link,sizeof(unsigned int) * GetRow());
	}

	delete[] m_Link;
	delete[] m_Useif;
	return num;
}


bool Graph::ZxBipartieNonweight::Can(unsigned int _Param)
{
	for(unsigned int i = 0; i < GetRow(); i++)
	{
		if(!m_Useif[i] && GetValue(_Param, i))
		{
			m_Useif[i] = 1;
			if(m_Link[i] == 0xFFFFFFFF || Can(m_Link[i]))
			{
				m_Link[i] = _Param;
				return true;
			}
		}
	}
	return false;
}
