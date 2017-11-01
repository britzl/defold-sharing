# Defold Sharing
[Defold](https://www.defold.com) native extension to share application data using native sharing dialogs.

## System requirements
The extension currently supports OSX, iOS and Android.

## Installation
You can use the Sharing extension in your own project by adding this project as a [Defold library dependency](http://www.defold.com/manuals/libraries/). Open your game.project file and in the dependencies field under project add:

https://github.com/britzl/defold-sharing/archive/master.zip

Or point to the ZIP file of a [specific release](https://github.com/britzl/defold-sharing/releases).

## Additional steps for Android
Sharing files (images) on Android is quite a bit tricker than on iOS due to the Android permission system. The correct way to share files is via a FileProvider. In order to use the extension on Android you need to add the following to your AndroidManifest.xml file:

	<manifest>
	    ...
	    <application>
	        ...
	        <provider
	            android:name="android.support.v4.content.FileProvider"
	            android:authorities="{{android.package}}.fileprovider"
	            android:grantUriPermissions="true"
	            android:exported="false">
	            <meta-data
	                android:name="android.support.FILE_PROVIDER_PATHS"
	                android:resource="@xml/filepaths" />
	        </provider>
	        ...
	    </application>
	</manifest>

## Usage

### share.text(text)
Share text using a native sharing dialog.

**PARAMETERS**
* ```text``` (string) - The text to share

### share.image(bytes)
Share an image using a native sharing dialog. The image format must be supported by ```BitmapFactory.decodeByteArray()``` on Android and ```UIImage.initWithData``` on iOS/OSX. On Android the image will first be stored locally as a file and then shared using a FileProvider. In order for this to work you need to follow the additional setup steps for Android mentioned above.

**PARAMETERS**
* ``` bytes``` (string) - The image bytes to share
