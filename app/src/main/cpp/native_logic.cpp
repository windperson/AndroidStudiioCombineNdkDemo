//
// Created by windperson on 10/7/2016.
//

#include "native_logic.h"
#include "native_caller.h"
#include "JNI_Helper.h"

using namespace std;

#include <android/log.h>
#define LOG_TAG "native_logic"
#define LOGINFO(...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)

static JavaVM* vm_ref;
static jint RUNTIME_JNI_VERSION;

jint JNI_OnLoad(JavaVM* vm, void* reserved){
    vm_ref = vm;

    RUNTIME_JNI_VERSION = JNI_Helper::OnLoadJNIVersionCheck(vm);

    return RUNTIME_JNI_VERSION;
}

extern "C" {

JNIEXPORT
void Java_tw_idv_windperson_androidstudiocmakendkdemo_MainActivity_beginJNIcallJavaDemo(
        JNIEnv *env,
        jobject /* this */,
        jstring prefix) {
    //calling object method to let it call Java method
    LOGINFO("init a CPP object that will call Java method in Attached Native Thread!");
    const char* input = (*env).GetStringUTFChars(prefix, 0);
    LOGINFO("prefix=%s", input);

    JNI_Helper *helper = JNI_Helper::getInstance(vm_ref, RUNTIME_JNI_VERSION);

    Native_caller run = helper->getJavaCaller("tw/idv/windperson/androidstudiocmakendkdemo/NativeCallee");
    run.invokeJavaMethod("javaCalleeMethod", "(Ljava/lang/String;)V", input);
    env->ReleaseStringUTFChars(prefix, input);

    return;
}


JNIEXPORT
void Java_tw_idv_windperson_androidstudiocmakendkdemo_MainActivity_callJavaInMultiThreadDemo(
        JNIEnv *env,
        jclass type,
        jstring prefix_) {
    LOGINFO("init a CPP object that will call Java method in UnAttached Native Thread!");
    const char *input = env->GetStringUTFChars(prefix_, 0);
    LOGINFO("prefix=%s", input);

    // TODO

    env->ReleaseStringUTFChars(prefix_, input);
}


}







