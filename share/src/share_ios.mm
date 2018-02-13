#include <dmsdk/sdk.h>
#include "share_private.h"

#if defined(DM_PLATFORM_IOS)

#include <UIKit/UIKit.h>
#include <Foundation/Foundation.h>

void share_items(NSArray *items) {
	UIWindow *window = dmGraphics::GetNativeiOSUIWindow();
	UIActivityViewController *controller = [[UIActivityViewController alloc]initWithActivityItems:items applicationActivities:nil];
	[window.rootViewController presentViewController:controller animated:YES completion:NULL];
}

void platform_share_text(const char* text) {
	NSArray *items = @[[NSString stringWithUTF8String:text]];
	share_items(items);
}

void platform_share_image(const char* image_bytes, size_t length, const char* text) {
	NSData *data = [[NSData alloc] initWithBytes:image_bytes length:length];
	UIImage *image = [[UIImage alloc] initWithData:data];
	NSArray *items;
	if (text) {
		items = @[image, [NSString stringWithUTF8String:text]];
	}
	else {
		items = @[image];
	}
	share_items(items);
}

#endif
