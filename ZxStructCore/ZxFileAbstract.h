#pragma once
#include <list>
using namespace std;

namespace File
{
	class ZXSTRUCT_API ZxFileAbstract
	{
	protected:
		char m_PhysicalPath[MAX_PATH];
		bool m_IsFolder;
	public:
		ZxFileAbstract(void);
		virtual ~ZxFileAbstract(void);
		char* GetDriver(void) const;
		char* GetFolders(void) const;
		static bool lessthan(ZxFileAbstract* _LeftVal, ZxFileAbstract* _RightVal);
		virtual bool SetFilePath(const char* _FileName);
		bool CompareName(const char* _FileName) const;
		bool IsFolder(void);
		bool IsNull(void);
		bool IsExistence(void);
		char* GetString(void);	//得到的是备份，请自行释放内存;
		static const char* GetRunningPath();//得到的是备份，请自行释放内存;
		static unsigned __int64 GetDriverFreeSpace(const ZxFileAbstract*);
	};
	typedef list<ZxFileAbstract*> ZxFileList;
}

