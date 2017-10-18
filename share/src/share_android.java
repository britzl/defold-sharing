package com.britzl.defold.clipboard.ClipboardExtension;


import android.util.Log;
import android.content.Context;
import android.content.ClipData;

class ClipboardExtension {
	private static final String TAG = "defold";

	public static void ToClipboard(Context context, String text) {
		if (android.os.Build.VERSION.SDK_INT >= android.os.Build.VERSION_CODES.HONEYCOMB) {
			android.content.ClipboardManager clipboard = (android.content.ClipboardManager)getSystemService(CLIPBOARD_SERVICE);
			ClipData clip = ClipData.newPlainText(text, text);
			clipboard.setPrimaryClip(clip);
		}
		else {
			android.text.ClipboardManager clipboard = (android.text.ClipboardManager)getSystemService(CLIPBOARD_SERVICE);
			clipboard.setText(text);
		}
	}

	public static String FromClipboard(Context context) {
		String text = "";
		if (android.os.Build.VERSION.SDK_INT >= android.os.Build.VERSION_CODES.HONEYCOMB) {
			android.content.ClipboardManager clipboard = (android.content.ClipboardManager)getSystemService(CLIPBOARD_SERVICE);
			if (clipboard.hasPrimaryClip() && clipboard.getPrimaryClipDescription().hasMimeType(MIMETYPE_TEXT_PLAIN)) {
				ClipData.Item item = clipboard.getPrimaryClip().getItemAt(0);
				text = item.getText();
				if(text == null) {
					text = "";
				}
			}
		}
		else {
			android.text.ClipboardManager clipboard = (android.text.ClipboardManager)getSystemService(CLIPBOARD_SERVICE);
			text = clipboard.getText();
		}
		return text;
	}
}
