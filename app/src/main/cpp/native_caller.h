//
// Created by windperson on 10/10/2016.
//

#ifndef Include_Native_Caller_H
#define Include_Native_Caller_H


#include <jni.h>
#include <string>

class JNI_Helper;


class Native_caller {
private:
    JNIEnv *_env;
    std::string _classPath;
    jclass _calleeClass;
    jclass initJavaClassRef();
public:
    Native_caller(JNIEnv* jniEnv, std::string classFullName);
    ~Native_caller();
    bool Detached;
    JNI_Helper *JNIHelper;
    void invokeJavaMethod(std::string, const char* , std::string);
};

#endif