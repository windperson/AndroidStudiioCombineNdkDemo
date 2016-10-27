#include <jni.h>

#ifndef Include_Native_Logic_H
#define Include_Native_Logic_H

extern "C" {
JNIEXPORT void JNICALL
Java_tw_idv_windperson_androidstudiocmakendkdemo_MainActivity_callJavaInMultiThreadDemo(
        JNIEnv *env,
        jclass type,
        jstring prefix_);

JNIEXPORT void JNICALL
Java_tw_idv_windperson_androidstudiocmakendkdemo_MainActivity_beginJNIcallJavaDemo(
        JNIEnv *env,
        jobject /* this */,
        jstring prefix);

};

#endif