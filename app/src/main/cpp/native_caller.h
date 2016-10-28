#ifndef Include_Native_Caller_H
#define Include_Native_Caller_H


#include <jni.h>
#include <string>
#include "JNI_Helper.h"

class JNI_Helper;


class Native_caller {
private:
    JNIEnv *_env;
    std::string _classPath;
    jclass _calleeClass;
    jclass initJavaClassRef();
public:
    Native_caller(JNIEnv* jniEnv, std::string classFullName, JNI_Helper *jniHelper);
    ~Native_caller();
    bool Detached;
    JNI_Helper *JNIHelper;
    void invokeJavaMethod(std::string, const char* , std::string);
};

#endif