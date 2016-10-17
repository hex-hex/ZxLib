#include "StdAfx.h"
#include "ZxFolderParse.h"

using namespace File;

ZxFolderParse::ZxFolderParse(ZxFolderParseFilterBase* _pFilter)
	:m_pFilter(_pFilter)
{
	m_FileIndex.clear();
}


ZxFolderParse::~ZxFolderParse(void)
{
	if (m_pFilter != NULL)
		delete m_pFilter;
}


bool ZxFolderParse::SetEntrance(const char* _FolderName)
{
	return m_EntranceFolder.SetFilePath(_FolderName);
}

void ZxFolderParse::DoParse(void)
{
	if(m_EntranceFolder.IsNull())
		return;
	if (m_pFilter == NULL)
	{
		m_pFilter = new ZxFolderParseFilterBase;
	}
	m_EntranceFolder.ParseMe(m_pFilter,true);
	IndexFiles();
}


void ZxFolderParse::IndexFiles(void)
{
	ZxFileStack FolderStack;
	ZxFolderBase* pCurrentFolder;
	ZxFileAbstract* pFileNode;
// 	if(FolderStack.size())
// 	{
// 		while(FolderStack.size())
// 			FolderStack.pop();
// 	}
	FolderStack.push(&m_EntranceFolder);
	while(!FolderStack.empty())
	{
		pCurrentFolder = FolderStack.top();
		FolderStack.pop();
		pCurrentFolder->GotoHead();
		while(pCurrentFolder->GetEnd())
		{
			pFileNode = pCurrentFolder->Next();
			if(pFileNode->IsFolder())
				FolderStack.push((ZxFolderBase*)pFileNode);
			else
				m_FileIndex.push_back(pFileNode);
		}
	}
}
