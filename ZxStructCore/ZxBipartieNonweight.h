#pragma once
#include "zxboolmatrix.h"
namespace Graph
{
	class ZXSTRUCT_API ZxBipartieNonweight :
		public ZxBoolMatrix
	{
	public:
		ZxBipartieNonweight(void);
		~ZxBipartieNonweight(void);
		int DoMatch(
			unsigned int** _ppNonMatchIndexList = NULL,//δƥ�����Ԫ�������б�,��Ҫ�����ͷ��ڴ�;
			unsigned int** _ppMatchIndexList = NULL);// ƥ����,��Ҫ�����ͷ��ڴ�;
		static bool ExportChart(const ZxBipartieNonweight& _Bipartie ,const char* _ImgFileName);
	private:
		char* m_Useif;
		unsigned int* m_Link;
		inline bool Can(unsigned int _Param);
	};
}

