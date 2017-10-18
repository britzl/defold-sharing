#include <dmsdk/sdk.h>
#include "share_private.h"

#if defined(DM_PLATFORM_IOS)

#include <UIKit/UIKit.h>
#include <Foundation/Foundation.h>

void platform_share_text(const char* text) {
	NSArray *items = @[[NSString stringWithUTF8String:text]];
	UIWindow *window = dmGraphics::GetNativeiOSUIWindow();
	UIActivityViewController *controller = [[UIActivityViewController alloc]initWithActivityItems:items applicationActivities:nil];
	[window.rootViewController presentViewController:controller animated:YES completion:NULL];
}

#endif
