#pragma once

#include <dmsdk/sdk.h>

extern void platform_share_text(const char* text);
extern void platform_share_image(const char* image, size_t length, const char* text, const char* name);
extern void platform_share_file(const char* path, const char* text, const char* name);
