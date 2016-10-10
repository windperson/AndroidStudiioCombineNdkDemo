//
// Created by windperson on 10/7/2016.
//

#include "native_logic.h"
#include "native_caller.h"

using namespace std;

#include <android/log.h>
#define LOG_TAG "native_logic"
#define LOGINFO(...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)


extern "C"
JNIEXPORT
void Java_tw_idv_windperson_androidstudiocombinendkdemo_MainActivity_beginJNIcallJavaDemo(
        JNIEnv *env,
        jobject /* this */,
        jstring prefix) {
    //calling object method to let it call Java method
    LOGINFO("init a CPP object that will call Java method!");
    string input = (*env).GetStringUTFChars(prefix, 0);
    LOGINFO("prefix=%s", input.c_str());

    Native_caller run = Native_caller(env,
                                    "tw/idv/windperson/androidstudiocombinendkdemo/NativeCallee");
    run.invokeJavaMethod("javaCalleeMethod", "(Ljava/lang/String;)V", input);
    return;
}





