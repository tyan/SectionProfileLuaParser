#pragma once

#if defined(RENGA_SCRIPT_LIBRARY)
#  define RENGA_SCRIPT_EXTERNAL __declspec(dllexport)
#else
#  define RENGA_SCRIPT_EXTERNAL __declspec(dllimport)
#endif