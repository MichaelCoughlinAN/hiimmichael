// Michael Coughlin
// CS5721, Spring 2017

#include <iostream>
#include <cstdlib>

using namespace std;

#include "Vector2D.h"
#include "Vector3D.h"
#include "FrameBuffer.h"

int main() {

  // variables and objects
   int w=725, h=408;
   Vector3D *random;
   Vector3D red(255,0,0);
Vector3D c(0,0,0);
   Vector3D blue(0,0,255);
   Vector3D green(0,255,0);
   Vector2D *p1;
   Vector2D *p2;

// Create first image
   FrameBuffer first(h, w);

// Uses dynamic memory to create circle design
double dRadius = 200;
for (int i=0;i<720;++i) {
   double dAng = 20 * asin (-1) * i / 360;
   double dx = dRadius * sin (dAng) + w/2;
   double dy = dRadius * cos (dAng) + h/2;
   // now you have coords of one point.
  p1 = new Vector2D(dx,dy);
  p2 = new Vector2D(w/2, h/2);
  first.rasterizeline_implicit(p1,p2,blue);
}
      
first.writePPM("first.ppm");

// Create Second Image
        w=640;
        h=480;
	FrameBuffer second(h, w);

    
for (int i=0;i<720;++i) {
   double dAng = 100 * asin (-1) * i / 360;
   double dx = dRadius * sin (dAng) + w/2;
   double dy = dRadius * cos (dAng) + h/2;
  
  p1 = new Vector2D(dx,dy);
  p2 = new Vector2D(w/2, h/2);
random = new Vector3D(rand() % 256, rand() % 256, rand() % 256);  

second.rasterizeline_parametric(p1, p2, green, random);
}

second.writePPM("second.ppm");

// Create Third Image
	w=725; 
	h=408;
	FrameBuffer third(h, w);

	        p1 = new Vector2D(362.5,408);
       		p2 = new Vector2D(0,0);
		third.rasterizeline_implicit(p1,p2,c);

                p1 = new Vector2D(725,0);
                p2 = new Vector2D(362.5, 408);
		third.rasterizeline_implicit(p1,p2,c);

	        p1 = new Vector2D(0,0);
	        p2 = new Vector2D(725,0);
                third.rasterizeline_implicit(p1,p2,c);

                p1 = new Vector2D(181.25, 204);
	        p2 = new Vector2D(543.75, 204);
                third.rasterizeline_implicit(p1,p2,c);

                p1 = new Vector2D(181.25, 204);
	        p2 = new Vector2D(362.5, 0);
                third.rasterizeline_implicit(p1,p2,c);

	        p1 = new Vector2D(543.75, 204);
                p2 = new Vector2D(362.5,0);
                third.rasterizeline_implicit(p1,p2,c);
   
                p1 = new Vector2D(181.25/2, 204/2);
	        p2 = new Vector2D(543.75/2, 204/2);
                third.rasterizeline_implicit(p1,p2,green);

		p1 = new Vector2D(181.25/2, 204/2);
	        p2 = new Vector2D(181.25, 0);
                third.rasterizeline_implicit(p1,p2,green);

		p1 = new Vector2D(543.75/2, 204/2);
	        p2 = new Vector2D(181.25, 0);
                third.rasterizeline_implicit(p1,p2,green);

                p1 = new Vector2D(362.5+90.625, 304);
	        p2 = new Vector2D(543.75/2, 304);
                third.rasterizeline_implicit(p1,p2,blue);

		p1 = new Vector2D(362.5+90.625, 304);
	        p2 = new Vector2D(362, 204);
                third.rasterizeline_implicit(p1,p2,blue);

		p1 = new Vector2D(543.75/2, 304);
	        p2 = new Vector2D(362, 204);
                third.rasterizeline_implicit(p1,p2,blue);

                p1 = new Vector2D(362.5+90.625, 204/2);
	        p2 = new Vector2D(634.375, 204/2);
                third.rasterizeline_implicit(p1,p2,red);
             
		p1 = new Vector2D(362.5+90.625, 204/2);
	        p2 = new Vector2D(543.75, 0);
                third.rasterizeline_implicit(p1,p2,red);

		p1 = new Vector2D(634.375, 204/2);
	        p2 = new Vector2D(543.75, 0);
                third.rasterizeline_implicit(p1,p2,red);
            





    
	third.writePPM("third.ppm");      

	return 0;
}
