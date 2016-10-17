#pragma once
#include "ZxImgFileRead.h"
#include "ZxImgFileWrite.h"
#include <map>
#include <string>
using namespace std;
namespace Raster
{
	class ZXSTRUCT_API ZxImgFileManager
	{
	private:
		class ZxImgFileElement
		{
		public:
			ZxImgFileElement();
			~ZxImgFileElement();
			CRITICAL_SECTION m_IOLock;
			int m_OpenReadCount;
			int m_OpenWriteCount;
			ZxImgFileRead* m_ReadAccess;
			ZxImgFileWrite* m_WriteAccess;
		};
		typedef map<string,ZxImgFileElement*> ZxImgFileSet;
		class AutoPtrManager
		{
		public:
			AutoPtrManager();
			~AutoPtrManager();
			ZxImgFileManager* m_pImgManager;
		};
		ZxImgFileManager(void);
		ZxImgFileSet m_ImgFileSet;
		static AutoPtrManager m_pManager;
		static ZxImgFileManager* GetManager(void);
	public:
		virtual ~ZxImgFileManager(void);
		static ZxImgFileRead* GetReadFile(const char* _FileName);
		static ZxImgFileWrite* GetWriteFile(const char* _FileName);
		static bool CloseReadFile(const char* _FileName);
		static bool CloseWriteFile(const char* _FileName);
	};
}

