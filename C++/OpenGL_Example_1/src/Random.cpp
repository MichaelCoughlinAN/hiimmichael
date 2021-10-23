#include <iostream>
#include <cstdlib>
#include <cmath>

#ifndef WIN32
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#endif

#include "Random.h"

using namespace sivelab;

void Random::init(long s)
{
  m_prng.seed(s);

  m_normal_value = false;

  m_lcg_m = std::numeric_limits<unsigned long>::max();
  m_lcg_a = 6364136223846793005UL;
  m_lcg_c = 1442695040888963407UL;

  // seed the first x value with the seed
  m_lcg_x = s;

  // combined tausworthe state
  m_taus_z1 = randVal() * std::numeric_limits<unsigned int>::max();
  m_taus_z2 = randVal() * std::numeric_limits<unsigned int>::max();
  m_taus_z3 = randVal() * std::numeric_limits<unsigned int>::max();
  m_taus_z4 = randVal() * std::numeric_limits<unsigned int>::max();
}

Random::Random()
{
#ifndef WIN32
  init( time(0) % getpid() );
#endif
}

Random::Random(long s)
{
  init(s);
}

double Random::uniform()
{
  return randVal();
}

// The normal function returns a random number from a Gaussian
// distribution with mean 0 and standard deviation of 1.  This is
// accomplished by using the Box-Muller algorithm for transformation
// between different distributions.
double Random::normal()
{
  double rsq, v1, v2;
  
  if (m_normal_value == false)
    {
      do 
	{
	  v1 = 2.0 * randVal() - 1.0;
	  v2 = 2.0 * randVal() - 1.0;
	  rsq = v1*v1 + v2*v2;
	} while (rsq >= 1.0);
      
      rsq = sqrt( (-2.0 * log(rsq) ) / rsq );
      
      m_remaining_value = v2 * rsq;
      m_normal_value = true;

      return v1*rsq;
    }
  else
    {
      m_normal_value = false;
      return m_remaining_value;
    }
}
 
double Random::lcg()
{
  m_lcg_x = (m_lcg_a * m_lcg_x + m_lcg_c) % m_lcg_m;
  return m_lcg_x / (long double)std::numeric_limits<unsigned long>::max();
}

