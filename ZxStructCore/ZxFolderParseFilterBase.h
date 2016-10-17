#pragma once
#include "ZxFileAbstract.h"

namespace File
{
	class ZXSTRUCT_API ZxFolderParseFilterBase
	{
	public:
		ZxFolderParseFilterBase(void);
		~ZxFolderParseFilterBase(void);
		virtual bool IsValid(const char* _FileName);
	};

}
