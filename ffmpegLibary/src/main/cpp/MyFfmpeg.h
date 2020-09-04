//
// Created by Administrator on 2020/9/4.
//

#ifndef MYDEMOFFMPEG_MYFFMPEG_H
#define MYDEMOFFMPEG_MYFFMPEG_H

#include "MyAudio.h"
#include "MyCallJava.h"

extern "C"
{
#include "libavformat/avformat.h"
};

class MyFfmpeg {
public:
    MyAudio *audio=NULL;
    MyPlayStatue *statue;
    MyCallJava *callJava;
    pthread_t decodeThread;
    const char *url=NULL;
    AVFormatContext *pFormatCtx = NULL;
public:
    MyFfmpeg(MyPlayStatue *statue, MyCallJava *callJava, const char *url);

    ~MyFfmpeg();

    void parpaed();

    void decodeFFmpegThread();

    void start();
};


#endif //MYDEMOFFMPEG_MYFFMPEG_H
