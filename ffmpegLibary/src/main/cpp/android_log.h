//
// Created by Administrator on 2020/9/3.
//
#include "android/log.h"
#ifndef MYCPP_ANDROID_LOG_H
#define MYCPP_ANDROID_LOG_H

#endif //MYCPP_ANDROID_LOG_H

#define LOGE(FORMAT, ...) __android_log_print(ANDROID_LOG_ERROR, "player", FORMAT, ##__VA_ARGS__);