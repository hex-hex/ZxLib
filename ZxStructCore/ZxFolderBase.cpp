#include "StdAfx.h"
#include "ZxFolderBase.h"


File::ZxFolderBase::ZxFolderBase(void)
{
}


File::ZxFolderBase::~ZxFolderBase(void)
{
	GotoHead();
	while(GetEnd())
	{
		delete Next();
	}
	m_Children.clear();
}

bool File::ZxFolderBase::SetFilePath(const char* _FileName)
{
	if(ZxFileAbstract::SetFilePath(_FileName))
	{
		m_IsFolder = true;
		return true;
	}
	else
		return false;
}

bool File::ZxFolderBase::ParseMe(ZxFolderParseFilterBase* _pFilter, bool _MakeTree)
{
	if (IsNull())
	{
		return false;
	}

	bool bNullFilter(false);
	if (_pFilter == NULL)
	{
		bNullFilter = true;
		_pFilter = new ZxFolderParseFilterBase;
	}

	CFileFind ffSearcher;
	CString strPath;
	CString strFile;
	strPath.Format(m_PhysicalPath);
	strPath.TrimRight();
	if (strPath.Right(1) == _T("\\"))
	{
		strPath += _T("*.*");
	}
	else
	{
		strPath += _T("\\*.*");
	}
	BOOL bExist = ffSearcher.FindFile(strPath);
	while(bExist)
	{
		bExist = ffSearcher.FindNextFile();
		strFile = ffSearcher.GetFilePath();
		if (strFile.Right(1) == _T("."))
		{
			continue;
		}
	//CString strPath();
		if (ffSearcher.IsDirectory())
		{
			if (_MakeTree)
			{
				ZxFolderBase* pFolder = new ZxFolderBase;
				pFolder->SetFilePath(strFile);
				this->m_Children.push_back(pFolder);
				pFolder->ParseMe(_pFilter,true);
			}
		}
		else
		{
			if(_pFilter->IsValid(strFile))
			{
				ZxFileBase* pFile = new ZxFileBase;
				pFile->SetFilePath(strFile);
				this->m_Children.push_back(pFile);
			}
		}
	}
	if (bNullFilter)
	{
		delete _pFilter;
	}
	return true;
}

void File::ZxFolderBase::GotoHead(void)
{
	m_pIterator = m_Children.begin();
}


File::ZxFileAbstract* File::ZxFolderBase::Next(void)
{
	return *(m_pIterator++);
}


bool File::ZxFolderBase::GetEnd(void)
{
	if (m_pIterator == m_Children.end())
		return false;
	else
		return true;
}

void File::ZxFolderBase::DestroyMe(void)
{
	GotoHead();
	while(GetEnd())
	{
		delete Next();
	}
	m_Children.clear();
}

int File::ZxFolderBase::GetSize()
{
	return m_Children.size();
}