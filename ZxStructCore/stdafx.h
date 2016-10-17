// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently

#pragma once

#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN            // Exclude rarely-used stuff from Windows headers
#endif

#include "targetver.h"

#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS      // some CString constructors will be explicit

#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions

#ifndef _AFX_NO_OLE_SUPPORT
#include <afxole.h>         // MFC OLE classes
#include <afxodlgs.h>       // MFC OLE dialog classes
#include <afxdisp.h>        // MFC Automation classes
#endif // _AFX_NO_OLE_SUPPORT

#ifndef _AFX_NO_DB_SUPPORT
#include <afxdb.h>                      // MFC ODBC database classes
#endif // _AFX_NO_DB_SUPPORT

#ifndef _AFX_NO_DAO_SUPPORT
#include <afxdao.h>                     // MFC DAO database classes
#endif // _AFX_NO_DAO_SUPPORT

#ifndef _AFX_NO_OLE_SUPPORT
#include <afxdtctl.h>           // MFC support for Internet Explorer 4 Common Controls
#endif
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>                     // MFC support for Windows Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT

#include <limits.h>
#include <float.h>
#include <omp.h>

#include "..\opencv\include\cv.h"
#include "..\opencv\include\highgui.h"
#include "..\opencv\include\cxcore.h"
#include "..\opencv\include\ml.h"
#pragma comment(lib, "..\\opencv\\lib\\opencv_highgui2410.lib")
#pragma comment(lib, "..\\opencv\\lib\\opencv_core2410.lib")
#pragma comment(lib, "..\\opencv\\lib\\opencv_imgproc2410.lib")
#pragma comment(lib, "..\\opencv\\lib\\opencv_ml2410.lib")

#include "..\vlfeat\include\vl\generic.h"

#pragma comment(lib, "..\\vlfeat\\bin\\vl.lib")

#include "math.h"
#include "../gdal/include/ogr_api.h"
#include "../gdal/include/ogr_spatialref.h"
#include "../gdal/include/ogr_geometry.h"
#include "../gdal/include/gdal_priv.h"
#pragma comment(lib, "..\\GDAL\\lib\\gdal_i.lib")
#pragma comment(lib, "..\\GDAL\\lib\\libtiff_i.lib")

#include <comdef.h>
#import <C:\\Program Files\\Common Files\\System\\ado\\msado15.dll> rename( "EOF", "AdoNSEOF" )

#define ZXSTRUCT_API __declspec(dllexport)

