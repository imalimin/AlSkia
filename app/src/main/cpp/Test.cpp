//
// Created by mingyi.li on 2020-05-09.
//

#include <jni.h>
#include "include/codec/SkCodec.h"
#include "include/core/SkBitmap.h"
#include "include/core/SkData.h"
#include "include/core/SkImage.h"
#include "include/core/SkCanvas.h"
#include "include/core/SkPath.h"
#include "include/core/SkFont.h"

#ifdef __cplusplus
extern "C" {
#endif

JNIEXPORT jobject JNICALL
Java_com_alimin_skia_MainActivity_test(JNIEnv *env, jobject thiz, jintArray jsize) {
    SkColorType colorType = kN32_SkColorType;
    bool requireUnpremul = false;
    SkBitmap bmp;
    sk_sp<SkData> data = SkData::MakeFromFileName("/sdcard/000000.arw");
    std::unique_ptr<SkCodec> codec = SkCodec::MakeFromData(data);
    if (!codec) {
        return nullptr;
    }

    SkImageInfo info = codec->getInfo().makeColorType(colorType);
    if (requireUnpremul && kPremul_SkAlphaType == info.alphaType()) {
        info = info.makeAlphaType(kUnpremul_SkAlphaType);
    }

    if (!bmp.tryAllocPixels(info)) {
        return nullptr;
    }

    if (SkCodec::kSuccess == codec->getPixels(info, bmp.getPixels(), bmp.rowBytes())) {
        jint *size = env->GetIntArrayElements(jsize, 0);
        size[0] = bmp.width();
        size[1] = bmp.height();
        env->ReleaseIntArrayElements(jsize, size, 0);

        auto len = bmp.computeByteSize();
        jbyteArray jbuf = env->NewByteArray(len);
        jbyte *buf = env->GetByteArrayElements(jbuf, 0);
        memcpy(buf, bmp.getPixels(), len);
        auto byteBuffer = env->NewDirectByteBuffer(buf, len);
        env->ReleaseByteArrayElements(jbuf, buf, 0);
        return byteBuffer;
    }
    return nullptr;
}


JNIEXPORT jobject JNICALL
Java_com_alimin_skia_MainActivity_testText(JNIEnv *env, jobject thiz, jintArray jsize) {
    SkBitmap bmp;
//    bmp.setInfo(SkImageInfo::Make(720, 1280, kRGBA_8888_SkColorType, kOpaque_SkAlphaType));
    bmp.allocN32Pixels(720, 1280);
    SkCanvas canvas(bmp);
    SkPaint paint;
    paint.setAntiAlias(true);
    paint.setColor(SK_ColorWHITE);
    paint.setStrokeWidth(3);
    canvas.drawColor(SK_ColorBLACK);

    SkFont font;
    font.setSize(60);

    SkString str = SkStringPrintf("Test text. 一二三四五六七八九十");
    const char *text = str.c_str();
    SkRect bounds;
    font.measureText(text, strlen(text), SkTextEncoding::kUTF8, &bounds);

    canvas.drawSimpleText(text, strlen(text), SkTextEncoding::kUTF8,
                          (bmp.width() - bounds.width()) / 2,
                          (bmp.height() + bounds.height()) / 2, font, paint);

    jint *size = env->GetIntArrayElements(jsize, 0);
    size[0] = bmp.width();
    size[1] = bmp.height();
    env->ReleaseIntArrayElements(jsize, size, 0);

    auto len = bmp.computeByteSize();
    jbyteArray jbuf = env->NewByteArray(len);
    jbyte *buf = env->GetByteArrayElements(jbuf, 0);
    memcpy(buf, bmp.getPixels(), len);
    auto byteBuffer = env->NewDirectByteBuffer(buf, len);
    env->ReleaseByteArrayElements(jbuf, buf, 0);
    return byteBuffer;
}

JNIEXPORT jobject JNICALL
Java_com_alimin_skia_MainActivity_testPath(JNIEnv *env, jobject thiz, jintArray jsize) {
    SkBitmap bmp;
//    bmp.setInfo(SkImageInfo::Make(720, 1280, kRGBA_8888_SkColorType, kOpaque_SkAlphaType));
    bmp.allocN32Pixels(720, 1280);
    SkCanvas canvas(bmp);
    SkPaint paint;
    paint.setAntiAlias(true);
    paint.setColor(SK_ColorWHITE);
    paint.setStrokeWidth(3);
    paint.setStyle(SkPaint::Style::kStroke_Style);
    canvas.drawColor(SK_ColorBLACK);

    SkPath path;
    SkPoint center = SkPoint::Make(360.f, 640.f);
    SkPoint end = SkPoint::Make(360.f, 1280.f);
    path.moveTo(0, 0);
    path.quadTo(center, end);
    canvas.drawPath(path, paint);

    jint *size = env->GetIntArrayElements(jsize, 0);
    size[0] = bmp.width();
    size[1] = bmp.height();
    env->ReleaseIntArrayElements(jsize, size, 0);

    auto len = bmp.computeByteSize();
    jbyteArray jbuf = env->NewByteArray(len);
    jbyte *buf = env->GetByteArrayElements(jbuf, 0);
    memcpy(buf, bmp.getPixels(), len);
    auto byteBuffer = env->NewDirectByteBuffer(buf, len);
    env->ReleaseByteArrayElements(jbuf, buf, 0);
    return byteBuffer;
}

#ifdef __cplusplus
}
#endif