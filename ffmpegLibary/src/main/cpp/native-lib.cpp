#include <jni.h>
#include <android/native_window.h>
#include <android/native_window_jni.h>
#include <android/log.h>
#include "android_log.h"
#include "MyFfmpeg.h"


extern "C" {
#include "libavformat/avformat.h"
#include "libavcodec/avcodec.h"
#include "libswscale/swscale.h"
#include "libavutil/imgutils.h"
}

JavaVM *javaVm;
MyFfmpeg *pFfmpeg;
MyCallJava *pJava;
MyPlayStatue *pStatue;
extern "C"
JNIEXPORT void JNICALL
Java_com_zcf_ffmpeglibary_FfmpegDeal_load(JNIEnv *env, jobject thiz, jstring s) {

    pStatue = new MyPlayStatue();

    pJava = new MyCallJava(javaVm, env, thiz);

    pFfmpeg = new MyFfmpeg(pStatue, pJava, env->GetStringUTFChars(s, 0));

    pFfmpeg->parpaed();

}
extern "C"
JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM *vm, void *reserved) {
    jint result = -1;
    javaVm = vm;
    JNIEnv *env;
    if (vm->GetEnv((void **) &env, JNI_VERSION_1_4) != JNI_OK) {

        return result;
    }
    return JNI_VERSION_1_4;

}

extern "C"
JNIEXPORT void JNICALL
Java_com_zcf_ffmpeglibary_FfmpegDeal_start(JNIEnv *env, jobject thiz) {
    if (pFfmpeg != NULL) {
        pFfmpeg->start();
    }
}