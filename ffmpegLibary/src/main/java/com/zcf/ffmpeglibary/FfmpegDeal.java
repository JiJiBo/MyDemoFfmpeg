package com.zcf.ffmpeglibary;

import android.util.Log;

import com.rulerbug.bugutils.Utils.BugLogUtils;

public class FfmpegDeal {


    static {
        System.loadLibrary("native-lib");
        System.loadLibrary("avcodec");
        System.loadLibrary("avdevice");
        System.loadLibrary("avfilter");
        System.loadLibrary("avformat");
        System.loadLibrary("avutil");
        System.loadLibrary("postproc");
        System.loadLibrary("swresample");
        System.loadLibrary("swscale");
    }

    public native void load(String url);

    public native void start();

    public void onCallParpared() {
        start();
    }
}
