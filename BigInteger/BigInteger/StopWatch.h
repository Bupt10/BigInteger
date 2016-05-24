//////////////////////////////////////////////////////////////////// 
//                          _ooOoo_                               // 
//                         o8888888o                              // 
//                         88" . "88                              // 
//                         (| ^_^ |)                              // 
//                         O\  =  /O                              // 
//                      ____/`---'\____                           // 
//                    .'  \\|     |//  `.                         // 
//                   /  \\|||  :  |||//  \                        // 
//                  /  _||||| -:- |||||-  \                       // 
//                  |   | \\\  -  /// |   |                       // 
//                  | \_|  ''\---/''  |   |                       // 
//                  \  .-\__  `-`  ___/-. /                       // 
//                ___`. .'  /--.--\  `. . ___                     // 
//              ."" '<  `.___\_<|>_/___.'  >'"".                  // 
//            | | :  `- \`.;`\ _ /`;.`/ - ` : | |                 // 
//            \  \ `-.   \_ __\ /__ _/   .-` /  /                 // 
//      ========`-.____`-.___\_____/___.-`____.-'========         // 
//                           `=---='                              // 
//      ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^        // 
//              佛祖保佑       永无BUG     永不修改               // 
//////////////////////////////////////////////////////////////////// 


#ifndef StopWatch_h__
#define StopWatch_h__

#pragma once

// platform
#ifdef _WIN32
#define _WINDOWS_PLATFORMS_
#elif defined(__linux__)
#define _LINUX_PLATFORMS_
#endif

#include<iostream>
#include<time.h>
#include<ctime>
#include<stdio.h>

#if defined( _WINDOWS_PLATFORMS_)
#include <Windows.h>
#endif

using namespace std;
/*
使用方法:
    StopWatch sw;
    sw.start();
    double sec = sw.seconds();

*/

//struct timespec {
//	time_t tv_sec; // seconds
//	long tv_nsec; // nanoseconds
//};

// 秒表
class StopWatch  
{
private:
#if defined( _WINDOWS_PLATFORMS_)
    LARGE_INTEGER begin_;
    LARGE_INTEGER counter_;
    LARGE_INTEGER freq_;
#elif defined(_LINUX_PLATFORMS_) 
    timespec begin_;
    timespec counter_;
#endif
    bool running_;

public:
    StopWatch(): running_(false) {
#if defined( _WINDOWS_PLATFORMS_)
        QueryPerformanceFrequency(&freq_); 
#endif
        reset(); 
    }

    void reset() {
#if defined( _WINDOWS_PLATFORMS_)
        begin_.QuadPart =  counter_.QuadPart = 0; 
#elif defined(_LINUX_PLATFORMS_) 
        begin_.tv_sec =  counter_.tv_sec = 0; 
        begin_.tv_nsec =  counter_.tv_nsec = 0; 
#endif
        running_ = false; 
    }

    void re_start() {
        reset();
        start();
    }

    void start() {
        if(!running_) { 
            running_ = true;
#if defined( _WINDOWS_PLATFORMS_)
            ::QueryPerformanceCounter(&begin_);
#elif defined(_LINUX_PLATFORMS_) 
		clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &begin_); 
#endif
        }
    }

    void stop() {
        if(running_) {
#if defined( _WINDOWS_PLATFORMS_)
            LARGE_INTEGER end;
            ::QueryPerformanceCounter(&end);
            counter_.QuadPart += end.QuadPart - begin_.QuadPart;
#elif defined(_LINUX_PLATFORMS_) 
            timespec end;
    		clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &end); 
    		timespec temp;
    		if ((end.tv_nsec-begin_.tv_nsec)<0) {
    			temp.tv_sec = end.tv_sec-begin_.tv_sec-1;
    			temp.tv_nsec = 1000000000+end.tv_nsec-begin_.tv_nsec;
    		} else {
    			temp.tv_sec = end.tv_sec-begin_.tv_sec;
    			temp.tv_nsec = end.tv_nsec-begin_.tv_nsec;
    		}

            counter_.tv_sec += temp.tv_sec; 
            counter_.tv_nsec += temp.tv_nsec; 
#endif
            running_ = false;
        }
    }

    double seconds() const {
        if(!running_) { 
#if defined( _WINDOWS_PLATFORMS_)
            return counter_.QuadPart / static_cast<double>(freq_.QuadPart);
#elif defined(_LINUX_PLATFORMS_) 
            return counter_.tv_sec +  counter_.tv_nsec / static_cast<double>(1000000000);
#endif
        } else {
#if defined( _WINDOWS_PLATFORMS_)
            LARGE_INTEGER end;
            ::QueryPerformanceCounter(&end);
            return (counter_.QuadPart + (end.QuadPart - begin_.QuadPart)) / static_cast<double>(freq_.QuadPart);
#elif defined(_LINUX_PLATFORMS_) 
            timespec end;
    		clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &end); 
    		timespec temp;
    		if ((end.tv_nsec-begin_.tv_nsec)<0) {
    			temp.tv_sec = end.tv_sec-begin_.tv_sec-1;
    			temp.tv_nsec = 1000000000+end.tv_nsec-begin_.tv_nsec;
    		} else {
    			temp.tv_sec = end.tv_sec-begin_.tv_sec;
    			temp.tv_nsec = end.tv_nsec-begin_.tv_nsec;
    		}

            return counter_.tv_sec + temp.tv_sec + temp.tv_nsec / static_cast<double>(1000000000);
#endif
        }

    }

    bool running() const { return running_; }

};//class StopWatch

#endif // StopWatch_h__
