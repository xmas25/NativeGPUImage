//
// Created by ben622 on 2019/9/27.
//

#ifndef NATIVEGPUIMAGE_GPU_IMAGE_WEAK_PIXEL_INCLUSION_FILTER_HPP
#define NATIVEGPUIMAGE_GPU_IMAGE_WEAK_PIXEL_INCLUSION_FILTER_HPP

#include "gpu_image_3x3_texture_sampling_filter.hpp"
#define JAVA_WEAK_PIXEL_INCLUSION_FILTER "com/ben/android/library/filter/GPUImageWeakPixelInclusionFilter"

static char *WEAKPIXEL_FRAGMENT_SHADER = GET_STR(
        precision lowp float;

        varying vec2 textureCoordinate;
        varying vec2 leftTextureCoordinate;
        varying vec2 rightTextureCoordinate;

        varying vec2 topTextureCoordinate;
        varying vec2 topLeftTextureCoordinate;
        varying vec2 topRightTextureCoordinate;

        varying vec2 bottomTextureCoordinate;
        varying vec2 bottomLeftTextureCoordinate;
        varying vec2 bottomRightTextureCoordinate;

        uniform sampler2D inputImageTexture;

        void main()
        {
            float bottomLeftIntensity = texture2D(inputImageTexture, bottomLeftTextureCoordinate).r;
            float topRightIntensity = texture2D(inputImageTexture, topRightTextureCoordinate).r;
            float topLeftIntensity = texture2D(inputImageTexture, topLeftTextureCoordinate).r;
            float bottomRightIntensity = texture2D(inputImageTexture, bottomRightTextureCoordinate).r;
            float leftIntensity = texture2D(inputImageTexture, leftTextureCoordinate).r;
            float rightIntensity = texture2D(inputImageTexture, rightTextureCoordinate).r;
            float bottomIntensity = texture2D(inputImageTexture, bottomTextureCoordinate).r;
            float topIntensity = texture2D(inputImageTexture, topTextureCoordinate).r;
            float centerIntensity = texture2D(inputImageTexture, textureCoordinate).r;

            float pixelIntensitySum = bottomLeftIntensity + topRightIntensity + topLeftIntensity + bottomRightIntensity + leftIntensity + rightIntensity + bottomIntensity + topIntensity + centerIntensity;
            float sumTest = step(1.5, pixelIntensitySum);
            float pixelTest = step(0.01, centerIntensity);

            gl_FragColor = vec4(vec3(sumTest * pixelTest), 1.0);
        }
);
namespace ben{
    namespace ngp{
        class GPUImageWeakPixelInclusionFilter: public GPUImage3x3TextureSamplingFilter {
        public:
            GPUImageWeakPixelInclusionFilter();

            GPUImageWeakPixelInclusionFilter(JNIEnv *env);

            virtual void initialize(JNIEnv *env);

            virtual void mapFields();

            virtual const char *getCanonicalName() const;
        };
    }
}
#endif //NATIVEGPUIMAGE_GPU_IMAGE_WEAK_PIXEL_INCLUSION_FILTER_HPP
