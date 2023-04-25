#pragma once

#include <librapid/librapid.hpp>
#include <raylib.h>

#if !defined(RAYLIB_VERSION_MAJOR) || !defined(RAYLIB_VERSION_MINOR) ||                            \
  RAYLIB_VERSION_MAJOR < 4 || RAYLIB_VERSION_MINOR < 5
#	error "raylib-cpp requires at least raylib 4.5.0"
#endif

#include "color.hpp"
#include "window.hpp"
#include "line.hpp"
