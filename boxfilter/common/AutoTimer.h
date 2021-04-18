/*
 * @Description: 
 * @File: 
 * @Brief: 计时程序，从MNN项目拿过来的，链接：https://github.com/alibaba/MNN/blob/master/include/MNN/AutoTime.hpp
 * @Author: chenjingyu(2458006366@qq.com)
 * @version: v0.1.0
 * @Date: 2021-01-09 14:08:44
 */
#ifndef _AUTO_TIMER_H_
#define _AUTO_TIMER_H_
#include <stdint.h>
#include <stdio.h>

namespace Mirror {
class Timer {
public:
    using self = Timer;
    Timer();
    ~Timer();
    Timer(const self&)  = delete;
    Timer(const self&&) = delete;
    Timer& operator=(const self&)   = delete;
    Timer& operator=(const self&&)  = delete;

    // reset timer
    void reset();
    // get duration (us) from init or latest reset.
    uint64_t duration_in_us();

protected:
    uint64_t last_reset_time_;
};

class AutoTime : Timer {
public:
    using self = AutoTime;
    AutoTime(int line, const char* func);
    ~AutoTime();
    AutoTime(const self&)  = delete;
    AutoTime(const self&&) = delete;
    AutoTime& operator=(const self&) = delete;
    AutoTime& operator=(const self&&) = delete;

private:
    int line_;
    char* name_;
};

} // namespace AISDK

#define AUTOTIME Mirror::AutoTime ___t(__LINE__, __func__)

#endif // AISDK_AUTO_TIMER_H_