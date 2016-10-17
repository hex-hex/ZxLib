#include "StdAfx.h"
#include "ZxFileAbstract.h"

File::ZxFileAbstract::ZxFileAbstract(void)
	:m_IsFolder(false)
{
	ZeroMemory(m_PhysicalPath,MAX_PATH);
}


File::ZxFileAbstract::~ZxFileAbstract(void)
{
}


bool lessthan(File::ZxFileAbstract* _LeftVal, File::ZxFileAbstract* _RightVal)
{
	if (_LeftVal->IsFolder() && !_RightVal->IsFolder())
	{
		return true;
	}
	else
		return false;
}


bool File::ZxFileAbstract::SetFilePath(const char* _FileName)
{
	ZeroMemory(m_PhysicalPath,MAX_PATH);
	CString strFileName(_FileName);
	strFileName.MakeLower();
	CFileStatus fileStatus;
	if(!CFile::GetStatus(strFileName,fileStatus))
		return false;
	else
	{
		strcpy_s(m_PhysicalPath,MAX_PATH,strFileName);
		return true;
	}
}


char* File::ZxFileAbstract::GetDriver(void) const
{
	if (*m_PhysicalPath == 0)
	{
		return NULL;
	}
	else
	{
		char* charDriver = new char[_MAX_DRIVE];
		_splitpath_s(m_PhysicalPath,charDriver,_MAX_DRIVE,NULL,0,NULL,0,NULL,0);
		return charDriver;
	}
}

char* File::ZxFileAbstract::GetFolders(void) const
{
	if (*m_PhysicalPath == 0)
	{
		return NULL;
	}
	else
	{
		char* charPath = new char[_MAX_DIR];
		_splitpath_s(m_PhysicalPath,NULL,0,charPath,_MAX_DIR,NULL,0,NULL,0);
		return charPath;
	}
}

bool File::ZxFileAbstract::IsFolder(void)
{
	return m_IsFolder;
}

bool File::ZxFileAbstract::IsNull(void)
{
	if (m_PhysicalPath == 0)
	{
		return true;
	}
	else
		return false;
}

const char* File::ZxFileAbstract::GetRunningPath()
{
	CString path = AfxGetApp()->m_pszHelpFilePath;   
	CString str = AfxGetApp()->m_pszExeName;   
	path=path.Left(path.GetLength()-str.GetLength()-4);
	char* pPath = new char[path.GetLength()+1];
	memcpy_s(pPath, path.GetLength()+1, path.GetBuffer(), path.GetLength() + 1);
	return pPath;
}

unsigned __int64 File::ZxFileAbstract::GetDriverFreeSpace(const ZxFileAbstract* _ioFile)
{
	ULARGE_INTEGER lpuse;   
	ULARGE_INTEGER lptotal;
	ULARGE_INTEGER lpfree;   
	GetDiskFreeSpaceEx(_ioFile->GetDriver(),&lpuse,&lptotal,&lpfree);
	return lpuse.QuadPart;
}

bool File::ZxFileAbstract::IsExistence(void)
{
	CString strFileName(m_PhysicalPath);
	CFileStatus fileStatus;
	if(!CFile::GetStatus(strFileName,fileStatus))
		return false;
	else
		return true;
}


char* File::ZxFileAbstract::GetString(void)
{
	if (*m_PhysicalPath == 0)
	{
		return NULL;
	}
	else
	{
		size_t strLength = strlen(m_PhysicalPath);
		char* strFilePath = new char[strLength + 1];
		strcpy_s(strFilePath,strLength + 1,m_PhysicalPath);
		return strFilePath;
	}
}

bool File::ZxFileAbstract::CompareName(const char* _FileName) const
{
	return strcmp(_FileName,m_PhysicalPath) == 0;
}
