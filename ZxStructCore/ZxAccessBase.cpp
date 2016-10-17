#include "StdAfx.h"
#include "ZxAccessBase.h"


File::ZxAccessBase::ZxAccessBase(void)
{
}


File::ZxAccessBase::~ZxAccessBase(void)
{
	if(m_pConn->State)  
		m_pConn->Close();  
	if (m_pRecordset->State)
		m_pRecordset->Close();
}


bool File::ZxAccessBase::SetFilePath(const char* _FileName)
{
	if(!ZxFileBase::SetFilePath(_FileName))
	{
		memset(m_PhysicalPath,0,MAX_PATH);
		return false;
	}

	HRESULT hr;
	memset(m_strException,0,256);
	::CoInitialize(NULL);
	_bstr_t bstrConnect = "Provider=Microsoft.ACE.OLEDB.15.0;Data Source=";
	bstrConnect += m_PhysicalPath;
	bstrConnect += ";";
	hr = m_pConn.CreateInstance("ADODB.Connection");
	if(SUCCEEDED(hr))
	{
		try
		{
			hr = m_pConn->Open(bstrConnect, "", "", ADODB::adModeUnknown);
			m_pRecordset.CreateInstance("ADODB.Recordset");
		}
		catch(_com_error e)
		{
			_bstr_t strE = e.Description();
			memset(m_strException,0,256);
			memcpy_s(m_strException,256,(LPSTR)strE,strE.length() * 2 + 1);
			hr = -1;
		}
	}
	return SUCCEEDED(hr);
}

void File::ZxAccessBase::ClearAll(void)
{
	if(!m_pConn->State)  
		return;
	CString strQuery;
	CStringArray strTables;
	try
	{ 
		m_pRecordset = m_pConn->OpenSchema(ADODB::adSchemaTables);
		while(!m_pRecordset->AdoNSEOF)
		{
			_bstr_t table_name = m_pRecordset->Fields->GetItem("TABLE_NAME")->Value;
			_bstr_t table_type = m_pRecordset->Fields->GetItem("TABLE_TYPE")->Value;                                
			if ( strcmp(((LPCSTR)table_type),"TABLE")==0)
			{
				strTables.Add((LPCSTR)table_name);                
			}       
			m_pRecordset->MoveNext();     
		}
		m_pRecordset->Close();
		for (int i = 0; i != strTables.GetCount(); i++)
		{
			strQuery.Format("DROP TABLE ");
			strQuery.Append(strTables.GetAt(i));
			m_pConn->Execute(strQuery.GetBuffer(),NULL,ADODB::adExecuteNoRecords);
		}

	}
	catch(_com_error e)
	{
		_bstr_t strE = e.Description();
		memset(m_strException,0,256);
		memcpy_s(m_strException,256,(LPSTR)strE,strE.length() * 2 + 1);
	}
}

bool File::ZxAccessBase::ExecuteSQL(const char* _strSQL)
{
	bool bSuccess(true);
	try
	{
		m_pConn->Execute(_strSQL,NULL,ADODB::adExecuteNoRecords);
	}
	catch(_com_error e)
	{
		_bstr_t strE = e.Description();
		bSuccess = false;
		memset(m_strException,0,256);
		memcpy_s(m_strException,strE.length(),(LPSTR)strE,256);
	}
	return bSuccess;
}