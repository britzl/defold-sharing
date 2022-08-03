#include <dmsdk/sdk.h>
#include "share_private.h"

#if defined(DM_PLATFORM_HTML5)

extern "C"
{
	void ShareText(const char *data);
	void ShareFile(const char *file_data, const char *file_type, const char *name, const char *title, const char *text, const char *url);
	void ShareImage(const char *file_data, size_t length, const char *file_type, const char *name);
}

void platform_share_text(const char *text)
{
	ShareText(text);
}

void platform_share_image(const char *image, size_t length, const char *text, const char *name)
{
	ShareImage(image, length, text, name);
}

void platform_share_file(const char *name, const char *file_data, const ShareFileInfo *info)
{
	ShareFile(file_data, info->type, name, info->title, info->text, info->url);
}

#endif
