#include "StdAfx.h"
#include "ZxImgFileManager.h"
#include <algorithm>


Raster::ZxImgFileManager::ZxImgFileElement::ZxImgFileElement()
	:m_ReadAccess(NULL)
	,m_WriteAccess(NULL)
	,m_OpenReadCount(0)
	,m_OpenWriteCount(0)
{
	InitializeCriticalSection(&m_IOLock);
}

Raster::ZxImgFileManager::ZxImgFileElement::~ZxImgFileElement()
{
	if (m_ReadAccess)
	{
		delete m_ReadAccess;
	}
	if (m_WriteAccess)
	{
		delete m_WriteAccess;
	}
	DeleteCriticalSection(&m_IOLock);
}

Raster::ZxImgFileManager::AutoPtrManager Raster::ZxImgFileManager::m_pManager = Raster::ZxImgFileManager::AutoPtrManager();

Raster::ZxImgFileManager::AutoPtrManager::AutoPtrManager()
	:m_pImgManager(NULL)
{

}

Raster::ZxImgFileManager::AutoPtrManager::~AutoPtrManager()
{
	if (m_pImgManager)
	{
		delete m_pImgManager;
	}
}


Raster::ZxImgFileManager::ZxImgFileManager(void)
{
}


Raster::ZxImgFileManager::~ZxImgFileManager(void)
{
	for (ZxImgFileSet::iterator iFile = m_ImgFileSet.begin();
		iFile != m_ImgFileSet.end(); iFile++)
	{
		delete iFile->second;
	}
	m_ImgFileSet.clear();
}

Raster::ZxImgFileManager* Raster::ZxImgFileManager::GetManager(void)
{
	if (m_pManager.m_pImgManager == NULL)
	{
		m_pManager.m_pImgManager = new ZxImgFileManager;
	}
	return m_pManager.m_pImgManager;
}


Raster::ZxImgFileRead* Raster::ZxImgFileManager::GetReadFile(const char* _FileName)
{
	string strFileName(_FileName);
	transform(strFileName.begin(),strFileName.end(),strFileName.begin(),tolower);
	ZxImgFileSet::iterator iFile = GetManager()->m_ImgFileSet.find(strFileName);
	if (iFile == GetManager()->m_ImgFileSet.end())
	{
		ZxImgFileElement* pElement = new ZxImgFileElement;
		GetManager()->m_ImgFileSet.insert(pair<string,ZxImgFileElement*>(strFileName,pElement));
		pElement->m_ReadAccess = new ZxImgFileRead(pElement->m_IOLock);
		if (pElement->m_ReadAccess->SetFilePath(_FileName))
		{
			pElement->m_OpenReadCount++;
			return pElement->m_ReadAccess;
		}
		else
		{
			GetManager()->m_ImgFileSet.erase(GetManager()->m_ImgFileSet.find(strFileName));
			delete pElement;
			return NULL;
		}
	}
	else
	{
		if (0 != iFile->second->m_WriteAccess)
		{
			return NULL;
		}
		else if(NULL != iFile->second->m_ReadAccess)
			return iFile->second->m_ReadAccess;
		else
		{
			ZxImgFileRead* pImgFile = new ZxImgFileRead(iFile->second->m_IOLock);
			if(pImgFile->SetFilePath(_FileName))
			{
				iFile->second->m_OpenReadCount++;
				iFile->second->m_ReadAccess = pImgFile;
				return pImgFile;
			}
			else
			{
				delete pImgFile;
				return NULL;
			}					
		}
	}
}

Raster::ZxImgFileWrite* Raster::ZxImgFileManager::GetWriteFile(const char* _FileName)
{
	string strFileName(_FileName);
	transform(strFileName.begin(),strFileName.end(),strFileName.begin(),tolower);
	ZxImgFileSet::iterator iFile = GetManager()->m_ImgFileSet.find(strFileName);
	if (iFile == GetManager()->m_ImgFileSet.end())
	{
		ZxImgFileElement* pElement = new ZxImgFileElement;
		GetManager()->m_ImgFileSet.insert(pair<string,ZxImgFileElement*>(strFileName,pElement));
		pElement->m_WriteAccess = new ZxImgFileWrite(pElement->m_IOLock);
		if (pElement->m_WriteAccess->SetFilePath(_FileName))
		{
			pElement->m_OpenWriteCount++;
			return pElement->m_WriteAccess;
		}
		else
		{
			GetManager()->m_ImgFileSet.erase(GetManager()->m_ImgFileSet.find(strFileName));
			delete pElement;
			return NULL;
		}
	}
	else
	{
		if (0 != iFile->second->m_ReadAccess)
		{
			return NULL;
		}
		else if(NULL != iFile->second->m_WriteAccess)
			return iFile->second->m_WriteAccess;
		else
		{
			ZxImgFileWrite* pImgFile = new ZxImgFileWrite(iFile->second->m_IOLock);
			if(pImgFile->SetFilePath(_FileName))
			{
				iFile->second->m_OpenWriteCount++;
				iFile->second->m_WriteAccess = pImgFile;
				return pImgFile;
			}
			else
			{
				delete pImgFile;
				return NULL;
			}					
		}
	}
}


bool Raster::ZxImgFileManager::CloseReadFile(const char* _FileName)
{
	string strFileName(_FileName);
	transform(strFileName.begin(),strFileName.end(),strFileName.begin(),tolower);
	ZxImgFileSet::iterator iFile = GetManager()->m_ImgFileSet.find(strFileName);
	if (iFile == GetManager()->m_ImgFileSet.end())
	{
		return true;
	}
	else
	{
		iFile->second->m_OpenReadCount--;
	}
	if (iFile->second->m_OpenReadCount == 0)
	{
		delete iFile->second->m_ReadAccess;
		iFile->second->m_ReadAccess = NULL;
		return true;
	}
	else
		return false;
}

bool Raster::ZxImgFileManager::CloseWriteFile(const char* _FileName)
{
	string strFileName(_FileName);
	transform(strFileName.begin(),strFileName.end(),strFileName.begin(),tolower);
	ZxImgFileSet::iterator iFile = GetManager()->m_ImgFileSet.find(strFileName);
	if (iFile == GetManager()->m_ImgFileSet.end())
	{
		return true;
	}
	else
	{
		iFile->second->m_OpenWriteCount--;
	}
	if (iFile->second->m_OpenWriteCount == 0)
	{
		delete iFile->second->m_WriteAccess;
		iFile->second->m_WriteAccess = NULL;
		return true;
	}
	else
		return false;
}