//
// Created by windperson on 10/7/2016.
//
#include <jni.h>

#ifndef Include_Native_Logic_H
#define Include_Native_Logic_H


extern "C"
JNIEXPORT
void Java_tw_idv_windperson_androidstudiocmakendkdemo_MainActivity_beginJNIcallJavaDemo(
        JNIEnv *env,
        jobject /* this */,
        jstring prefix);

#endif