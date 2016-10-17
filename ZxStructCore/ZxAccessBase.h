#pragma once
#include "ZxFileBase.h"
namespace File
{
	class ZXSTRUCT_API ZxAccessBase :
		public File::ZxFileBase
	{
	protected:
		char m_strException[256];
		ADODB::_ConnectionPtr m_pConn;
		ADODB::_RecordsetPtr m_pRecordset;
	public:
		ZxAccessBase(void);
		virtual ~ZxAccessBase(void);
		virtual void ClearAll(void);
		virtual bool SetFilePath(const char* _FileName);
		virtual bool ExecuteSQL(const char* _strSQL);
	};
}