package com.britzl.defold.sharing;


import android.util.Log;
import android.content.Context;
import android.content.Intent;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.net.Uri;
import java.io.File;
import java.nio.channels.FileChannel;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import android.support.v4.content.FileProvider;
import java.io.FileNotFoundException;
import java.io.IOException;

class ShareExtension {
	private static final String TAG = "defold";

	public static void ShareText(Context context, String text) {
		Intent shareIntent = new Intent(Intent.ACTION_SEND);
		shareIntent.putExtra(Intent.EXTRA_TEXT, text);
		shareIntent.setType("text/plain");
		context.startActivity(Intent.createChooser(shareIntent, "Share text with..."));
	}

	// https://stackoverflow.com/a/30172247/1266551
	public static void ShareImage(Context context, byte[] image, String text) {
		Bitmap bitmap = BitmapFactory.decodeByteArray(image, 0, image.length);

		// save bitmap to cache directory
		try {
			File cachePath = new File(context.getCacheDir(), "images");
			cachePath.mkdirs(); // don't forget to make the directory
			FileOutputStream stream = new FileOutputStream(cachePath + "/shared_image.png"); // overwrites this image every time
			bitmap.compress(Bitmap.CompressFormat.PNG, 100, stream);
			stream.close();
		} catch (FileNotFoundException e) {
			Log.v(TAG, "Unable to save image before sharing");
			e.printStackTrace();
			return;
		} catch (IOException e) {
			Log.v(TAG, "Unable to save image before sharing");
			e.printStackTrace();
			return;
		}

		// share it
		File imagePath = new File(context.getCacheDir(), "images");
		File newFile = new File(imagePath, "shared_image.png");
		String packageName = context.getPackageName();
		Uri contentUri = FileProvider.getUriForFile(context, packageName + ".fileprovider", newFile);
		if (contentUri != null) {
			Intent shareIntent = new Intent(Intent.ACTION_SEND);
			shareIntent.addFlags(Intent.FLAG_GRANT_READ_URI_PERMISSION); // temp permission for receiving app to read this file
			shareIntent.setDataAndType(contentUri, context.getContentResolver().getType(contentUri));
			shareIntent.putExtra(Intent.EXTRA_STREAM, contentUri);
			if (text != null && !text.isEmpty()) {
				shareIntent.putExtra(Intent.EXTRA_TEXT, text);
			}
			context.startActivity(Intent.createChooser(shareIntent, "Share image with..."));
		}
		else {
			Log.w(TAG, "Unable to get file URI for sharing");
		}
	}


	// https://stackoverflow.com/a/30172247/1266551
	public static void ShareFile(Context context, String path, String text) {

		// copy to cache directory
		File dstPath = new File(context.getCacheDir(), "files");
		File dstFile = new File(dstPath, new File(path).getName());

		FileChannel source = null;
		FileChannel destination = null;
		try {
			dstPath.mkdirs(); // don't forget to make the directory
		    source = new FileInputStream(path).getChannel();
		    destination = new FileOutputStream(dstFile).getChannel();
		    destination.transferFrom(source, 0, source.size());
		}
		catch(IOException e) {
			Log.v(TAG, "Unable to copy file before sharing");
			e.printStackTrace();
			return;
		}

		// share it
		String packageName = context.getPackageName();
		Uri contentUri = FileProvider.getUriForFile(context, packageName + ".fileprovider", dstFile);
		if (contentUri != null) {
			Intent shareIntent = new Intent(Intent.ACTION_SEND);
			shareIntent.addFlags(Intent.FLAG_GRANT_READ_URI_PERMISSION); // temp permission for receiving app to read this file
			shareIntent.setDataAndType(contentUri, context.getContentResolver().getType(contentUri));
			shareIntent.putExtra(Intent.EXTRA_STREAM, contentUri);
			if (text != null && !text.isEmpty()) {
				shareIntent.putExtra(Intent.EXTRA_TEXT, text);
			}
			context.startActivity(Intent.createChooser(shareIntent, "Share file with..."));
		}
		else {
			Log.w(TAG, "Unable to get file URI for sharing");
		}
	}

}
