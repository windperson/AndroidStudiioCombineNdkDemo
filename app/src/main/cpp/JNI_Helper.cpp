//
// Created by windperson on 10/24/2016.
//

#include <cwchar>
#include "JNI_Helper.h"

#include <android/log.h>
#define LOG_TAG "JNI_Helper"
#define LOGINFO(...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)
#define LOGERROR(...) __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)


JNI_Helper *JNI_Helper::singleton = NULL;

JNI_Helper* JNI_Helper::getInstance(JavaVM *vm, jint jni_version) {
    if(JNI_Helper::singleton){
        return JNI_Helper::singleton;
    }
    JNI_Helper::singleton = new JNI_Helper(vm, jni_version);
    return JNI_Helper::singleton;
}

JNIEnv* JNI_Helper::getJNIEnv(bool* isDetached) {
    JNIEnv *env = NULL;
    if(isDetached != NULL){
        bool initBoolean = false;
        *isDetached = initBoolean;
    }
    jint status = JNI_Helper::determineJNI_Env_Valid(JNI_Helper::singleton->_vm, env, JNI_Helper::singleton->_jni_ver);
    if(status == JNI_EDETACHED){
        _vm->AttachCurrentThread(&env, NULL);
        *isDetached = true;
    }
    else if(status == JNI_EVERSION) {
        //
        LOGERROR("JNI_VERSION error");
    }
    else{
        jint getStatus = JNI_Helper::singleton->_vm->GetEnv((void **)&env, JNI_Helper::singleton->_jni_ver);
        if(getStatus != JNI_OK){
            LOGERROR("Cannot get JEnv");
        }
    }
    return env;
}

JNI_Helper::JNI_Helper(JavaVM *vm, jint jni_version) : _vm(vm), _jni_ver(jni_version) {
}

bool JNI_Helper::cleanupJNIEnv(JNIEnv *jniEnv, bool isDetached) {
    if(JNI_Helper::singleton){
        if(isDetached){
            jint apiStatus = JNI_Helper::singleton->_vm->DetachCurrentThread();
            return apiStatus == JNI_OK;
        }
        else{
            return true;
        }
    }
    return false;
}

Native_caller JNI_Helper::getJavaCaller(std::string classFullName) {
    bool isDetached = false;
    JNIEnv *env = getJNIEnv(&isDetached);

    Native_caller run = Native_caller(env, classFullName, JNI_Helper::singleton);
    run.Detached = isDetached;
    return run;
}

void JNI_Helper::setupThreadedClassLoader(JNIEnv *env, const char *classFullName){
    jclass targetClass = env->FindClass(classFullName);
    jclass applicationMetaClass = env->GetObjectClass(targetClass);
    jclass classLoaderClass = env->FindClass("java/lang/ClassLoader");
    jmethodID getClassLoaderMethod = env->GetMethodID(applicationMetaClass,"getClassLoader","()Ljava/lang/ClassLoader;");
    this->threadedClassLoader.ClassLoader = reinterpret_cast<jclass>( env->NewGlobalRef(
            env->CallObjectMethod(targetClass, getClassLoaderMethod)));
    this->threadedClassLoader.FindClassMethod = env->GetMethodID(classLoaderClass, "findClass", "(Ljava/lang/String;)Ljava/lang/Class;");
}

jint JNI_Helper::OnLoadJNIVersionCheck(JavaVM *vm) {
    JNIEnv *env = NULL;

    if((*vm).GetEnv((void **) &env, JNI_VERSION_1_6) == JNI_OK){
        LOGINFO("Runtime JNI Version=JNI_VERSION_1_6");
        return JNI_VERSION_1_6;
    }

    if((*vm).GetEnv((void **) &env, JNI_VERSION_1_4) == JNI_OK){
        LOGINFO("Runtime JNI Version=JNI_VERSION_1_4");
        return JNI_VERSION_1_4;
    }

    if((*vm).GetEnv((void **) &env, JNI_VERSION_1_2) == JNI_OK){
        LOGINFO("Runtime JNI Version=JNI_VERSION_1_2");
        return JNI_VERSION_1_2;
    }

    if((*vm).GetEnv((void **) &env, JNI_VERSION_1_1) == JNI_OK){
        LOGINFO("Runtime JNI Version=JNI_VERSION_1_1");
        return JNI_VERSION_1_1;
    }

    LOGERROR("CAN NOT Detect JNI Version!");
    return JNI_EVERSION;
}

jclass JNI_Helper::findClass(const char *name, JNIEnv *env) {
    return static_cast<jclass>(env->CallObjectMethod(this->threadedClassLoader.ClassLoader,
                                                     this->threadedClassLoader.FindClassMethod, env->NewStringUTF(name)));
}

jint JNI_Helper::determineJNI_Env_Valid(JavaVM *vm, JNIEnv *env, jint jni_version) {
    JNIEnv *testEnv = env;
    jint ret = JNI_OK;
    ret = (*vm).GetEnv((void **) &testEnv, jni_version);
    return ret;
}

JNI_Helper::~JNI_Helper() {
    if(this->threadedClassLoader.ClassLoader != NULL){
        bool isDetached = false;
        JNIEnv *env = getJNIEnv(&isDetached);
        env->DeleteGlobalRef(this->threadedClassLoader.ClassLoader);
        this->threadedClassLoader.ClassLoader = NULL;
    }

}
