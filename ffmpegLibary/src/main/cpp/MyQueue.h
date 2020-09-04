//
// Created by Administrator on 2020/9/4.
//

#ifndef MYDEMOFFMPEG_MYQUEUE_H
#define MYDEMOFFMPEG_MYQUEUE_H

#include "pthread.h"
#include "queue"
#include "MyPlayStatue.h"

extern "C" {
#include "libavcodec/avcodec.h"
};

class MyQueue {
public:
    std::queue<AVPacket *> queuePacket;
    pthread_mutex_t mutex;
    pthread_cond_t cont;
    MyPlayStatue *statue;
public:
    MyQueue(MyPlayStatue *statue);

    ~MyQueue();

    int getAvPacket(AVPacket *packet);

    int putAvPacket(AVPacket *packet);

    int getQueueSize();
};


#endif //MYDEMOFFMPEG_MYQUEUE_H
