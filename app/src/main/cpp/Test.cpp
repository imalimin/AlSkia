//
// Created by mingyi.li on 2020-05-09.
//

#include <jni.h>
#include "include/codec/SkCodec.h"
#include "include/core/SkBitmap.h"
#include "include/core/SkData.h"
#include "include/core/SkImage.h"

#ifdef __cplusplus
extern "C" {
#endif

JNIEXPORT jobject JNICALL
Java_com_alimin_skia_MainActivity_test(JNIEnv *env, jobject thiz, jintArray jsize) {
    SkColorType colorType = kN32_SkColorType;
    bool requireUnpremul = false;
    SkBitmap bmp;
    sk_sp<SkData> data = SkData::MakeFromFileName("/sdcard/000001.jpg");
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
        auto byteBuffer =  env->NewDirectByteBuffer(buf, len);
        env->ReleaseByteArrayElements(jbuf, buf, 0);
        return byteBuffer;
    }
    return nullptr;
}

#ifdef __cplusplus
}
#endif