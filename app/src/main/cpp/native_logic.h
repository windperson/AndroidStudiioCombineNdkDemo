//
// Created by windperson on 10/7/2016.
//
#include <jni.h>
#include <string>

extern "C"
JNIEXPORT
void Java_tw_idv_windperson_androidstudiocombinendkdemo_MainActivity_beginJNIcallJavaDemo(
        JNIEnv *env,
        jobject /* this */,
        jstring prefix);

#ifndef ANDROIDSTUDIOCOMBINENDKDEMO_NATIVE_LOGIC_H
#define ANDROIDSTUDIOCOMBINENDKDEMO_NATIVE_LOGIC_H


class Native_logic {
private:
    JNIEnv *_env;
    std::string _classPath;
    jclass initJavaClassRef();
public:
    Native_logic(JNIEnv*,std::string);
    void invokeJavaMethod(std::string, const char* , std::string);
};


#endif //ANDROIDSTUDIOCOMBINENDKDEMO_NATIVE_LOGIC_H
