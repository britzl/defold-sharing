#include <dmsdk/sdk.h>
#include "share_private.h"

#if defined(DM_PLATFORM_HTML5)

extern "C"
{
	void ShareText(const char *data);
	void ShareFile(const char *file_data, const char *text, const char *name);
	void ShareImage(const char *file_data, const char *text, const char *name);
}

void platform_share_text(const char *text)
{
	ShareText(text);
}

void platform_share_image(const char *image, size_t length, const char *text, const char* name)
{
	ShareImage(image, text, name);
}

void platform_share_file(const char *file_data, const char *text, const char* name)
{
	ShareFile(file_data, text, name);
}

#endif
