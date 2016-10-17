#pragma once
#include "ZxFileAbstract.h"

namespace File
{
	class ZXSTRUCT_API ZxFileBase 
		: public ZxFileAbstract
	{
	protected:
		ULONGLONG m_fileSize;
		bool Existance();
	public:
		ZxFileBase(void);
		virtual ~ZxFileBase(void);
		char* GetFileTitle(void);
		char* GetFileExt(void);
		virtual bool SetFilePath(const char* _FileName);
		int MatchFileName(ZxFileBase* _File);
		ULONGLONG GetFileSize(void);
		static bool ZxCreateFile(const char* _FileName, bool _Visible = true, bool _OverWrite = false);//可见性暂时无效;
		static bool ZxDeleteFile(const char* _FileName, bool _MakeSure = false);
		static bool ZxCopyFile(const char* _FileSrc, const char* _FileDst, bool _OverWrite = false);
	};
}
