//
// Created by Administrator on 2020/9/4.
//

#ifndef MYDEMOFFMPEG_MYAUDIO_H
#define MYDEMOFFMPEG_MYAUDIO_H

#include "MyQueue.h"
#include "MyPlayStatue.h"

class MyAudio {
public:
    MyQueue *queue;
    int streamIndex=-1;
    AVCodecParameters *avCodecParameters;
    AVCodecContext *codecContext;
    MyPlayStatue *statue;
public:
    MyAudio(MyPlayStatue *statue);
};


#endif //MYDEMOFFMPEG_MYAUDIO_H
