//
// Created by windperson on 10/24/2016.
//

#ifndef Include_JNI_Helper_H
#define Include_JNI_Helper_H


#include <jni.h>
#include <string>
#include "native_caller.h"


class JNI_Helper {
private:
    JavaVM *_vm;
    jint _jni_ver;
    JNI_Helper(JavaVM* vm, jint jni_version);

public:
    static jint OnLoadJNIVersionCheck(JavaVM *vm);
    static JNI_Helper* getInstance(JavaVM* vm, jint jni_version);
    static bool cleanupJNIEnv(JNIEnv *jniEnv);
    Native_caller getJavaCaller(std::string classFullName);

    JNIEnv *getJNIEnv(bool* isDetached);
};

#endif