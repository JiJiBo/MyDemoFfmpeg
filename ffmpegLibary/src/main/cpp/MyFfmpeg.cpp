//
// Created by Administrator on 2020/9/4.
//
#include "MyFfmpeg.h"
#include "android_log.h"

MyFfmpeg::MyFfmpeg(MyPlayStatue *statue, MyCallJava *callJava, const char *url) {
    this->statue = statue;
    this->callJava = callJava;
    this->url = url;
}

void *decodeFFmpeg(void *data) {
    MyFfmpeg *ffmpeg = (MyFfmpeg *) data;
    ffmpeg->decodeFFmpegThread();
    pthread_exit(&ffmpeg->decodeThread);
}

void MyFfmpeg::parpaed() {
    pthread_create(&decodeThread, NULL, decodeFFmpeg, this);
}

void MyFfmpeg::decodeFFmpegThread() {
    av_register_all();
    avformat_network_init();
    pFormatCtx = avformat_alloc_context();
    if (avformat_open_input(&pFormatCtx, url, NULL, NULL) != 0) {
        LOGE("打开失败  %s", url);
        return;
    }

    if (avformat_find_stream_info(pFormatCtx, NULL) < 0) {
        LOGE("寻找流失败");
        return;
    }
    LOGE("寻找流   %d",pFormatCtx->nb_streams);
    for (int i = 0; i < pFormatCtx->nb_streams; i++) {
        if (pFormatCtx->streams[i]->codecpar->codec_type == AVMEDIA_TYPE_AUDIO) {
            if (audio == NULL) {
                audio = new MyAudio(statue);
                audio->streamIndex = i;
                audio->avCodecParameters = pFormatCtx->streams[i]->codecpar;
                LOGE("寻找流 成功");
                break;
            }
        }
    }
    AVCodec *pCodec = avcodec_find_decoder(audio->avCodecParameters->codec_id);
    if (!pCodec) {
        LOGE("寻找解码器失败")
        return;
    }
    audio->codecContext = avcodec_alloc_context3(pCodec);
    if (!audio->codecContext) {
        LOGE("解析失败")
        return;
    }
    if (avcodec_parameters_to_context(audio->codecContext, audio->avCodecParameters) != 0) {
        LOGE("解析失败")
        return;
    }
    if (avcodec_open2(audio->codecContext, pCodec, 0) != 0) {
        LOGE("打开流失败")
        return;
    }
    callJava->callJava(CHILD_THREAD);
}

void MyFfmpeg::start() {
    LOGE("解码开始")
    int count = 0;
    while (1) {
        AVPacket *pAvPacket = av_packet_alloc();
        if (av_read_frame(pFormatCtx, pAvPacket) == 0) {
            if (pAvPacket->stream_index == audio->streamIndex) {
                count++;
                audio->queue->putAvPacket(pAvPacket);
            } else {
                av_packet_free(&pAvPacket);
                av_free(pAvPacket);
                pAvPacket = NULL;
            }
        } else {
            av_packet_free(&pAvPacket);
            av_free(pAvPacket);
            pAvPacket = NULL;
            break;
        }
    }
    while (audio->queue->getQueueSize() > 0) {
        AVPacket *pAvPacket = av_packet_alloc();
        audio->queue->getAvPacket(pAvPacket);
        av_packet_free(&pAvPacket);
        av_free(pAvPacket);
        pAvPacket = NULL;
    }
    LOGE("解码完成")
}