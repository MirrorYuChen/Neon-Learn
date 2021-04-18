/*
 * @Description: 
 * @File: 
 * @Brief: 
 * @Author: chenjingyu(2458006366@qq.com)
 * @version: v0.1.0
 * @Date: 2021-04-19 00:58:18
 */
#include "BoxFilter.hpp"
#include <algorithm>

namespace Mirror {
void BoxFilter::Filter(float* in, float* out) {
    for (int h = 0; h < height_; ++h) {
        int shift = h * width_;
        for (int w = 0; w < width_; ++w) {
            int start_h = std::max(0, h - radius_);
            int end_h   = std::min(height_ - 1, h + radius_);
            int start_w = std::max(0, w - radius_);
            int end_w   = std::min(width_ - 1, w + radius_);

            float tmp = 0.0f;
            for (int rh = start_h; rh <= end_h; ++rh) {
                for (int rw = start_w; rw <= end_w; ++rw) {
                    tmp += in[rh * width_ + rw];
                }
            }
            out[shift + w] = tmp;
        }
    }
}

void BoxFilter::FastFilterV1(float* in, float* out) {
    auto data_ptr = cache_.data();
    // sum horizonal
    for (int h = 0; h < height_; ++h) {
        int shift = h * width_;
        for (int w = 0; w < width_; ++w) {
            int start_w = std::max(0, w - radius_);
            int end_w   = std::min(width_ - 1, w + radius_);
            float tmp = 0.0f;
            for (int rw = start_w; rw <= end_w; ++rw) {
                tmp += in[shift + w];
            }
            data_ptr[shift + w] = tmp;
        }
    }
    // sum vertical
    for (int h = 0; h < height_; ++h) {
        int shift = h * width_;
        int start_h = std::max(0, h - radius_);
        int end_h   = std::min(height_ - 1, h + radius_);

        for (int rh = start_h; rh <= end_h; ++rh) {
            int out_shift = rh * width_;
            for (int w = 0; w < width_; ++w) {
                out[out_shift + w] += data_ptr[shift + w];
            }
        }
    }
}

void BoxFilter::FastFilterV2(float* in, float* out) {

}

void BoxFilter::FastFilterV2NeonIntrinsic(float* in, float* out) {

}

void BoxFilter::FastFilterV2NeonAsmV1(float* in, float* out) {

}

void BoxFilter::FastFilterV2NeonAsmV2(float* in, float* out) {

}


} // namespace Mirror