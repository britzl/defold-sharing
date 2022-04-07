#include <dmsdk/sdk.h>
#include "share_private.h"

#if defined(DM_PLATFORM_IOS)

#include <UIKit/UIKit.h>
#include <Foundation/Foundation.h>

void share_items(NSArray *items) {
	UIWindow *window = dmGraphics::GetNativeiOSUIWindow();
	UIActivityViewController *controller = [[UIActivityViewController alloc]initWithActivityItems:items applicationActivities:nil];
	controller.modalPresentationStyle = UIModalPresentationPopover;

	UIPopoverPresentationController *popController = [controller popoverPresentationController];
	if(popController) {
		popController.permittedArrowDirections = UIPopoverArrowDirectionAny;
		popController.sourceView = dmGraphics::GetNativeiOSUIView();
		popController.sourceRect = CGRectMake(0.0, 0.0, 1.0, 1.0);
	}

	[window.rootViewController presentViewController:controller animated:YES completion:NULL];
}

void platform_share_text(const char* text) {
	NSArray *items = @[[NSString stringWithUTF8String:text]];
	share_items(items);
}

void platform_share_image(const char* image_bytes, size_t length, const char* text, const char* name) {
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

void platform_share_file(const char* path, const char* text, const char* name) {
	NSURL *url = [NSURL fileURLWithPath:[NSString stringWithUTF8String:path]];
	NSArray *items;
	if (text) {
		items = @[url, [NSString stringWithUTF8String:text]];
	}
	else {
		items = @[url];
	}
	share_items(items);
}

#endif
