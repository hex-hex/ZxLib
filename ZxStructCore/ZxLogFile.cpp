#include "StdAfx.h"
#include "ZxLogFile.h"

Experience::ZxLogFile Experience::ZxLogFile::g_LogFile;

Experience::ZxLogFile::ZxLogFile(void)
{
}


Experience::ZxLogFile::~ZxLogFile(void)
{
}

bool Experience::ZxLogFile::SetFilePath(const char* _FileName)
{
	ZeroMemory(m_PhysicalPath,MAX_PATH);
	strcpy_s(m_PhysicalPath,MAX_PATH,_FileName);
	m_IsFolder = false;
	CString strExt(GetFileExt());
	strExt.MakeLower();
	if (strExt != _T(".zlog"))
	{
		strExt = _T(".ZLOG");
		const char* strDriver = GetDriver();
		const char* strDir = GetFolders();
		const char* strFName = GetFileTitle();
		_makepath_s(m_PhysicalPath,strDriver,strDir,strFName,strExt);
		delete[] strDriver;
		delete[] strDir;
		delete[] strFName;
	}
	return Existance();
}


bool Experience::ZxLogFile::WriteLog(const char* _strContent)
{
	CStdioFile file;
	if(!file.Open(m_PhysicalPath,CStdioFile::modeWrite))
		return false;
	file.SeekToEnd();
	CString strContent(_strContent);
	if(strContent.Right(1) != "\n")
		strContent += '\n';
	file.WriteString(strContent);
	file.Close();
	return true;
}


bool Experience::ZxLogFile::WriteLog(int _nContent)
{
	CStdioFile file;
	if(!file.Open(m_PhysicalPath,CStdioFile::modeWrite))
		return false;
	file.SeekToEnd();
	CString strContent;
	strContent.Format("%d\n",_nContent);
	file.WriteString(strContent);
	file.Close();
	return true;
}


bool Experience::ZxLogFile::WriteLog(double _dbContent)
{
	CStdioFile file;
	if(!file.Open(m_PhysicalPath,CStdioFile::modeWrite))
		return false;
	file.SeekToEnd();
	CString strContent;
	strContent.Format("%f\n",_dbContent);
	file.WriteString(strContent);
	file.Close();
	return true;
}

bool Experience::ZxLogFile::CreateLog(const char* _FileName/* = NULL*/)
{
	CString logFileName;
	if (_FileName == NULL)
	{
		logFileName.Format(_T("C:\\ZebraLog.zlog"));
	}
	else
	{
		logFileName.Format(_FileName);
	}

	if(g_LogFile.SetFilePath(logFileName))
	{
		return false;
	}
	else
	{
		CString strFileName(g_LogFile.GetString());
		CFile file;
		if(file.Open(strFileName,CFile::modeCreate))
		{
			file.Close();
			return true;
		}
		else
		{
			return false;
		}
	}
}

void Experience::ZxLogFile::ZxWriteLog(const char* _strContent)
{
	if (!g_LogFile.Existance())
	{
		CreateLog();
	}
	g_LogFile.WriteLog(_strContent);
}

void Experience::ZxLogFile::ZxWriteLog(int _nContent)
{
	if (!g_LogFile.Existance())
	{
		CreateLog();
	}
	g_LogFile.WriteLog(_nContent);
}

void Experience::ZxLogFile::ZxWriteLog(double _dbContent)
{

	if (!g_LogFile.Existance())
	{
		CreateLog();
	}
	g_LogFile.WriteLog(_dbContent);
}