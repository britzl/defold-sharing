# Defold Sharing
[Defold](https://www.defold.com) native extension to share application data using native sharing dialogs.

## System requirements
The extension currently supports OSX, iOS and Android.

## Installation
You can use the Sharing extension in your own project by adding this project as a [Defold library dependency](http://www.defold.com/manuals/libraries/). Open your game.project file and in the dependencies field under project add:

https://github.com/britzl/defold-sharing/archive/master.zip

Or point to the ZIP file of a [specific release](https://github.com/britzl/defold-sharing/releases).

## Usage

### share.text(text)
Share text using a native sharing dialog.

**PARAMETERS**
* ```text``` (string) - The text to share
