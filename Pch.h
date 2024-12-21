#pragma once
//====================================================================================================
//プリコンパイル済みヘッダー
//コンパイル時間短縮のために使用
//====================================================================================================

//====================================================================================================
//標準
//====================================================================================================
#pragma comment(lib, "winmm.lib")

#define NOMINMAX
#include <Windows.h>
#include <cassert>
#include <wrl/client.h>
#include <wrl.h>  //ComPtr

//====================================================================================================
//STL
//====================================================================================================
#include <map>
#include <set>
#include <list>
#include <array>
#include <mutex>
#include <queue>
#include <stack>
#include <atomic>
#include <bitset>
#include <chrono>
#include <future>
#include <memory>
#include <random>
#include <string>
#include <thread>
#include <vector>
#include <fstream>
#include <sstream>
#include <cassert>
#include <cstdint>
#include <iterator>
#include <iostream>
#include <typeinfo>
#include <stdexcept>
#include <algorithm>
#include <functional>
#include <filesystem>
#include <unordered_map>
#include <unordered_set>
//====================================================================================================
//DirectX
//====================================================================================================
#include <d3d12.h>
#include "d3dx12.h"
#include <dxgi1_6.h>
#include <DirectXMath.h>

#define USE_MATH_DEFINES
#include <math.h>