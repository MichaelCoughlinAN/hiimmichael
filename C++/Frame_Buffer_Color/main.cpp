// Michael Coughlin
// CS5721, Spring 2017

#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cmath>

using namespace std;

#include "Vector2D.h"
#include "Vector3D.h"
#include "FrameBuffer.h"

int main() {

  // variables and objects
 int w=800, h=600;
 Color color1(1.0f, 0.0f, 0.0f);
 Color color2(0.0f, 1.0f, 0.0f);
 Color color3(0.0f, 0.0f, 1.0f);
 float r = 0.0f;
 float PI = 3.14;
 const float size = 110.0f;

	float x1 = (w / 2) + cosf(r - PI / 6.0) * size;
	float y1 = (h / 2) + sinf(r - PI / 6.0) * size;
	float x2 = (w / 2) + cosf(r + PI / 2.0) * size;
	float y2 = (h / 2) + sinf(r + PI / 2.0) * size;
	float x3 = (w / 2) + cosf(r + PI + PI / 6.0) * size;
	float y3 = (h / 2) + sinf(r + PI + PI / 6.0) * size;

   
// Create first image
   FrameBuffer first(h, w);
  first.DrawTriangle(color1, 0, 0, color1, w-1, 0, color1, w-1, h-1);
first.DrawTriangle(color1, w-1, h-1, color2, 0, h-1, color3, 0, 0);
    
first.writePPM("first.ppm");

// Create second image
h= 1000;
w = 1000;
   FrameBuffer second(h, w);

 Color color4(1.0f, 1.0f, 0.0f);
 Color color5(0.0f, 1.0f, 1.0f);
 Color color6(1.0f, 0.0f, 1.0f);
 Color color7(1.0f, 1.0f, 1.0f);
Color color8(0.0f,0.0f,0.0f);

  second.DrawTriangle(color4, 200, 0, color5, 200, 200, color6, 0, 200);
  second.DrawTriangle(color3, 200, 0, color3, w-1, 200, color3, 200, 200);
  second.DrawTriangle(color2, 200, h-1, color8, 200, 200, color3, w-1, 200);
  second.DrawTriangle(color2, 200, 200, color4, 200, h-1, color7, 0, 200);
  second.writePPM("second.ppm");

 FrameBuffer third(h, w);
// here is a square
 third.DrawTriangle(color1, 3, 0, color1, w-500, 0, color1, w-500, h-503);
 third.DrawTriangle(color1, w-500, h-500, color1, 0, h-500, color1, 0, 0);
/////////////////////////////////////////////

 third.DrawTriangle(color1, 500, 700, color2, 596, 800, color1,   700, 700);

third.DrawTriangle(color1, 800 // right point 
, 806, color2, 596, 806, color1,   700, 708);



 third.DrawTriangle(color1, 900, 700, color2, 800, 800, color1, 700, 700);

third.DrawTriangle(color1, 500, 696, color2, 596, 600, color1, 700, 696);

 third.DrawTriangle(color1, 900, 696, color2, 800, 600, color1, 700, 696);



third.DrawTriangle(color1, 604,600, color2, 700, 690 , color1, 796, 600) ;


third.DrawTriangle(color3, 0,700, color3, 400, 796 , color3, 0, 796) ;
third.DrawTriangle(color3, 0,1000, color3, 400, 800 , color3, 0, 800) ;

 third.writePPM("third.ppm");


// draws a 3d shape.

FrameBuffer f(h, w);
// f.DrawTriangle(color1, 0, 0, color1, w-500, 0, color1, w-500, h-500);
 f.DrawTriangle(color1, 500 ,500, color1, 0, 500, color1, 500, 0);
 f.DrawTriangle(color2, 0, 500, color1, 500, 500, color1, 700, 575);
 f.DrawTriangle(color2, 500,  0, color1, 500, 500, color1, 700, 575);
f.writePPM("four.ppm");
	return 0;
}
