//
// Created by isak on 10/10/2016.
//

#include "native_caller.h"

using namespace std;

#include <android/log.h>
#define LOG_TAG "native_caller"
#define LOGINFO(...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)


Native_caller::Native_caller(JNIEnv *env, string classPath) {
    this->_env = env;
    this->_classPath = classPath;
}


jclass Native_caller::initJavaClassRef() {
    jclass javaClass = this->_env->FindClass(this->_classPath.c_str());
    return (jclass) this->_env->NewGlobalRef(javaClass);
}

void Native_caller::invokeJavaMethod(string methodName, const char *methodSignatureCode,
                                    string input_arg) {
    LOGINFO("input_arg=%s", input_arg.c_str());

    jclass javaClass = this->initJavaClassRef();

    // in this demo the method signature code should be "(java/lang/String;)V"
    jmethodID javaMethodRef = this->_env->GetMethodID(javaClass, methodName.c_str(),
                                                      methodSignatureCode);

    jmethodID javaClassConstructor = this->_env->GetMethodID(javaClass, "<init>", "()V");
    jobject javaObjectRef = this->_env->NewObject(javaClass, javaClassConstructor);

    jstring arg = this->_env->NewStringUTF(input_arg.c_str());
    this->_env->CallVoidMethod(javaObjectRef, javaMethodRef, arg);
    return;
}
