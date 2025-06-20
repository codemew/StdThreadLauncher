/////////////////////////////////////////////////////////////////////////////
///
/// @copyright
///     Copyright [2023] <Mindteck>
///
/// @brief
///    This is the Header file of Utility class.
///
/// @authors Somnath Dutta Banik
///
//////////////////////////////////////////////////////////////////////////////
/*
  Author: Somnath Dutta Banik
  Date: 06-Nov-2023
  Description: Create Thread From Anywhere and for any class::function().
  Create and Start Thread with that specified Function -> StartStandardThreadStartFunctionAsthread.
  No restriction on Static member or Static Function. Create threads of non-Static functions.


  //todo:: arguement support for the new function created as thread.

*/
#ifndef COMMONUTILITY
#define COMMONUTILITY

#pragma once
#include <pthread.h>
#include <unistd.h>
#include <sys/time.h>
#include <iostream>
#include <string>
#include <ctime>
#include <cstdio>

namespace COMMONUTILS {

#define PRINT(x) \
      { \
          timeval curTime; \
          gettimeofday(&curTime, nullptr); \
          int milli = curTime.tv_usec; \
          char buffer[10] = "", currentTime[128] = ""; \
          strftime(buffer, sizeof(buffer), "%H:%M:%S", \
          localtime(&curTime.tv_sec)); \
          snprintf(currentTime, currentTimeSize, "%s.%03d", buffer, milli); \
          string file = __FILE__; file = \
          file.substr(file.find_last_of('/') + 1);\
          std::cout << currentTime << "," << file << ",line:" << \
          __LINE__ << "," << x << std::endl; \
      }

  template <typename T, typename T1> // NOLINT
struct FunctionArgs {
    T *obj;
    T1 fptr;
    void *arg;
};

  template <typename T, typename T1> // NOLINT
  void *PthreadStartFunction(void *arg) { // NOLINT
    FunctionArgs<T, T1> *fargs = static_cast<FunctionArgs<T, T1> *>(arg);

    // T *obj = Fargs->obj;
    // T1 fptr = Fargs->fptr;
    // (obj->*fptr)();

    (fargs->obj->*(fargs->fptr))();

    return nullptr;
  } // NOLINT

  template <typename T, typename T1> // NOLINT
  pthread_t StartStandardThreadStartFunctionAsthread(T *obj, T1 fptr, // NOLINT
                      char *threadname, pthread_attr_t *attr = nullptr ) { // NOLINT
    // PRINT("Starting as Thread Start Function: " << threadname );
    // PRINT("Starting as Thread Start Function: " << threadname );

    FunctionArgs<T, T1> *p_farg =
                new FunctionArgs<T, T1>();  // {obj, fptr, NULL};

    p_farg->obj = obj;
    p_farg->fptr = fptr;
    p_farg->arg = nullptr;

    pthread_t thread_id;

    pthread_create(&thread_id, attr, PthreadStartFunction<T, T1>,
                          reinterpret_cast<void *>(p_farg));
    // SetThreadAffinity(threadptr, threadname);
    // sleep(1);
    usleep(50*1000);
    delete p_farg;
    p_farg = nullptr;

    return thread_id;
  } // NOLINT


  //////////////////////////////////////////////////////////////////////////////
  /// @brief
  /// This method gets Tick count.
  ///
  /// @param none
  ///
  /// @return It returns Unsigned Int Value.
  //////////////////////////////////////////////////////////////////////////////
  static uint64_t getTickCount() { // NOLINT
    uint64_t val = 0;
    struct timespec *t;
    t = (struct timespec *)malloc(sizeof(timespec));
    clock_gettime(CLOCK_MONOTONIC, t);
    // Get Values in MS
    val = t->tv_sec * 1000 + t->tv_nsec * 0.000001;
    free(t);
    //  Logger::logEvent(ECGModule,
    //                   PHMString("ECG getTick count = %1").format(1, val));
    return val;
  } // NOLINT

  //////////////////////////////////////////////////////////////////////////////
  /// @brief
  /// This method gets Tick count in MicroSeconds.
  ///
  /// @param none
  ///
  /// @return It returns Unsigned Int Value.
  //////////////////////////////////////////////////////////////////////////////
  static uint64_t getTickCountInMicroSec() { // NOLINT
    uint64_t val = 0;
    struct timespec *t;
    t = (struct timespec *)malloc(sizeof(timespec));
    clock_gettime(CLOCK_MONOTONIC, t);
    // Get Values in MS
    val = t->tv_sec * 1000'000 + t->tv_nsec * 0.001;
    free(t);
    //  Logger::logEvent(ECGModule,
    //                   PHMString("ECG getTick count = %1").format(1, val));
    return val;
  } // NOLINT

    //////////////////////////////////////////////////////////////////////////////
  /// @brief
  /// This method returns time in Microsecs.
  ///
  /// @param none
  ///
  /// @return It returns Unsigned Int Value.
  //////////////////////////////////////////////////////////////////////////////
  // static uint64_t getTimeInMicrosec() {
  //   timeval tv;
  //   gettimeofday (&tv, NULL);
  //   return (double) (((double)tv.tv_sec * 1000000) + (double)tv.tv_usec);
  // }

  //////////////////////////////////////////////////////////////////////////////
  /// @brief
  /// This method Sleeps util Time given.
  ///
  /// @param milliSeconds, Time given
  ///
  /// @return none
  //////////////////////////////////////////////////////////////////////////////
  static void sleep(uint milliSeconds) { // NOLINT
    usleep(milliSeconds * 1000);  // Sleeps in micro seconds
  } // NOLINT
}  // namespace COMMONUTILS
#endif
