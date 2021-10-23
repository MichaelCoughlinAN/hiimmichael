// This codes tests the Vector3D class. It uses the Boost UnitTest
// framework. For more information about what is possible with Boost's
// Unit Test, you are referred to the following:
//
// http://www.boost.org/doc/libs/1_53_0/libs/test/doc/html/index.html
// http://www.ibm.com/developerworks/aix/library/au-ctools1_boost/
// http://www.alittlemadness.com/2009/03/31/c-unit-testing-with-boosttest/

#define BOOST_TEST_MODULE Vector3DTest
#include <boost/test/included/unit_test.hpp>

#include "Vector3D.h"

// Name of the test as it is reported when running the tests.
BOOST_AUTO_TEST_SUITE(Vector3D)

BOOST_AUTO_TEST_CASE(Add)
{
  sivelab::Vector3D a(1.0f,0.0f,0.0f), b(0.0f,1.0f,0.0f), c(0.0f, 0.0f, 1.0f);
  sivelab::Vector3D ans(1.0f, 1.0f, 1.0f), res;

  res = a + b + c;
  BOOST_CHECK_CLOSE_FRACTION ( res[0], ans[0], 0.00001 );   
  BOOST_CHECK_CLOSE_FRACTION ( res[1], ans[1], 0.00001 );   
  BOOST_CHECK_CLOSE_FRACTION ( res[2], ans[2], 0.00001 );   
}

BOOST_AUTO_TEST_CASE (dotProduct)
{
  // Check the orthogonality of the Cartesian coordinate system using
  // the dot product. The resulting dot products between these vectors
  // must be 0, but recall that we cannot compare equality with
  // floating point representations and have it be a robust
  // calculation. So, we use Boost's CHECK_CLOSE_FRACTION function to
  // compare closeness within 0.00001.
  sivelab::Vector3D X(1.0f, 0.0f, 0.0f), Y(0.0f, 1.0f, 0.0f), Z(0.0f, 0.0f, 1.0f);

  BOOST_CHECK_CLOSE_FRACTION ( X.dot(Y), 0.0, 0.00001 ); 
  BOOST_CHECK_CLOSE_FRACTION ( X.dot(Z), 0.0, 0.00001 ); 
  BOOST_CHECK_CLOSE_FRACTION ( Y.dot(Z), 0.0, 0.00001 ); 
}

BOOST_AUTO_TEST_CASE (crossProduct)
{
  // Check the orthogonality of the Cartesian coordinate system using
  // the dot product. The resulting dot products between these vectors
  // must be 0, but recall that we cannot compare equality with
  // floating point representations and have it be a robust
  // calculation. So, we use Boost's CHECK_CLOSE_FRACTION function to
  // compare closeness within 0.00001.
  sivelab::Vector3D X(1.0f, 0.0f, 0.0f), Y(0.0f, 1.0f, 0.0f), 
    Z(0.0f, 0.0f, 1.0f), negZ(0.0f, 0.0f, -1.0f);
  sivelab::Vector3D res;

  res = X.cross(Y);
  BOOST_CHECK_CLOSE_FRACTION ( res[0], Z[0], 0.00001 ); 
  BOOST_CHECK_CLOSE_FRACTION ( res[1], Z[1], 0.00001 ); 
  BOOST_CHECK_CLOSE_FRACTION ( res[2], Z[2], 0.00001 ); 

  res = Y.cross(X);
  BOOST_CHECK_CLOSE_FRACTION ( res[0], negZ[0], 0.00001 ); 
  BOOST_CHECK_CLOSE_FRACTION ( res[1], negZ[1], 0.00001 ); 
  BOOST_CHECK_CLOSE_FRACTION ( res[2], negZ[2], 0.00001 ); 

}


BOOST_AUTO_TEST_CASE (length)
{
  // Check the orthogonality of the Cartesian coordinate system using
  // the dot product. The resulting dot products between these vectors
  // must be 0, but recall that we cannot compare equality with
  // floating point representations and have it be a robust
  // calculation. So, we use Boost's CHECK_CLOSE_FRACTION function to
  // compare closeness within 0.00001.
  sivelab::Vector3D X(1.0f, 0.0f, 0.0f), 
    Y(0.0f, 1.0f, 0.0f), 
    Z(0.0f, 0.0f, 1.0f), 
    XYZ(1.0f, 1.0f, 1.0f);

  // length of these should each be 1 (or sqrt(1))
  double sqrtOne = sqrt(1.0);
  
  BOOST_CHECK_CLOSE_FRACTION ( sqrtOne, X.length(), 0.00001 );   
  BOOST_CHECK_CLOSE_FRACTION ( sqrtOne, Y.length(), 0.00001 );   
  BOOST_CHECK_CLOSE_FRACTION ( sqrtOne, Z.length(), 0.00001 );   

  // A vector that points to 1, 1, 1 should have sqrt(1+1+1)
  double sqrtAllOnes = sqrt( 1.0*1.0 + 1.0*1.0 + 1.0*1.0 );
  BOOST_CHECK_CLOSE_FRACTION ( sqrtAllOnes, XYZ.length(), 0.00001 );   
}

BOOST_AUTO_TEST_SUITE_END ()
