//
// Created by Administrator on 2020/9/4.
//

#include "MyQueue.h"
#include "android_log.h"

MyQueue::MyQueue(MyPlayStatue *statue) {
    this->statue = statue;
    pthread_mutex_init(&mutex, NULL);
    pthread_cond_init(&cont, NULL);
}

MyQueue::~MyQueue() {

}

int MyQueue::getAvPacket(AVPacket *packet) {
    pthread_mutex_lock(&mutex);

    while (this->statue != NULL && !statue->exit) {

        if (queuePacket.size() > 0) {
            AVPacket *q_packet = queuePacket.front();
            if (av_packet_ref(packet, q_packet) == 0) {
                queuePacket.pop();
//                LOGE("读取中  还剩 %d 帧", queuePacket.size())
            }
            av_packet_free(&q_packet);
            av_free(q_packet);
            q_packet = NULL;
            break;
        } else {
            pthread_cond_wait(&cont, &mutex);
        }

    }

    pthread_mutex_unlock(&mutex);
    return 0;
}

int MyQueue::putAvPacket(AVPacket *packet) {

    pthread_mutex_lock(&mutex);

    queuePacket.push(packet);
//    LOGE("解码中  总共解码 %d 帧", queuePacket.size())
    pthread_cond_signal(&cont);

    pthread_mutex_unlock(&mutex);
    return 0;
}

int MyQueue::getQueueSize() {
    int size = 0;
    pthread_mutex_lock(&mutex);
    size = queuePacket.size();
    pthread_mutex_unlock(&mutex);
    return size;
}
