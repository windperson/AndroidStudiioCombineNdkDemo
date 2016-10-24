//
// Created by windperson on 10/24/2016.
//

#include <cwchar>
#include "JNI_Helper.h"

JNI_Helper *singleton = NULL;

JNI_Helper* JNI_Helper::getInstance(JavaVM *vm, jint jni_version) {
    if(singleton){
        return singleton;
    }
    singleton = new JNI_Helper(vm, jni_version);
}

jint determineJNI_Env_Valid(JavaVM *vm, JNIEnv **env, jint jni_version);
JNIEnv* JNI_Helper::getJNIEnv(bool* isDetached) {
    JNIEnv *env;
    *isDetached = false;
    if(determineJNI_Env_Valid(_vm, &env, _jni_ver) == JNI_EDETACHED){
        _vm->AttachCurrentThread(&env, 0);
        *isDetached = true;
    }
    return env;
}

JNI_Helper::JNI_Helper(JavaVM *vm, jint jni_version) : _vm(vm), _jni_ver(jni_version) {
}

Native_caller JNI_Helper::getJavaCaller(std::string classFullName) {
    //TODO: create Native_Caller properly.
    return NULL;
}

bool JNI_Helper::cleanupJNIEnv(JNIEnv *jniEnv) {
    if(singleton){
        if(determineJNI_Env_Valid(singleton->_vm, &jniEnv, singleton->_jni_ver) == JNI_EDETACHED){
            jint apiStatus = singleton->_vm->DetachCurrentThread();
            return apiStatus == JNI_OK;
        }
        else{
            return true;
        }
    }
    return false;
}

jint determineJNI_Env_Valid(JavaVM *vm, JNIEnv **env, jint jni_version) {
    jint ret = JNI_OK;
    ret = (*vm).GetEnv((void **) &env, jni_version);
    return ret;
}






