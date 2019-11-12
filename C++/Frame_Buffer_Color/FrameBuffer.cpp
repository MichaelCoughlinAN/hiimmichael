#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>


#include <cstdio>
#include <cstring>
#include <cmath>

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



Edge::Edge(const Color &color1, int x1, int y1,
           const Color &color2, int x2, int y2) {
	if(y1 < y2) {
		Color1 = color1;
		X1 = x1;
		Y1 = y1;
		Color2 = color2;
		X2 = x2;
		Y2 = y2;
	} else {
		Color1 = color2;
		X1 = x2;
		Y1 = y2;
		Color2 = color1;
		X2 = x1;
		Y2 = y1;
	}
}

Span::Span(const Color &color1, int x1, const Color &color2, int x2) {
	if(x1 < x2) {
		Color1 = color1;
		X1 = x1;
		Color2 = color2;
		X2 = x2;
	} else {
		Color1 = color2;
		X1 = x2;
		Color2 = color1;
		X2 = x1;
	}
}



void FrameBuffer::SetPixel(unsigned int x, unsigned int y, const Color &color) {
	
	set(x, y, color.R, color.G, color.B);
}

void FrameBuffer::SetPixel(int x, int y, const Color &color) {
	set(x, y, color.R, color.G, color.B);
}

void FrameBuffer::SetPixel(float x, float y, const Color &color) {

	set(x, y, color.R, color.G, color.B);
}


void FrameBuffer::DrawSpan(const Span &span, int y) {
	int xdiff = span.X2 - span.X1;
	if(xdiff == 0)
		return;

	Color colordiff = span.Color2 - span.Color1;

	float factor = 0.0f;
	float factorStep = 1.0f / (float)xdiff;

	// draw each pixel in the span
	for(int x = span.X1; x < span.X2; x++) {
		SetPixel(x, y, span.Color1 + (colordiff * factor));
		factor += factorStep;
	}
}

void FrameBuffer::DrawSpansBetweenEdges(const Edge &e1, const Edge &e2)
{
	// calculate difference between the y coordinates
	// of the first edge and return if 0
	float e1ydiff = (float)(e1.Y2 - e1.Y1);
	if(e1ydiff == 0.0f)
		return;

	// calculate difference between the y coordinates
	// of the second edge and return if 0
	float e2ydiff = (float)(e2.Y2 - e2.Y1);
	if(e2ydiff == 0.0f)
		return;

	// calculate differences between the x coordinates
	// and colors of the points of the edges
	float e1xdiff = (float)(e1.X2 - e1.X1);
	float e2xdiff = (float)(e2.X2 - e2.X1);
	Color e1colordiff = (e1.Color2 - e1.Color1);
	Color e2colordiff = (e2.Color2 - e2.Color1);

	// calculate factors to use for interpolation
	// with the edges and the step values to increase
	// them by after drawing each span
	float factor1 = (float)(e2.Y1 - e1.Y1) / e1ydiff;
	float factorStep1 = 1.0f / e1ydiff;
	float factor2 = 0.0f;
	float factorStep2 = 1.0f / e2ydiff;

	// loop through the lines between the edges and draw spans
	for(int y = e2.Y1; y < e2.Y2; y++) {
		// create and draw span
		Span span(e1.Color1 + (e1colordiff * factor1),
		          e1.X1 + (int)(e1xdiff * factor1),
		          e2.Color1 + (e2colordiff * factor2),
		          e2.X1 + (int)(e2xdiff * factor2));
		DrawSpan(span, y);

		// increase factors
		factor1 += factorStep1;
		factor2 += factorStep2;
	}
}

void FrameBuffer::DrawTriangle(const Color &color1, float x1, float y1,
                         const Color &color2, float x2, float y2,
                         const Color &color3, float x3, float y3)
{
	// create edges for the triangle
	Edge edges[3] = {
		Edge(color1, (int)x1, (int)y1, color2, (int)x2, (int)y2),
		Edge(color2, (int)x2, (int)y2, color3, (int)x3, (int)y3),
		Edge(color3, (int)x3, (int)y3, color1, (int)x1, (int)y1)
	};

	int maxLength = 0;
	int longEdge = 0;

	// find edge with the greatest length in the y axis
	for(int i = 0; i < 3; i++) {
		int length = edges[i].Y2 - edges[i].Y1;
		if(length > maxLength) {
			maxLength = length;
			longEdge = i;
		}
	}

	int shortEdge1 = (longEdge + 1) % 3;
	int shortEdge2 = (longEdge + 2) % 3;

	// draw spans between edges; the long edge can be drawn
	// with the shorter edges to draw the full triangle
	DrawSpansBetweenEdges(edges[longEdge], edges[shortEdge1]);
	DrawSpansBetweenEdges(edges[longEdge], edges[shortEdge2]);
}

void FrameBuffer::DrawLine(const Color &color1, float x1, float y1,
                      const Color &color2, float x2, float y2) {
	float xdiff = (x2 - x1);
	float ydiff = (y2 - y1);

	if(xdiff == 0.0f && ydiff == 0.0f) {
		SetPixel(x1, y1, color1);
		return;
	}

	if(fabs(xdiff) > fabs(ydiff)) {
		float xmin, xmax;

		// set xmin to the lower x value given
		// and xmax to the higher value
		if(x1 < x2) {
			xmin = x1;
			xmax = x2;
		} else {
			xmin = x2;
			xmax = x1;
		}

		// draw line in terms of y slope
		float slope = ydiff / xdiff;
		for(float x = xmin; x <= xmax; x += 1.0f) {
			float y = y1 + ((x - x1) * slope);
			Color color = color1 + ((color2 - color1) * ((x - x1) / xdiff));
			SetPixel(x, y, color);
		}
	} else {
		float ymin, ymax;

		// set ymin to the lower y value given
		// and ymax to the higher value
		if(y1 < y2) {
			ymin = y1;
			ymax = y2;
		} else {
			ymin = y2;
			ymax = y1;
		}

		// draw line in terms of x slope
		float slope = xdiff / ydiff;
		for(float y = ymin; y <= ymax; y += 1.0f) {
			float x = x1 + ((y - y1) * slope);
			Color color = color1 + ((color2 - color1) * ((y - y1) / ydiff));
			SetPixel(x, y, color);
		}
	}
}
