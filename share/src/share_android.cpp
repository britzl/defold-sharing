#include <dmsdk/sdk.h>
#include "share_private.h"

#if defined(DM_PLATFORM_ANDROID)

namespace {
	// JNI access is only valid on an attached thread.
	struct ThreadAttacher {
		JNIEnv *env;
		bool has_attached;
		ThreadAttacher() : env(NULL), has_attached(false) {
			if (dmGraphics::GetNativeAndroidJavaVM()->GetEnv((void **)&env, JNI_VERSION_1_6) != JNI_OK) {
				dmGraphics::GetNativeAndroidJavaVM()->AttachCurrentThread(&env, NULL);
				has_attached = true;
			}
		}
		~ThreadAttacher() {
			if (has_attached) {
				if (env->ExceptionCheck()) {
					env->ExceptionDescribe();
				}
				env->ExceptionClear();
				dmGraphics::GetNativeAndroidJavaVM()->DetachCurrentThread();
			}
		}
	};

	// Dynamic Java class loading.
	struct ClassLoader {
		private:
			JNIEnv *env;
			jobject class_loader_object;
			jmethodID load_class;
		public:
			ClassLoader(JNIEnv *env) : env(env) {
				jclass activity_class = env->FindClass("android/app/NativeActivity");
				jclass class_loader_class = env->FindClass("java/lang/ClassLoader");
				jmethodID get_class_loader = env->GetMethodID(activity_class, "getClassLoader", "()Ljava/lang/ClassLoader;");
				load_class = env->GetMethodID(class_loader_class, "loadClass", "(Ljava/lang/String;)Ljava/lang/Class;");
				class_loader_object = env->CallObjectMethod(dmGraphics::GetNativeAndroidActivity(), get_class_loader);
			}
			jclass load(const char *class_name) {
				jstring class_name_string = env->NewStringUTF(class_name);
				jclass loaded_class = (jclass)env->CallObjectMethod(class_loader_object, load_class, class_name_string);
				env->DeleteLocalRef(class_name_string);
				return loaded_class;
			}
	};
}

void platform_share_text(const char* text) {
	// prepare JNI
	ThreadAttacher attacher;
	JNIEnv *env = attacher.env;
	ClassLoader class_loader = ClassLoader(env);
	jclass cls = class_loader.load("com.britzl.defold.sharing.ShareExtension");

	// call method
	jmethodID share_text = env->GetStaticMethodID(cls, "ShareText", "(Landroid/content/Context;Ljava/lang/String;)V");
	jstring text_string = env->NewStringUTF(text);
	env->CallStaticVoidMethod(cls, share_text, dmGraphics::GetNativeAndroidActivity(), text_string);
	env->DeleteLocalRef(text_string);
}

void platform_share_image(const char* image, size_t length, const char* text, const char* name) {
	// prepare JNI
	ThreadAttacher attacher;
	JNIEnv *env = attacher.env;
	ClassLoader class_loader = ClassLoader(env);
	jclass cls = class_loader.load("com.britzl.defold.sharing.ShareExtension");

	jbyteArray arr = env->NewByteArray(length);
	env->SetByteArrayRegion(arr, 0, length, (jbyte*)image);

	// call method
	jmethodID share_image = env->GetStaticMethodID(cls, "ShareImage", "(Landroid/content/Context;[BLjava/lang/String;)V");
	jstring text_string = env->NewStringUTF(text);
	env->CallStaticVoidMethod(cls, share_image, dmGraphics::GetNativeAndroidActivity(), arr, text_string);
	env->DeleteLocalRef(text_string);
}

void platform_share_file(const char* path, const char* text, const ShareFileInfo *info) {
	// prepare JNI
	ThreadAttacher attacher;
	JNIEnv *env = attacher.env;
	ClassLoader class_loader = ClassLoader(env);
	jclass cls = class_loader.load("com.britzl.defold.sharing.ShareExtension");

	// call method
	jmethodID share_image = env->GetStaticMethodID(cls, "ShareFile", "(Landroid/content/Context;Ljava/lang/String;Ljava/lang/String;)V");
	jstring path_string = env->NewStringUTF(path);
	jstring text_string = env->NewStringUTF(text);
	env->CallStaticVoidMethod(cls, share_image, dmGraphics::GetNativeAndroidActivity(), path_string, text_string);
	env->DeleteLocalRef(path_string);
	env->DeleteLocalRef(text_string);
}

#endif
