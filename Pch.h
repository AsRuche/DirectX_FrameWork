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
#include <iostream>
#include <cassert>

#include <wrl/client.h>

//====================================================================================================
//STL
//====================================================================================================
#include <map>
#include <unordered_map>
#include <unordered_set>
#include <string>
#include <array>
#include <vector>
#include <stack>
#include <list>
#include <iterator>
#include <queue>
#include <algorithm>
#include <memory>
#include <random>
#include <fstream>
#include <iostream>
#include <sstream>
#include <functional>
#include <thread>
#include <atomic>
#include <mutex>
#include <future>
#include <filesystem>
#include <chrono>
#include <bitset>
#include <cassert>

#define USE_MATH_DEFINES
#include <math.h>