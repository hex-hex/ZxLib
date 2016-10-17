#pragma once
#ifndef ZXDEVICE_API
#define ZXDEVICE_API __declspec(dllimport)
#endif

#include <d2d1.h>
#include <dwrite.h>
#include <d2d1helper.h>
#include <wincodec.h>

#pragma comment(lib, "windowscodecs.lib")
#pragma comment(lib, "d2d1.lib")
#pragma comment(lib, "dwrite.lib")
#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "d3d10_1.lib")

#include "ZxDeviceManager.h"
#include "ZxDisplay2D_GraphGroup.h"
#include "ZxDisplay2D_GraphicBrushMaker.h"
#include "ZxDisplay2D_GraphRectangle.h"
#include "ZxDisplay2D_GraphPointBase.h"
#include "ZxDisplay2D_GraphicMultiline.h"
#include "ZxDisplay2D_GraphicPolyline.h"
#include "ZxDisplay2D_GraphCharacters.h"

#ifdef _DEBUG
#pragma comment(lib,"../x64/Debug/ZxDevice.lib")
#else
#pragma comment(lib,"../x64/Release/ZxDevice.lib")
#endif // _DEBUG

using namespace Display2D;