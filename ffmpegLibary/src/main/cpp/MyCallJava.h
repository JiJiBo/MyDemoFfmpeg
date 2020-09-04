//
// Created by Administrator on 2020/9/4.
//

#ifndef MYDEMOFFMPEG_MYCALLJAVA_H
#define MYDEMOFFMPEG_MYCALLJAVA_H

#include "jni.h"

#define  MAIN_THREAD  0
#define  CHILD_THREAD  1

class MyCallJava {
public:
    JavaVM *jVm;
    JNIEnv *jenv;
    jobject jobj;
    jclass jlz;
    jmethodID jmid;

public:
    MyCallJava(JavaVM *vm, JNIEnv *env, jobject obj);

    ~MyCallJava();

    void callJava(int type);
};


#endif //MYDEMOFFMPEG_MYCALLJAVA_H
