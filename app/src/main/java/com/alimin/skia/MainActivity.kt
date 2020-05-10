package com.alimin.skia

import android.graphics.Bitmap
import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.widget.ImageView
import android.widget.TextView
import java.nio.ByteBuffer

class MainActivity : AppCompatActivity() {

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)
        System.loadLibrary("skia")
        System.loadLibrary("skia_native")

        show()
        findViewById<TextView>(R.id.textView)?.setOnClickListener {
            show()
        }
    }

    private fun show() {
        val size = IntArray(2)
        val obj = testPath(size)
        val buf = obj as ByteBuffer?
        findViewById<TextView>(R.id.textView)?.text =
            "${buf?.capacity().toString()}, ${size[0]}x${size[1]}"

        val bmp = Bitmap.createBitmap(size[0], size[1], Bitmap.Config.ARGB_8888)
        bmp.copyPixelsFromBuffer(buf)
        findViewById<ImageView>(R.id.imageView)?.setImageBitmap(bmp)
    }

    private external fun test(size: IntArray): Any?

    private external fun testText(size: IntArray): Any?

    private external fun testPath(size: IntArray): Any?
}
