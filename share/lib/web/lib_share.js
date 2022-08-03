var LibShare = {

    // This can be accessed from the bootstrap code in the .html file
    $ShareLibrary: {

    },

    ShareText: function (data) {
        if (navigator && navigator.share) {
            try {
                var text = UTF8ToString(data);
                var shareData = {
                    text: text
                };
                navigator.share(shareData).then().catch((err) => { console.log('Sharing Error: ' + err); });
            } catch (err) {
                console.log('Sharing Error: ' + err);
            }
        } else {
            console.log('Sharing Error: navigator.share is not supported');
        }
    },

    ShareFile: function (data, type, name, title, text, url) {
        if (navigator && navigator.share) {
            try {
                var file_data = data ? UTF8ToString(data) : '';
                var file_type = type ? UTF8ToString(type) : 'text/plain';
                var file_name = name ? UTF8ToString(name) : 'file.txt';
                var file_title = title ? UTF8ToString(title) : undefined;
                var file_text = text ? UTF8ToString(text) : undefined;
                var file_url = url ? UTF8ToString(url) : undefined;
                var shareData = {
                    files: [
                        new File([file_data], file_name, {
                            type: file_type
                        })
                    ],
                    title: file_title,
                    text: file_text,
                    url: file_url
                }
                navigator.share(shareData).then().catch((err) => { console.log('Sharing Error: ' + err); });
            } catch (err) {
                console.log('Sharing Error: ' + err);
            }
        } else {
            console.log('Sharing Error: navigator.share is not supported');
        }
    },

    ShareImage: function (data, size, text, name) {
        if (navigator && navigator.share) {
            try {
                var file_data = data ? UTF8ToString(data) : '';
                var file_text = text ? UTF8ToString(text) : undefined;
                var file_name = (name ? UTF8ToString(name) : 'file.png');

                var mime_type = null;
                var image_data = null;
                if (file_data.startsWith("data:")) {
                    // https://developer.mozilla.org/en-US/docs/Web/HTTP/Basics_of_HTTP/Data_URLs
                    var arr = file_data.split(',');
                    mime_type = arr[0].match(/:(.*?);/)[1];

                    // base64 decode
                    var bstr = atob(arr[1]);

                    // copy
                    var n = bstr.length;
                    image_data = new Uint8Array(n);
                    while (n--) {
                        image_data[n] = bstr.charCodeAt(n);
                    }
                }
                else {
                    image_data = new Uint8Array(Module.HEAPU8.buffer, data, size);
                }

                var file = new File([image_data], file_name, { type: mime_type });
                var shareData = {
                    files: [file],
                    title: file_name,
                    text: file_text
                };
                navigator.share(shareData).then().catch((err) => { console.log('Sharing Error: ' + err); });
            } catch (err) {
                console.log('Sharing Error: ' + err);
            }
        } else {
            console.log('Sharing Error: navigator.share is not supported');
        }
    },
}

autoAddDeps(LibShare, '$ShareLibrary');
mergeInto(LibraryManager.library, LibShare);