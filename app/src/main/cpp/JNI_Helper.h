#ifndef Include_JNI_Helper_H
#define Include_JNI_Helper_H


#include <jni.h>
#include <string>
#include "native_caller.h"

struct ThreadedClassLoader{
    jobject ClassLoader;
    jmethodID FindClassMethod;

};

class Native_caller;

class JNI_Helper {
private:
    static JNI_Helper *singleton;
    JavaVM *_vm;
    jint _jni_ver;
    JNI_Helper(JavaVM* vm, jint jni_version);

public:
    static jint OnLoadJNIVersionCheck(JavaVM *vm);
    static JNI_Helper* getInstance(JavaVM* vm, jint jni_version);
    static jint determineJNI_Env_Valid(JavaVM *vm, JNIEnv *env, jint jni_version);
    static bool cleanupJNIEnv(JNIEnv *jniEnv, bool isDetached);
    Native_caller getJavaCaller(std::string classFullName);
    ~JNI_Helper();

    ThreadedClassLoader threadedClassLoader;
    void setupThreadedClassLoader(JNIEnv *env, const char *classFullName);
    JNIEnv *getJNIEnv(bool* isDetached);
    jclass findClass(const char* name, JNIEnv *env);
};



#endif