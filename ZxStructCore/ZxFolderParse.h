#pragma once
#include "ZxFileBase.h"
#include "ZxFolderBase.h"
#include "ZxFolderParseFilterBase.h"

namespace File
{
	class ZXSTRUCT_API ZxFolderParse
	{
	protected:
		ZxFolderBase				m_EntranceFolder;
		ZxFileList					m_FileIndex;
		ZxFolderParseFilterBase*	m_pFilter;
		void IndexFiles(void);
	public:
		ZxFolderParse(ZxFolderParseFilterBase* _pFilter);
		~ZxFolderParse(void);
		bool SetEntrance(const char* _FolderName);
		void DoParse(void);
	};
}

