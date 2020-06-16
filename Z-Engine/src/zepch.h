#pragma once

// Functions
#include <iostream>
#include <memory>
#include <utility>
#include <algorithm>
#include <functional>

// Data Structures
#include <string>
#include <sstream>
#include <vector>
#include <map>
#include <unordered_map>
#include <set>
#include <unordered_set>
#include <queue>

// Platform Specific
#ifdef ZE_PLATFORM_WINDOWS
	#include <Windows.h>
#endif

// Rendering Libs
// DirectX
#include <d3d12.h>
#include <dxgi1_6.h>
#include <D3Dcompiler.h>
#include <DirectXMath.h>
#include <DirectXPackedVector.h>
#include <DirectXColors.h>
#include "vendor/d3dx12.h"

// ZE
#include "Engine/Core.h"
#include "Engine/Logging.h"


// STUFF
#define BIT(x) (1 << x)

#define NUM_SWAP_BUFFERS 2

#define SAFE_RELEASE(p)			\
	{								\
		if ((*p))					\
		{							\
			(*p)->Release();		\
			(*p) = NULL;			\
		}							\
	}