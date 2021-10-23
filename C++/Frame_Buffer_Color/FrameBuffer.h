#ifndef FRAMEBUFFERH
#define FRAMEBUFFERH

#include "Vector2D.h"
#include "Vector3D.h"
#include "Color.h"

class Edge
{
	public:
		Color Color1, Color2;
		int X1, Y1, X2, Y2;

		Edge(const Color &color1, int x1, int y1, const Color &color2, int x2, int y2);
};

class Span
{
	public:
		Color Color1, Color2;
		int X1, X2;

		Span(const Color &color1, int x1, const Color &color2, int x2);
};

class FrameBuffer {
public:
	FrameBuffer(int height, int width);
        ~FrameBuffer(void);
	int width() const;
	int height() const;

        void rasterizeline_implicit(const Vector2D* p0, 
			            const Vector2D* p1, 
			            const Vector3D& c);

        void rasterizeline_parametric(const Vector2D* p0, 
				     const Vector2D* p1,
				     const Vector3D& c0,
 				     const Vector3D* c1);

	void set(int x, int y, short int red, short int green, 
		 short int blue);

	void erase();
	void resize(int height, int width);
	void writePPM(const string& filename) const;
	int* bufferData();

		void SetPixel(unsigned int x, unsigned int y, const Color &color = Color());
		void SetPixel(int x, int y, const Color &color = Color());
		void SetPixel(float x, float y, const Color &color = Color());
		

		void DrawTriangle(const Color &color1, float x1, float y1, const Color &color2, float x2, float y2, const Color &color3, float x3, float y3);

		void DrawLine(const Color &color1, float x1, float y1, const Color &color2, float x2, float y2);

private:
	int h;
	int w;
	short int* data;

protected:
		uint32_t *m_FrameBuffer;
		unsigned int m_Width, m_Height;

		void DrawSpan(const Span &span, int y);
		void DrawSpansBetweenEdges(const Edge &e1, const Edge &e2);

	
		
};

#endif
