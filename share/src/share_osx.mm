#include <dmsdk/sdk.h>
#include "share_private.h"

#if defined(DM_PLATFORM_OSX)

#include <AppKit/AppKit.h>
#include <Foundation/Foundation.h>

void share_items(NSArray *items) {
	NSView *sender = dmGraphics::GetNativeOSXNSView();
	NSSharingServicePicker *sharingServicePicker = [[NSSharingServicePicker alloc] initWithItems:items];
	[sharingServicePicker showRelativeToRect:[sender bounds] ofView:sender preferredEdge:NSMinYEdge];
}

void platform_share_text(const char* text) {
	NSArray *items = @[[NSString stringWithUTF8String:text]];
	share_items(items);
}

void platform_share_image(const char* image_bytes, size_t length, const char* text) {
	NSData *data = [[NSData alloc] initWithBytes:image_bytes length:length];
	NSImage *image = [[NSImage alloc] initWithData:data];
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
