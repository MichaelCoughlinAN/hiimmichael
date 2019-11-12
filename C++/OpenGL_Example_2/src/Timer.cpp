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

#include <iostream>
#include <cstring>

#include "Timer.h"

using namespace sivelab;

#ifdef WIN32
#include <sys/types.h>
#include <fcntl.h>
#include <windows.h>
#include <winbase.h>

Timer::Timer( bool enable_high_res_timer )
  : _use_high_res_timer(enable_high_res_timer)
{
	if (_use_high_res_timer)
	{
		Timer_t ctr;
		if (QueryPerformanceCounter((LARGE_INTEGER *)&ctr) != 0)
		{
			std::cout << "High Performance Timer available." << std::endl;
		}
		else
		{
			// High performance timer is not available.
			_secsPerTic = 1.0;
			std::cerr << "**************************************" << std::endl;
			std::cerr << "Error: Timer::Timer() unable to use QueryPerformanceFrequency, " << std::endl;
			std::cerr << "timing code will be wrong, Windows error code: "<< GetLastError() << std::endl;
			std::cerr << "**************************************" << std::endl;
		}
	}
	else 
	{
		// Use the lower resolution timers
		_secsPerTic = 1.0;
	}
}

Timer_t Timer::tic() const
{
	if (_use_high_res_timer)
	{
		Timer_t qpc;
		if (QueryPerformanceCounter((LARGE_INTEGER *)&qpc) != 0)
		{
			return qpc;
		}
		else
		{
			std::cerr << "Error: Timer::Timer() unable to use QueryPerformanceCounter, " << std::endl;
			std::cerr << "timing code will be wrong, Windows error code: "<< GetLastError() << std::endl;
			return 0;
		}
	}
	else
	{
		// use the low resolution timer
		return timeGetTime();
	}
}

double Timer::deltas( Timer_t t1, Timer_t t2 ) const
{ 
	if (_use_high_res_timer)
	{
		Timer_t frequency;
		QueryPerformanceFrequency((LARGE_INTEGER *)&frequency);
		return (t2 - t1) * 1.0 / frequency;
	}
	else
	{
		// this is in milliseconds, so convert to seconds
		return (double)(t2 - t1) / 1000.0;
	}
}

#else

// UNIX and OS X based timer functionality
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/time.h>

// This is the hardware assembly code for the high resolution, low
// latency timer on x86 machines.  This timer will only work on x86
// hardware running Linux and must be enabled as a default argument to
// the constructor.
#define CLK(x)      __asm__ volatile (".byte 0x0f, 0x31" : "=A" (x))

Timer::Timer( bool enable_high_res_timer )
  : _use_high_res_timer(enable_high_res_timer)
{
  //
  // The high res timer will NOT work on Macs, so don't even allow it..
  //
#ifndef __APPLE__
  if (_use_high_res_timer)
    {
      char buff[128];
      FILE *fp = fopen( "/proc/cpuinfo", "r" );
      
      double cpu_mhz=0.0f;
      while( fgets( buff, sizeof( buff ), fp ) > 0 )
	{
	  if( !strncmp( buff, "cpu MHz", strlen( "cpu MHz" )))
	    {
	      char *ptr = buff;
	      
	      while( ptr && *ptr != ':' ) ptr++;
	      if( ptr ) 
		{
		  ptr++;
		  sscanf( ptr, "%lf", &cpu_mhz );
		}
	      break;
	    }
	}
      fclose( fp );
      
      if (cpu_mhz==0.0f)
	{
	  // error - no cpu_mhz found, guess the secs per tic...
	  Timer_t start_time = tic();
	  sleep (1);
	  Timer_t end_time = tic();
	  _secsPerTic = 1.0/(double)(end_time-start_time);
	}
      else
	{
	  _secsPerTic = 1e-6/cpu_mhz;
	}
    }
  else 
    {
#endif
      // use standard, gettimeofday timing mechanism
      _secsPerTic = (1.0 / (double) 1000000);
#ifndef __APPLE__
    }
#endif
}

Timer_t Timer::tic() const
{
#ifndef __APPLE__
  if (_use_high_res_timer)
    {
      Timer_t x;CLK(x);return x;
    }
  else
    {
#endif
      struct timeval tv;
      gettimeofday(&tv, NULL);
      return ((Timer_t)tv.tv_sec)*1000000+(Timer_t)tv.tv_usec;
#ifndef __APPLE__
    }
#endif
}

double Timer::deltas( Timer_t t1, Timer_t t2 ) const
{ 
	return (double)((t2 - t1) * _secsPerTic);
}

#endif // else clause for ifdef WIN32
