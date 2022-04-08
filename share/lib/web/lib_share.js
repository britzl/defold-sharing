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
                var file_title = title ? UTF8ToString(title) : '';
                var file_text = text ? UTF8ToString(text) : '';
                var file_url = url ? UTF8ToString(url) : '';
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

    ShareImage: function (data, text, name) {
        if (navigator && navigator.share) {
            try {
                var file_data = data ? UTF8ToString(data) : '';
                var file_text = text ? UTF8ToString(text) : '';
                var file_name = (name ? UTF8ToString(name) : 'file.png');
                var arr = file_data.split(',');
                var mime = arr[0].match(/:(.*?);/)[1];
                var bstr = atob(arr[1]);
                var n = bstr.length;
                var u8arr = new Uint8Array(n);
                while (n--) {
                    u8arr[n] = bstr.charCodeAt(n);
                }
                var file = new File([u8arr], file_name, { type: mime });
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