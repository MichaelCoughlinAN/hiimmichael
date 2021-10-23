#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

using namespace std;

#include "FrameBuffer.h"

void FrameBuffer::rasterizeline_implicit(const Vector2D* p0, const Vector2D *p1, const Vector3D& c) {
 double x,y,dx,dy,dx1,dy1,px,py,xe,ye,i;
 double x1 = p0->x();
 double x2 = p1->x();
 double y1 = p0->y();
 double y2 = p1->y();
 
 dx=x2-x1;
 dy=y2-y1;
 dx1=fabs(dx);
 dy1=fabs(dy);
 px=2*dy1-dx1;
 py=2*dx1-dy1;
 if(dy1<=dx1)
 {
  if(dx>=0)
  {
   x=x1;
   y=y1;
   xe=x2;
  }
  else
  {
   x=x2;
   y=y2;
   xe=x1;
  }
     set(x,y,c.x(), c.y(), c.z());
  for(i=0;x<xe;i++)
  {
   x=x+1;
   if(px<0)
   {
    px=px+2*dy1;
   }
   else
   {
    if((dx<0 && dy<0) || (dx>0 && dy>0))
    {
     y=y+1;
    }
    else
    {
     y=y-1;
    }
    px=px+2*(dy1-dx1);
   }
   set(x,y,c.x(), c.y(), c.z());
  }
 }
 else
 {

  if(dy>=0)
  {
   x=x1;
   y=y1;
   ye=y2;
  }
  else
  {
   x=x2;
   y=y2;
   ye=y1;
  }
     set(x,y,c.x(), c.y(), c.z());
  for(i=0;y<ye;i++)
  {
   y=y+1;
   if(py<=0)
   {
    py=py+2*dx1;
   }
   else
   {
    if((dx<0 && dy<0) || (dx>0 && dy>0))
    {
     x=x+1;
    }
    else
    {
     x=x-1;
    }
    py=py+2*(dx1-dy1);
   }
     set(x,y,c.x(), c.y(), c.z());
  }
 }
}
  void FrameBuffer::rasterizeline_parametric( const Vector2D* p0, const Vector2D* p1, const Vector3D& c0, const Vector3D* c1) {
double x,y,dx,dy,dx1,dy1,px,py,xe,ye,i;
 double x1 = p0->x();
 double x2 = p1->x();
 double y1 = p0->y();
 double y2 = p1->y();
 
 dx=x2-x1;
 dy=y2-y1;
 dx1=fabs(dx);
 dy1=fabs(dy);
 px=2*dy1-dx1;
 py=2*dx1-dy1;
 if(dy1<=dx1)
 {
  if(dx>=0)
  {
   x=x1;
   y=y1;
   xe=x2;
  }
  else
  {
   x=x2;
   y=y2;
   xe=x1;
  }
     set(x,y,c1->x(), c1->y(), c1->z());
  for(i=0;x<xe;i++)
  {
   x=x+1;
   if(px<0)
   {
    px=px+2*dy1;
   }
   else
   {
    if((dx<0 && dy<0) || (dx>0 && dy>0))
    {
     y=y+1;
    }
    else
    {
     y=y-1;
    }
    px=px+2*(dy1-dx1);
   }
   set(x,y,c0.x(), c0.y(), c0.z());
  }
 }
 else
 {

  if(dy>=0)
  {
   x=x1;
   y=y1;
   ye=y2;
  }
  else
  {
   x=x2;
   y=y2;
   ye=y1;
  }
     set(x,y,c1->x(), c1->y(), c1->z());
  for(i=0;y<ye;i++)
  {
   y=y+1;
   if(py<=0)
   {
    py=py+2*dx1;
   }
   else
   {
    if((dx<0 && dy<0) || (dx>0 && dy>0))
    {
     x=x+1;
    }
    else
    {
     x=x-1;
    }
    py=py+2*(dx1-dy1);
   }
     set(x,y,c0.x(), c0.y(), c0.z());
  }
 }
}


FrameBuffer::FrameBuffer(int height, int width) : h(height), w(width) {
	data = new short[height * width * 3];

	// initialize the FrameBuffer background
	for (int x = 0; x < width; x++)
	{
		for (int y = 0; y < height; y++) {
			data[((x*3) + (y*3) * width + 0)] = 255;
			data[((x*3) + (y*3) * width + 1)] = 255;
			data[((x*3) + (y*3) * width + 2)] = 255;
		}
	}
}

FrameBuffer::~FrameBuffer(void)  {
	delete[] data;
}

int FrameBuffer::width() const {
	return w;
}

int FrameBuffer::height() const {
	return h;
}

void FrameBuffer::set(int x, int y, short int red, short int green, short int blue) {
	int r, g, b;

	r = ( red >= 0 ) ? red : 0;
	r = ( r <= 255 ) ? r : 255;

	g = ( green >= 0 ) ? green : 0;
	g = ( g <= 255 ) ? g : 255;

	b = ( blue >= 0 ) ? blue : 0;
	b = ( b <= 255 ) ? b : 255;

	if ( ((x*3) + (y*3) * w + 2) <= (h * w * 3) )
	{
		data[ ((x*3) + (y*3) * w + 0) ] = r;
		data[ ((x*3) + (y*3) * w + 1) ] = g;
		data[ ((x*3) + (y*3) * w + 2) ] = b;
	}
}

void FrameBuffer::erase() {
	// reinitialize the FrameBuffer to a black background

	for (int x = 0; x < w; x++)
	{
		for (int y = 0; y < h; y++) {
			set(x, y, 0, 0, 0);
		}
	}
}

void FrameBuffer::resize(int height, int width) {
	delete[] data;

	h = height;
	w = width;

	data = new short[height * width * 3 ];
}

void FrameBuffer::writePPM(const string &filename) const {
	char *row, *col;

	ofstream output;
	output.open(filename.c_str(), ofstream::out | ofstream::trunc);

	output << "P3\n" << w << " " << h << " 255";

	// write data to the ppm output file one line at a time

	for (int y = h-1; y >= 0; y--)
	{
		row = new char[ w * 3 * 4 + 2 ]; // width pixels * 3 colors * 4 characters max (ie '255 ') + new line
		col = row;
		col += sprintf(col, "\n");

		for (int x = 0; x < w; x++) {
			for (int c = 0; c < 3; c++) {
				col += sprintf(col, "%d ", data[ ((x*3) + (y*3) * w + c) ]);
			}
		}

		output << row;
		delete[] row;
	}

	output.close();
}

int* FrameBuffer::bufferData()
{
	int* tmp = new int[ h * w * 3 ];

	for (int i = 0; i < (h * w * 3); i++) {
		tmp[i] = (int) data[i];
	}

	return tmp;
}
