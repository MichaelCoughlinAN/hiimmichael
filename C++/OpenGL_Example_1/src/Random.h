/*
 *  Random.h
 *
 *  Created by Pete Willemsen on 10/6/09.
 *  Copyright 2009 Department of Computer Science, University of Minnesota-Duluth. All rights reserved.
 *
 * This file is part of libSIVELab library (libsivelab).
 *
 * libSIVELab is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * libSIVELab is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with libSIVELab.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef __SIVELAB_RANDOM_H__
#define __SIVELAB_RANDOM_H__ 1

#include <limits>

#ifdef WIN32
#include <windows.h>
#pragma comment(lib, "advapi32.lib")

// Windows includes a macro called max that interfers with the numeric limits max functions.  This removes it.
#undef max
#endif

#include <boost/random/mersenne_twister.hpp>
#include <boost/random/uniform_01.hpp>

namespace sivelab {

  class Random 
  {
  public:
    Random();
    Random(long seedval);

    // Returns a random number pulled from a uniform distribution.  The
    // value will be between 0 and 1.
    double uniform();

    // Returns a random number pulled from a normal distribution with
    // mean 0 and standard deviation of 1.
    double normal();

    double lcg();

    double taus()
    {
      double tVal = 2.3283064365387e-10                      // Periods
	* (tausStep(m_taus_z1, 13, 19, 12, 4294967294UL) ^   // p1 = 2^31-1
	   tausStep(m_taus_z2, 2, 25, 4, 4294967288UL) ^     // p2 = 2^30-1
	   tausStep(m_taus_z3, 3, 11, 17, 4294967280UL) ^    // p3 = 2^28-1
	   lcgStep(m_taus_z4, 1664525UL, 1013904223UL)         // p4 = 2^32
	   );
      double retVal = static_cast<double>((tVal / static_cast<double>(std::numeric_limits<unsigned int>::max())));
      return retVal;
    }
    
  private:
    boost::mt19937 m_prng;

    void init(long s);
	
    double randVal()
    {
      boost::uniform_01<> dist;
      return dist(m_prng);
    }

    bool m_normal_value;
    double m_remaining_value;

    unsigned long m_lcg_m, m_lcg_c, m_lcg_a, m_lcg_x; 
    unsigned long m_taus_z1, m_taus_z2, m_taus_z3, m_taus_z4;

    // Based on GPU Gems 3, Random Number Generators, page 813: S1, S2,
    // S3, and M are all constants, and z is part of the private
    // per-thread generator state.
    unsigned long tausStep(unsigned long &z, int S1, int S2, int S3, unsigned long M)
    {
      unsigned int b = (((z << S1) ^ z) >> S2);
      return z = (((z & M) << S3) ^ b);
    }

    unsigned long lcgStep(unsigned long &z, unsigned long A, unsigned long C)
    {
      return z = (A*z+C);
    }
  };
  
}

#endif // __SIVELAB_RANDOM_H__

