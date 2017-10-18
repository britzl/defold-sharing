#include <dmsdk/sdk.h>
#include "share_private.h"

#if defined(DM_PLATFORM_OSX)

#include <AppKit/AppKit.h>
#include <Foundation/Foundation.h>

void platform_share_text(const char* text) {
	NSView *sender = dmGraphics::GetNativeOSXNSView();
	NSArray *items = @[[NSString stringWithUTF8String:text]];
	NSSharingServicePicker *sharingServicePicker = [[NSSharingServicePicker alloc] initWithItems:items];
	[sharingServicePicker showRelativeToRect:[sender bounds] ofView:sender preferredEdge:NSMinYEdge];
}

#endif
