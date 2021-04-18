/*
 * @Description: 
 * @File: https://github.com/Ldpe2G/ArmNeonOptimization/
 * @Brief: 
 * @Author: chenjingyu(2458006366@qq.com)
 * @version: v0.1.0
 * @Date: 2021-04-19 00:58:10
 */
#include <vector>

namespace Mirror {
class BoxFilter {
public:
    BoxFilter() {
        cache_.clear();
        col_sum_.clear();
    }
    ~BoxFilter() {
        cache_.clear();
        col_sum_.clear();
    }

    inline void Init(int height, int width, int radius) {
        height_ = height;
        width_  = width;
        radius_ = radius;
        cache_.resize(height_ * width_);
        col_sum_.resize(width_);
    }

    void Filter(float* in, float* out);
    void FastFilterV1(float* in, float* out);
    void FastFilterV2(float* in, float* out);
    void FastFilterV2NeonIntrinsic(float* in, float* out);
    void FastFilterV2NeonAsmV1(float* in, float* out);
    void FastFilterV2NeonAsmV2(float* in, float* out);

private:
    std::vector<float> cache_;
    std::vector<float> col_sum_;
    int width_ = 0;
    int height_ = 0;
    int radius_ = 1;

};
} // namespace Mirror