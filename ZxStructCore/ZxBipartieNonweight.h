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
			unsigned int** _ppNonMatchIndexList = NULL,//未匹配的列元素索引列表,需要自行释放内存;
			unsigned int** _ppMatchIndexList = NULL);// 匹配结果,需要自行释放内存;
		static bool ExportChart(const ZxBipartieNonweight& _Bipartie ,const char* _ImgFileName);
	private:
		char* m_Useif;
		unsigned int* m_Link;
		inline bool Can(unsigned int _Param);
	};
}

