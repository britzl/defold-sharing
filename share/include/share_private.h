#pragma once

#include <dmsdk/sdk.h>

class ShareFileInfo
{
public:
    const char *text = 0;
    const char *url = 0;
    const char *title = 0;
    const char *type = 0;
};

extern void platform_share_text(const char *text);
extern void platform_share_image(const char *image, size_t length, const char *text, const char *name);
extern void platform_share_file(const char *path, const char *text, const ShareFileInfo *info);
