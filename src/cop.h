#pragma once
#include <SDKDDKVer.h>
#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <stdexcept>
#include <chrono>

#include "directx/d3dx12.h"

#include <d3d12.h>
#include <d3dcommon.h>
#include <dxgi1_4.h>
#include <wrl/client.h>
#include <DirectXMath.h>
using namespace DirectX;

#include "cop_timer.h"
#include "cop_window.h"
#include "cop_graphics_mgr.h"
#include "cop_app.h"

