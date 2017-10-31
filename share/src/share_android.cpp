#include <dmsdk/sdk.h>
#include "share_private.h"

#if defined(DM_PLATFORM_ANDROID)


static JNIEnv* Attach()
{
	JNIEnv* env;
	JavaVM* vm = dmGraphics::GetNativeAndroidJavaVM();
	vm->AttachCurrentThread(&env, NULL);
	return env;
}

static bool Detach(JNIEnv* env)
{
	bool exception = (bool) env->ExceptionCheck();
	env->ExceptionClear();
	JavaVM* vm = dmGraphics::GetNativeAndroidJavaVM();
	vm->DetachCurrentThread();
	return !exception;
}

namespace {
	struct AttachScope {
		JNIEnv* m_Env;
		AttachScope() : m_Env(Attach()) {
		}
		~AttachScope() {
			Detach(m_Env);
		}
	};
}

static jclass GetClass(JNIEnv* env, const char* classname)
{
	dmLogError("GetClass %s", classname);
	jclass activity_class = env->FindClass("android/app/NativeActivity");
	dmLogError("GetClass after FindClass");
	jmethodID get_class_loader = env->GetMethodID(activity_class,"getClassLoader", "()Ljava/lang/ClassLoader;");
	dmLogError("GetClass after GetMethodID");
	jobject cls = env->CallObjectMethod(dmGraphics::GetNativeAndroidActivity(), get_class_loader);
	dmLogError("GetClass after CallObjectMethod");
	jclass class_loader = env->FindClass("java/lang/ClassLoader");
	dmLogError("GetClass after FindClass");
	jmethodID find_class = env->GetMethodID(class_loader, "loadClass", "(Ljava/lang/String;)Ljava/lang/Class;");
	dmLogError("GetClass after GetMethodID");

	jstring str_class_name = env->NewStringUTF(classname);
	dmLogError("GetClass after NewStringUTF");
	jclass outcls = (jclass)env->CallObjectMethod(cls, find_class, str_class_name);
	env->DeleteLocalRef(str_class_name);
	return outcls;
}


void platform_share_text(const char* text) {
	dmLogError("platform_share_text %s", text);
	// prepare JNI
	AttachScope attachscope;
	JNIEnv* env = attachscope.m_Env;
	jclass cls = GetClass(env, "com.britzl.defold.sharing.ShareExtension");
	dmLogError("platform_share_text after GetClass");

	// call method
	jmethodID share_text = env->GetStaticMethodID(cls, "ShareText", "(Landroid/content/Context;Ljava/lang/String;)V");
	dmLogError("platform_share_text got static method");
	env->CallStaticVoidMethod(cls, share_text, dmGraphics::GetNativeAndroidActivity(), env->NewStringUTF(text));
	dmLogError("platform_share_text after jni call");
}

void platform_share_image(const char* image, size_t length) {
	// prepare JNI
	AttachScope attachscope;
	JNIEnv* env = attachscope.m_Env;
	jclass cls = GetClass(env, "com.britzl.defold.sharing.ShareExtension");
	dmLogError("platform_share_image after GetClass");

	jbyteArray arr = env->NewByteArray(length);
	env->SetByteArrayRegion(arr, 0, length, (jbyte*)image);
	dmLogError("platform_share_image created jbytearray");

	// call method
	jmethodID share_image = env->GetStaticMethodID(cls, "ShareImage", "(Landroid/content/Context;[B)V");
	dmLogError("platform_share_image GetStaticMethodID");
	env->CallStaticVoidMethod(cls, share_image, dmGraphics::GetNativeAndroidActivity(), arr);
	dmLogError("platform_share_image done");
}

#endif
