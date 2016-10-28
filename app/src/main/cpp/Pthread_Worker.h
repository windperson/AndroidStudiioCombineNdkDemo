#ifndef ANDROIDSTUDIOCMAKENDKDEMO_PTHREAD_WORKER_H
#define ANDROIDSTUDIOCMAKENDKDEMO_PTHREAD_WORKER_H

#include <string>
#include "JNI_Helper.h"

struct ThreadWorkerArgs {
    int id;
    std::string input_args;
    JNI_Helper *jni_helper;
};


class Pthread_Worker {
public:
    static void *thread_work(void *args);
};


#endif //ANDROIDSTUDIOCMAKENDKDEMO_PTHREAD_WORKER_H
