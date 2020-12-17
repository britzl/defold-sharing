![](logo.png)

# Defold Sharing
[Defold](https://www.defold.com) native extension to share application data using native sharing dialogs.

## System requirements
The extension currently supports OSX, iOS and Android.

## Installation
You can use the Sharing extension in your own project by adding this project as a [Defold library dependency](http://www.defold.com/manuals/libraries/). Open your game.project file and in the dependencies field under project add:

https://github.com/britzl/defold-sharing/archive/master.zip

Or point to the ZIP file of a [specific release](https://github.com/britzl/defold-sharing/releases).

Starting Defold 1.2.165 the Android dependencies are resolved using the `build.gradle` file.

## Usage
The share.* namespace will be nil if the share extension isn't supported (see [System requirements](#system-requirements) above).

### share.text(text)
Share text using a native sharing dialog.

**PARAMETERS**
* ```text``` (string) - The text to share

### share.image(bytes, [text])
Share an image (with optional text) using a native sharing dialog. The image format must be supported by ```BitmapFactory.decodeByteArray()``` on Android and ```UIImage.initWithData``` on iOS/OSX. On Android the image will first be stored locally as a file and then shared using a FileProvider. In order for this to work you need to follow the additional setup steps for Android mentioned above.

**PARAMETERS**
* ``` bytes``` (string) - The image bytes to share
* ```text``` (string) - Optional text to share

### share.file(path, [text])
Share a file (with optional text) using a native sharing dialog. On Android the file will first be copied to a predefined location and then shared using a FileProvider. In order for this to work you need to follow the additional setup steps for Android mentioned above. Files are shared with their original filename and extension. This will allow iOS to offer different kinds of applications depending on the shared content.

**PARAMETERS**
* ``` path``` (string) - Full path to the file to share
* ```text``` (string) - Optional text to share
