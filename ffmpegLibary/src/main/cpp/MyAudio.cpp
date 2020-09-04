//
// Created by Administrator on 2020/9/4.
//

#include "MyAudio.h"

MyAudio::MyAudio(MyPlayStatue *statue) {
    this->statue = statue;
    queue = new MyQueue(statue);
}
