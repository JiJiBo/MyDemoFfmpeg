//
// Created by Administrator on 2020/9/4.
//

#include "MyCallJava.h"
#include "android_log.h"

MyCallJava::MyCallJava(JavaVM *vm, JNIEnv *env, jobject obj) {
    jVm = vm;
    jenv = env;
    jobj = env->NewGlobalRef(obj);
    jlz = env->GetObjectClass(jobj);
    jmid = env->GetMethodID(jlz, "onCallParpared", "()V");
}

void MyCallJava::callJava(int type) {
    LOGE("callJava")
    if (type == MAIN_THREAD) {
        jenv->CallVoidMethod(jobj, jmid);
    } else if (type == CHILD_THREAD) {
        if (jVm->AttachCurrentThread(&jenv, 0) != JNI_OK) {
            LOGE("接触线程失败")
            return;
        }
        jenv->CallVoidMethod(jobj, jmid);
        jVm->DetachCurrentThread();
    }

}


