//
// This code is from the rtfs library and The Timer class in
// OpenSceneGraph, both written by Robert Osfield of OpenSceneGraph.
// "rtfs" is a real-time frame scheduler.
//
// It has been modified to provide some additional functionality for
// the SIVE Lab applications.
//
// I've also supplied a working windows timer using both the high resolution (nano-second) 
// clocks and a lower resolution (millisecond) clock.  Supplying a "true" value to the constructor
// will allow the class to use the high resolution timers.
//
// -Pete Willemsen <willemsn@d.umn.edu>
// 
//C++ header - Open Scene Graph - Copyright (C) 1998-2001 Robert Osfield
//Distributed under the terms of the GNU Library General Public License (LGPL)
//as published by the Free Software Foundation.

#ifndef __SIVELAB_TIMER_H__
#define __SIVELAB_TIMER_H__ 1

#include <cstdio>
#include <cstdlib>

// #include "util/sive-util_export.h"

namespace sivelab
{

#if defined(_MSC_VER)
  typedef __int64 Timer_t;
#else
  typedef unsigned long long Timer_t;
#endif



  class Timer {
  
  public:
    
    Timer(bool enable_high_res_timer=false);
    ~Timer() {}
    
    Timer_t tic() const;
    
    double deltas( Timer_t t1, Timer_t t2 ) const;
    inline Timer_t deltam( Timer_t t1, Timer_t t2 ) const { return Timer_t(deltas(t1,t2)*1e3); }
    inline Timer_t deltau( Timer_t t1, Timer_t t2 ) const { return Timer_t(deltas(t1,t2)*1e6); }
    inline Timer_t deltan( Timer_t t1, Timer_t t2 ) const { return Timer_t(deltas(t1,t2)*1e9); }
  
    double getSecsPerClick() { return _secsPerTic; }
  
  private :
    double                  _secsPerTic;
    bool                    _use_high_res_timer;
  };

}

#endif
