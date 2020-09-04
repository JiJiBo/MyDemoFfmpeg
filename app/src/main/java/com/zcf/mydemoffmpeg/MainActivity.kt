package com.zcf.mydemoffmpeg

import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import com.afollestad.assent.Permission
import com.afollestad.assent.runWithPermissions
import com.rulerbug.bugutils.Manager.BugThreadManager
import com.rulerbug.bugutils.Utils.BugDirUtils
import com.rulerbug.bugutils.Utils.BugLogUtils
import com.zcf.ffmpeglibary.FfmpegDeal
import kotlinx.android.synthetic.main.activity_main.*
import java.io.File

class MainActivity : AppCompatActivity() {

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)
        runWithPermissions(Permission.WRITE_EXTERNAL_STORAGE, Permission.READ_EXTERNAL_STORAGE) {
            val dir = BugDirUtils.getDirPathByDirName("zcf")
            val file = File(dir, "a.mp4");
            BugLogUtils.e(file.isFile)
            BugLogUtils.e(file.absolutePath)

                FfmpegDeal().load(file.absolutePath)


        }

    }
}
