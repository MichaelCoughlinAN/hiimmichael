#include <windows.h>

#include "string.h"
#include "glmath.h"

#include <FreeImage.h> // http://freeimage.sourceforge.net/

#pragma comment(lib, "FreeImage.lib")

// ----------------------------------------------------------------------------------------------------------------------------

class CTexture
{
private:
	BYTE *Data;
	int Width, Height;

public:
	CTexture();
	~CTexture();

	bool CreateTexture2D(char *Texture2DFileName);
	vec3 GetColorNearest(float s, float t);
	vec3 GetColorBilinear(float s, float t);
	void Destroy();
};

// ----------------------------------------------------------------------------------------------------------------------------

class CQuad
{
public:
	float Reflection, Refraction, Eta, ODEta, D, D1, D2, D3, D4;
	vec3 a, b, c, d, Color, ab, ad, m, T, B, N, O, N1, N2, N3, N4;
	CTexture *Texture;
	// static UINT Intersections;

public:
	CQuad();
	CQuad(const vec3 &a, const vec3 &b, const vec3 &c, const vec3 &d, const vec3 &Color, CTexture *Texture = NULL, float Reflection = 0.0f, float Refraction = 0.0f, float Eta = 1.0f);

	bool Inside(vec3 &Point);
	bool Intersect(vec3 &Origin, const vec3 &Ray, float MaxDistance, float &Distance, vec3 &Point);
	bool Intersect(vec3 &Origin, const vec3 &Ray, float MaxDistance, float &Distance);
	bool Intersect(vec3 &Origin, const vec3 &Ray, float MaxDistance);
};

// ----------------------------------------------------------------------------------------------------------------------------

class CSphere
{
public:
	float Radius, Radius2, ODRadius, Reflection, Refraction, Eta, ODEta;
	vec3 Position, Color;
	CTexture *Texture;
	// static UINT Intersections;

public:
	CSphere();
	CSphere(const vec3 &Position, float Radius, const vec3 &Color, CTexture *Texture = NULL, float Reflection = 0.0f, float Refraction = 0.0f, float Eta = 1.0f);

	bool Intersect(vec3 &Origin, const vec3 &Ray, float MaxDistance, float &Distance, vec3 &Point);
	bool Intersect(vec3 &Origin, const vec3 &Ray, float MaxDistance, float &Distance);
	bool Intersect(vec3 &Origin, const vec3 &Ray, float MaxDistance);
};

// ----------------------------------------------------------------------------------------------------------------------------

class CLight
{
public:
	float Ambient, Diffuse, ConstantAttenuation, LinearAttenuation, QuadraticAttenuation;
	CSphere *Sphere;
	CQuad *Quad;

public:
	CLight();
	~CLight();
};

// ----------------------------------------------------------------------------------------------------------------------------

class CCamera
{
public:
	vec3 X, Y, Z, Reference, Position;
	mat4x4 Vin, Pin, Bin, VPin, RayMatrix;

public:
	CCamera();
	~CCamera();

	void CalculateRayMatrix();
	void LookAt(const vec3 &Reference, const vec3 &Position, bool RotateAroundReference = false);
	bool OnKeyDown(UINT nChar);
	void OnMouseMove(int dx, int dy);
	void OnMouseWheel(short zDelta);
};

// ----------------------------------------------------------------------------------------------------------------------------

class RTData
{
public:
	float Distance, TestDistance;
	vec3 Color, Point, TestPoint;
	CQuad *Quad;
	CSphere *Sphere;
	CLight *Light;

public:
	RTData();
};

// ----------------------------------------------------------------------------------------------------------------------------

class CRayTracer
{
private:
	BYTE *ColorBuffer;
	BITMAPINFO ColorBufferInfo;
	vec3 *HDRColorBuffer;
	int Width, LineWidth, Height, Samples, GISamples, WidthMSamples, HeightMSamples, WidthMHeightMSamples2;
	float ODSamples2, ODGISamples, AmbientOcclusionIntensity, ODGISamplesMAmbientOcclusionIntensity;

protected:
	CQuad *Quads, *LastQuad;
	CSphere *Spheres, *LastSphere;
	CLight *Lights, *LastLight;
	int QuadsCount, SpheresCount, LightsCount;

public:
	bool Textures, SoftShadows, AmbientOcclusion;

public:
	CRayTracer();
	~CRayTracer();

	bool Init();
	void RayTrace(int Line);
	void Resize(int Width, int Height);
	void Destroy();

	void ClearColorBuffer();
	int GetSamples();
	void MapHDRColors();
	bool SetSamples(int Samples);
	void SwapBuffers(HDC hDC);

protected:
	virtual bool InitScene() = 0;
	virtual void DestroyTextures() = 0;

private:
	bool Shadow(void *Object, vec3 &Point, vec3 &LightDirection, float LightDistance);
	vec3 LightIntensity(void *Object, vec3 &Point, vec3 &Normal, vec3 &LightPosition, CLight *Light, float AO);
	float AmbientOcclusionFactor(void *Object, vec3 &Point, vec3 &Normal);
	void IlluminatePoint(void *Object, vec3 &Point, vec3 &Normal, vec3 &Color);
	vec3 RayTrace(vec3 &Origin, const vec3 &Ray, UINT Depth = 0, void *Object = NULL);
};

// ----------------------------------------------------------------------------------------------------------------------------

class CMyRayTracer : public CRayTracer
{
private:
	CTexture Floor, Cube, Earth;

protected:
	bool InitScene();
	void DestroyTextures();
};

// ----------------------------------------------------------------------------------------------------------------------------

class CWnd
{
protected:
	char *WindowName;
	HWND hWnd;
	HDC hDC;
	int Width, Height, Line;
	POINT LastCurPos;

public:
	CWnd();
	~CWnd();

	bool Create(HINSTANCE hInstance, char *WindowName, int Width, int Height);
	void RePaint();
	void Show(bool Maximized = false);
	void MsgLoop();
	void Destroy();

	void OnKeyDown(UINT Key);
	void OnMouseMove(int cx, int cy);
	void OnMouseWheel(short zDelta);
	void OnPaint();
	void OnRButtonDown(int cx, int cy);
	void OnSize(int Width, int Height);
};

// ----------------------------------------------------------------------------------------------------------------------------

LRESULT CALLBACK WndProc(HWND hWnd, UINT uiMsg, WPARAM wParam, LPARAM lParam);
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR sCmdLine, int iShow);
