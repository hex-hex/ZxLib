#pragma once
#include "zxfilebase.h"
using namespace File;
namespace Experience
{
	class ZXSTRUCT_API ZxLogFile :
		public ZxFileBase
	{
	private:
		static ZxLogFile g_LogFile;
	public:
		ZxLogFile(void);
		~ZxLogFile(void);
		virtual bool SetFilePath(const char* _FileName);
		bool WriteLog(const char* _strContent);
		bool WriteLog(int _nContent);
		bool WriteLog(double _dbContent);

		static bool CreateLog(const char* _FileName = NULL);
		static void ZxWriteLog(const char* _strContent);
		static void ZxWriteLog(int _nContent);
		static void ZxWriteLog(double _dbContent);
	};
}

