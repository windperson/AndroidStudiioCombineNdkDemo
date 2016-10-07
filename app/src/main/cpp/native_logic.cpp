//
// Created by windperson on 10/7/2016.
//

#include "native_logic.h"

#include <jni.h>
#include <android/log.h>
#define LOG_TAG "natvie_logic"
#define LOGINFO(...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)

extern "C"
void Java_tw_idv_windperson_androidstudiiocombinendkdemo_MainActivity_beginJNIcallJavaDemo(JNIEnv *env, jobject /* this */) {
    //calling object method to let it call Java method
    LOGINFO("init a CPP object that will call Java method!");
    return;
}