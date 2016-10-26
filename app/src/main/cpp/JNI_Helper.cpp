//
// Created by windperson on 10/24/2016.
//

#include <cwchar>
#include "JNI_Helper.h"

#include <android/log.h>
#define LOG_TAG "JNI_Helper"
#define LOGINFO(...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)
#define LOGERROR(...) __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)


static JNI_Helper *singleton = NULL;

JNI_Helper* JNI_Helper::getInstance(JavaVM *vm, jint jni_version) {
    if(singleton){
        return singleton;
    }
    singleton = new JNI_Helper(vm, jni_version);
    return singleton;
}

jint determineJNI_Env_Valid(JavaVM *vm, JNIEnv *env, jint jni_version);

JNIEnv* JNI_Helper::getJNIEnv(bool* isDetached) {
    JNIEnv *env = NULL;
    bool initBoolean = false;
    *isDetached = initBoolean;
    jint status = determineJNI_Env_Valid(_vm, env, _jni_ver);
    if(status == JNI_EDETACHED){
        _vm->AttachCurrentThread(&env, 0);
        *isDetached = true;
    }
    else if(status == JNI_EVERSION) {
        //
        LOGERROR("JNI_VERSION error");
    }
    else{
        jint getStatus = _vm->GetEnv((void **)&env,_jni_ver);
        if(getStatus != JNI_OK){
            LOGERROR("Cannot get JEnv");
        }
    }
    return env;
}

JNI_Helper::JNI_Helper(JavaVM *vm, jint jni_version) : _vm(vm), _jni_ver(jni_version) {
}

Native_caller JNI_Helper::getJavaCaller(std::string classFullName) {
    bool isDetached = false;
    JNIEnv *env = getJNIEnv(&isDetached);

    Native_caller run = Native_caller(env,classFullName);
    return run;
}

bool JNI_Helper::cleanupJNIEnv(JNIEnv *jniEnv) {
    if(singleton){
        if(determineJNI_Env_Valid(singleton->_vm, jniEnv, singleton->_jni_ver) == JNI_EDETACHED){
            jint apiStatus = singleton->_vm->DetachCurrentThread();
            return apiStatus == JNI_OK;
        }
        else{
            return true;
        }
    }
    return false;
}

jint determineJNI_Env_Valid(JavaVM *vm, JNIEnv *env, jint jni_version) {
    JNIEnv *testEnv = env;
    jint ret = JNI_OK;
    ret = (*vm).GetEnv((void **) &testEnv, jni_version);
    return ret;
}






