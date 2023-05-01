#pragma once

#ifdef MLS_PLATFORM_WINDOWS
	#define NOMINMAX
	#include <windows.h>
#endif

#include <iostream>
#include <string>
#include <memory>
#include <map>
#include <fstream>
#include <sstream>
#include <vector>
#include <string_view>
#include <type_traits>