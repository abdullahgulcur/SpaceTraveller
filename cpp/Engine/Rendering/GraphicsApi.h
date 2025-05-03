#pragma once

#if PLATFORM == ANDROID
#include <GLES3/gl32.h>
#elif PLATFORM == WIN
#include "glew.h"
#endif