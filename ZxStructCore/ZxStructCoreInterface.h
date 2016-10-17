#pragma once
#ifndef ZXSTRUCT_API
#define ZXSTRUCT_API __declspec(dllimport)
#endif

#include <omp.h>
#include <comdef.h>
#import <C:\\Program Files\\Common Files\\System\\ado\\msado15.dll> rename( "EOF", "AdoNSEOF" )

#include "Zx2DPoint.h"
#include "Zx3DPoint.h"
#include "ZxRectangle.h"
#include "ZxGeoTrans.h"
#include "ZxFolderParseFilterBase.h"
#include "Zxfolderparse.h"
#include "ZxBipartieNonweight.h"
#include "ZxImgFileRead.h"
#include "ZxImgFileWrite.h"
#include "ZxMatrix.h"
#include "ZxSolveModelBase.h"
#include "ZxImgFileManager.h"
#include "ZxTimeNode.h"
#include "ZxGraph.h"
#include "ZxQuadTree.h"
#include "ZxColorBase.h"
#include "ZxClassifierKNearest.h"
#include "ZxClassifierNormalBayes.h"
#include "ZxClassifierSVM.h"
#include "ZxAccessBase.h"

#ifdef _DEBUG
#pragma comment(lib,"../x64/Debug/ZxStructCore.lib")
#else
#pragma comment(lib,"../x64/Release/ZxStructCore.lib")
#endif // _DEBUG

using namespace Geometry;
using namespace GeoReference;
using namespace File;
using namespace Graph;
using namespace Raster;
using namespace Solve;
using namespace Classify;