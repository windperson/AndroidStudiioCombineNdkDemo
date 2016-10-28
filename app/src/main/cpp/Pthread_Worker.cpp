#include <cwchar>
#include <sstream>
#include "Pthread_Worker.h"


#include <android/log.h>
#define LOG_TAG "Thread_Worker"
#define LOGINFO(...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)
#define LOGERROR(...) __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)


void *Pthread_Worker::thread_work(void *args) {

    ThreadWorkerArgs *threadWorkerInput = (ThreadWorkerArgs*) args;
    LOGINFO("id=%d, input_arg=%s",threadWorkerInput->id,threadWorkerInput->input_args.c_str());
    JNI_Helper *jniHelper = threadWorkerInput->jni_helper;

    std::stringstream sstm;
    sstm << threadWorkerInput->input_args << " id=" << threadWorkerInput->id;

    std::string input =  sstm.str();

    Native_caller run = jniHelper->getJavaCaller("tw/idv/windperson/androidstudiocmakendkdemo/NativeCallee");
    run.invokeJavaMethod("javaCalleeMethod", "(Ljava/lang/String;)V", input);
    return NULL;
}



