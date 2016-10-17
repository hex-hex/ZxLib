#pragma once
#include "zxfilebase.h"
#include "ZxFolderParseFilterBase.h"
#include <stack>
using namespace std;

namespace File
{
	class ZxFolderBase;
	typedef stack<ZxFolderBase*> ZxFileStack;
	class ZXSTRUCT_API ZxFolderBase :
		public ZxFileAbstract
	{
	protected:
		ZxFileList m_Children;
		ZxFileList::iterator m_pIterator;
	public:
		ZxFolderBase(void);
		virtual ~ZxFolderBase(void);
		int GetSize();
		virtual bool SetFilePath(const char* _FileName);
		virtual bool ParseMe(ZxFolderParseFilterBase* _pFilter, bool _MakeTree = false);
		virtual void DestroyMe(void);
	public:
		//////////////////////////////////////////////////////////////////////////���ڱ����ļ�������
		void GotoHead(void);
		ZxFileAbstract* Next(void);
		bool GetEnd(void);
		////////////////////////�Ƽ��÷�///////////////////////////////////////////
		// 	pCurrentFolder->GotoHead();
		// 	while(pCurrentFolder->GetEnd())
		// 	{
		// 		pFileNode = pCurrentFolder->Next();
		// 
		// 		...
		// 
		// 	}
		//////////////////////////////////////////////////////////////////////////
	};

}
