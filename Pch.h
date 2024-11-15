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
#include <set>
#include <list>
#include <array>
#include <stack>
#include <queue>
#include <mutex>
#include <memory>
#include <random>
#include <thread>
#include <future>
#include <chrono>
#include <bitset>
#include <atomic>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <cassert>
#include <cstdint>
#include <iterator>
#include <iostream>
#include <typeinfo>
#include <algorithm>
#include <functional>
#include <filesystem>
#include <unordered_map>
#include <unordered_set>

#define USE_MATH_DEFINES
#include <math.h>