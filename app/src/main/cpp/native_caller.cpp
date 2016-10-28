//
// Created by isak on 10/10/2016.
//

#include "native_caller.h"
#include "JNI_Helper.h"

using namespace std;

#include <android/log.h>
#define LOG_TAG "native_caller"
#define LOGINFO(...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)
#define LOGERROR(...) __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)


Native_caller::Native_caller(JNIEnv* jniEnv, std::string classFullName):
        _env(jniEnv), _classPath(classFullName) {
    this->_calleeClass = initJavaClassRef();
}

jclass Native_caller::initJavaClassRef() {
    jclass ret = NULL;
    const char *classFullName = this->_classPath.c_str();
    jclass javaClass = this->_env->FindClass(classFullName);
    jthrowable loadingEx = this->_env->ExceptionOccurred();
    if (loadingEx != NULL){
        this->_env->ExceptionClear();
        //using JNI_Helper's findClass method to try to load again.
         javaClass = this->JNIHelper->findClass(classFullName, this->_env);
    }
    ret = reinterpret_cast<jclass>( this->_env->NewGlobalRef(javaClass));
    return ret;
}

Native_caller::~Native_caller() {
    if(this->_calleeClass != NULL){
        this->_env->DeleteGlobalRef(this->_calleeClass);
    }
    bool cleanUp = JNI_Helper::cleanupJNIEnv(this->_env, this->Detached);
    if(!cleanUp){
        LOGERROR("cleanup GlobalRef failed!");
    }
}

void Native_caller::invokeJavaMethod(string methodName, const char *methodSignatureCode,
                                    string input_arg) {
    LOGINFO("input_arg=%s", input_arg.c_str());

    // in this demo the method signature code should be "(java/lang/String;)V"
    jmethodID javaMethodRef = this->_env->GetMethodID(this->_calleeClass, methodName.c_str(),
                                                      methodSignatureCode);

    jmethodID javaClassConstructor = this->_env->GetMethodID(this->_calleeClass, "<init>", "()V");
    jobject javaObjectRef = this->_env->NewObject(this->_calleeClass, javaClassConstructor);

    jstring arg = this->_env->NewStringUTF(input_arg.c_str());
    this->_env->CallVoidMethod(javaObjectRef, javaMethodRef, arg);
    if(this->_env->ExceptionCheck()){
        this->_env->ExceptionDescribe();
    }
    return;
}




