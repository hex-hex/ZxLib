#include "StdAfx.h"
#include "ZxFileBase.h"

File::ZxFileBase::ZxFileBase(void)
	:m_fileSize(-1)
{
}


File::ZxFileBase::~ZxFileBase(void)
{
}

bool File::ZxFileBase::Existance()
{
	if (m_PhysicalPath[0] == 0)
		return false;

	CString strFileName(m_PhysicalPath);
	CFileStatus fileStatus;
	if(!CFile::GetStatus(strFileName,fileStatus))
	{
		return false;
	}
	else
	{
		m_IsFolder = false;
		m_fileSize = fileStatus.m_size;
		return true;
	}
}

bool File::ZxFileBase::SetFilePath(const char* _FileName)
{
	ZeroMemory(m_PhysicalPath,MAX_PATH);
	strcpy_s(m_PhysicalPath,MAX_PATH,_FileName);
	return Existance();
}


char* File::ZxFileBase::GetFileTitle(void)
{
	if (*m_PhysicalPath == 0)
	{
		return NULL;
	}
	else
	{
		char* charTitle = new char[_MAX_FNAME];
		_splitpath_s(m_PhysicalPath,NULL,0,NULL,0,charTitle,_MAX_FNAME,NULL,0);
		return charTitle;
	}
}


char* File::ZxFileBase::GetFileExt(void)
{
	if (*m_PhysicalPath == 0)
	{
		return NULL;
	}
	else
	{
		char* charExt = new char[_MAX_EXT];
		_splitpath_s(m_PhysicalPath,NULL,0,NULL,0,NULL,0,charExt,_MAX_EXT);
		return charExt;
	}
}

bool File::ZxFileBase::ZxCopyFile(const char* _FileSrc, const char* _FileDst, bool _OverWrite/* = false*/)
{
	return static_cast<bool>(CopyFile(_FileSrc,_FileDst,!_OverWrite));
}

bool File::ZxFileBase::ZxCreateFile(const char* _FileName, bool _Visible, bool _OverWrite)
{
	if (*_FileName == NULL)
	{
		return false;
	}
	CString strFileName(_FileName);
	CFileStatus fileStatus;
	if(CFile::GetStatus(strFileName,fileStatus))
	{
		if (fileStatus.m_attribute == CFile::readOnly)
			return false;
		if (!_OverWrite)
			return false;
	}

	CFile fileNew;
	if(!fileNew.Open(strFileName, CFile::modeCreate | CFile::modeReadWrite))
		return false;
	fileNew.Close();
	if(CFile::GetStatus(strFileName,fileStatus))
	{
		if(!_Visible)
			fileStatus.m_attribute = CFile::hidden;
		return true;
	}
	else
		return false;
}


bool File::ZxFileBase::ZxDeleteFile(const char* _FileName, bool _MakeSure)
{
	if (!_MakeSure)
	{
		return false;
	}

	if (*_FileName == NULL)
	{
		return false;
	}
	CString strFileName(_FileName);
	CFileStatus fileStatus;
	if(!CFile::GetStatus(strFileName,fileStatus))
		return false;
	else
	{
		if (fileStatus.m_attribute == CFile::readOnly)
		{
			return false;
		}
		CFile::Remove(strFileName);
		return true;
	}
}

int File::ZxFileBase::MatchFileName(ZxFileBase* _File)
{
	CString strComp1(_File->GetString());
	CString strComp2(GetString());
	return strComp1.CompareNoCase(strComp2);
}

ULONGLONG File::ZxFileBase::GetFileSize(void)
{
	return m_fileSize;
}