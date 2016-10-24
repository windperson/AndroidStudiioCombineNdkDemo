//
// Created by windperson on 10/10/2016.
//
#include <jni.h>
#include <string>

class Native_caller {
private:
    JNIEnv *_env;
    std::string _classPath;
    jclass _calleeClass;
    jclass initJavaClassRef();
public:
    Native_caller(JNIEnv* jniEnv, std::string classFullName);
    ~Native_caller();
    void invokeJavaMethod(std::string, const char* , std::string);
};
