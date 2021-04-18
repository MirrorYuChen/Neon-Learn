/*
 * @Description: 
 * @File: 
 * @Brief: 
 * @Author: chenjingyu(2458006366@qq.com)
 * @version: v0.1.0
 * @Date: 2021-01-09 14:08:58
 */
#include "AutoTimer.h"
#include <stdlib.h>
#include <string.h>
#if defined(_MSC_VER)
#include <Windows.h>
#else
#include <sys/time.h>
#endif

#include <iostream>

namespace Mirror {
Timer::Timer() {
    reset();
}

Timer::~Timer() {
    // do nothing
}

void Timer::reset() {
#if defined(_MSC_VER)
    LARGE_INTEGER time, freq;
    QueryPerformanceFrequency(&freq);
    QueryPerformanceCounter(&time);
    uint64_t sec   = time.QuadPart / freq.QuadPart;
    uint64_t usec  = (time.QuadPart % freq.QuadPart) * 1000000 / freq.QuadPart;
    last_reset_time_ = sec * 1000000 + usec;
#else
    struct timeval current;
    gettimeofday(&current, nullptr);
    last_reset_time_ = current.tv_sec * 1000000 + current.tv_usec;
#endif
}

uint64_t Timer::duration_in_us() {
#if defined(_MSC_VER)
    LARGE_INTEGER time, freq;
    QueryPerformanceCounter(&time);
    QueryPerformanceFrequency(&freq);
    uint64_t sec  = time.QuadPart / freq.QuadPart;
    uint64_t usec = (time.QuadPart % freq.QuadPart) * 1000000 / freq.QuadPart;
    auto last_time = sec * 1000000 + usec;
#else
    struct timeval current;
    gettimeofday(&current, nullptr);
    auto last_time = current.tv_sec * 1000000 + current.tv_usec;
#endif

    return last_time - last_reset_time_;
}

AutoTime::AutoTime(int line, const char* func) : Timer() {
    name_ = ::strdup(func);
    line_ = line;
}

AutoTime::~AutoTime() {
    auto time_in_us = duration_in_us();
    printf("%s, %d, cost time: %f ms\n", name_, line_, (float)time_in_us / 1000.0f);
    free(name_);
}


} // namespace AISDK