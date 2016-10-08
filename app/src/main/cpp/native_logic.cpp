//
// Created by windperson on 10/7/2016.
//

#include "native_logic.h"

using namespace std;

#include <android/log.h>
#include <string>
#include <sstream>

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

    Native_logic run = Native_logic(env,
                                    "tw/idv/windperson/androidstudiocombinendkdemo/NativeCallee");
    run.invokeJavaMethod("javaCalleeMethod", "(Ljava/lang/String;)V", input);
    return;
}


Native_logic::Native_logic(JNIEnv *env, string classPath) {
    this->_env = env;
    this->_classPath = classPath;
}


jclass Native_logic::initJavaClassRef() {
    jclass javaClass = this->_env->FindClass(this->_classPath.c_str());
    if (!javaClass) {
        std::ostringstream str;
        str << "Java Class" << this->_classPath.c_str() << "not found";
        throw str.str();
    }
    return (jclass) this->_env->NewGlobalRef(javaClass);
}

void Native_logic::invokeJavaMethod(string methodName, const char *methodSignatureCode,
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



