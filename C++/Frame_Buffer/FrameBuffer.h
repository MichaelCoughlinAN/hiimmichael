#ifndef FRAMEBUFFERH
#define FRAMEBUFFERH

#include "Vector2D.h"
#include "Vector3D.h"

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

private:
	int h;
	int w;
	short int* data;
};

#endif
