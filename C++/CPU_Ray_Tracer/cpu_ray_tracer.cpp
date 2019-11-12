#include "cpu_ray_tracer.h"

// ----------------------------------------------------------------------------------------------------------------------------

CString ModuleDirectory, ErrorLog;

// ----------------------------------------------------------------------------------------------------------------------------

CTexture::CTexture()
{
	Data = NULL;
	Width = Height = 0;
}

CTexture::~CTexture()
{
}

bool CTexture::CreateTexture2D(char *Texture2DFileName)
{
	CString FileName = ModuleDirectory + Texture2DFileName;
	CString ErrorText = "Error loading file " + FileName + "! -> ";

	FREE_IMAGE_FORMAT fif = FreeImage_GetFileType(FileName);

	if(fif == FIF_UNKNOWN)
	{
		fif = FreeImage_GetFIFFromFilename(FileName);
	}

	if(fif == FIF_UNKNOWN)
	{
		ErrorLog.Append(ErrorText + "fif is FIF_UNKNOWN" + "\r\n");
		return false;
	}

	FIBITMAP *dib = NULL;

	if(FreeImage_FIFSupportsReading(fif))
	{
		dib = FreeImage_Load(fif, FileName);
	}

	if(dib == NULL)
	{
		ErrorLog.Append(ErrorText + "dib is NULL" + "\r\n");
		return false;
	}

	int Width = FreeImage_GetWidth(dib);
	int Height = FreeImage_GetHeight(dib);
	int Pitch = FreeImage_GetPitch(dib);
	int BPP = FreeImage_GetBPP(dib);

	if(Width == 0 || Height == 0)
	{
		ErrorLog.Append(ErrorText + "Width or Height is 0" + "\r\n");
		return false;
	}

	BYTE *Bits = FreeImage_GetBits(dib);

	if(Bits == NULL)
	{
		ErrorLog.Append(ErrorText + "Bits is NULL" + "\r\n");
		return false;
	}

	if(BPP != 24 && BPP != 32)
	{
		FreeImage_Unload(dib);
		ErrorLog.Append(ErrorText + "BPP is not 24 nor 32" + "\r\n");
		return false;
	}

	Destroy();

	Data = new BYTE[Width * Height * 3];

	this->Width = Width;
	this->Height = Height;

	int bpp = BPP / 8;

	BYTE *data = Data, *line = Bits;

	for(int y = 0; y < Height; y++)
	{
		BYTE *pixel = line;

		for(int x = 0; x < Width; x++)
		{
			data[0] = pixel[2];
			data[1] = pixel[1];
			data[2] = pixel[0];

			pixel += bpp;
			data += 3;
		}

		line += Pitch;
	}

	FreeImage_Unload(dib);

	return true;
}

float OD255 = 1.0f / 255;

vec3 CTexture::GetColorNearest(float s, float t)
{
	vec3 Color = vec3(1.0f);

	if(Data != NULL)
	{
		s -= (int)s;
		t -= (int)t;
		
		if(s < 0.0f) s += 1.0f;
		if(t < 0.0f) t += 1.0f;

		int x = (int)(s * Width), y = (int)(t * Height);

		BYTE *data = (Width * y + x) * 3 + Data;

		Color.r = OD255 * data[0];
		Color.g = OD255 * data[1];
		Color.b = OD255 * data[2];
	}

	return Color;
}

vec3 CTexture::GetColorBilinear(float s, float t)
{
	vec3 Color = vec3(1.0f);

	if(Data != NULL)
	{
		s -= (int)s;
		t -= (int)t;
		
		if(s < 0.0f) s += 1.0f;
		if(t < 0.0f) t += 1.0f;

		float dx = s * Width - 0.5f, dy = t * Height - 0.5f;

		if(dx < 0.0f) dx += Width;
		if(dy < 0.0f) dy += Height;

		int x0 = (int)dx, y0 = (int)dy, x1 = (x0 + 1) % Width, y1 = (y0 + 1) % Height;

		int Width3 = Width * 3;

		BYTE *y0w = y0 * Width3 + Data;
		BYTE *y1w = y1 * Width3 + Data;

		int x03 = x0 * 3, x13 = x1 * 3;

		BYTE *a = y0w + x03;
		BYTE *b = y0w + x13;
		BYTE *c = y1w + x13;
		BYTE *d = y1w + x03;

		float u1 = dx - x0, v1 = dy - y0, u0 = 1.0f - u1, v0 = 1.0f - v1;

		u0 *= OD255;
		u1 *= OD255;

		float u0v0 = u0 * v0, u1v0 = u1 * v0, u1v1 = u1 * v1, u0v1 = u0 * v1;

		Color.r = u0v0 * a[0] + u1v0 * b[0] + u1v1 * c[0] + u0v1 * d[0];
		Color.g = u0v0 * a[1] + u1v0 * b[1] + u1v1 * c[1] + u0v1 * d[1];
		Color.b = u0v0 * a[2] + u1v0 * b[2] + u1v1 * c[2] + u0v1 * d[2];
	}

	return Color;
}

void CTexture::Destroy()
{
	if(Data != NULL)
	{
		delete [] Data;
		Data = NULL;
		Width = Height = 0;
	}
}

// ----------------------------------------------------------------------------------------------------------------------------

// UINT CQuad::Intersections;

CQuad::CQuad()
{
}

CQuad::CQuad(const vec3 &a, const vec3 &b, const vec3 &c, const vec3 &d, const vec3 &Color, CTexture *Texture, float Reflection, float Refraction, float Eta) : a(a), b(b), c(c), d(d), N(N), D(D), Color(Color), Texture(Texture), Reflection(Reflection), Refraction(Refraction), Eta(Eta)
{
	ab = b - a;
	ad = d - a;
	m = (a + b + c + d) / 4.0f;

	T = normalize(b - a);
	N = normalize(cross(b - a, c - a));
	B = cross(N, T);
	O = vec3(dot(T, a), dot(B, a), dot(N, a));

	D = -dot(N, a);
	ODEta = 1.0f / Eta;

	N1 = normalize(cross(N, b - a));
	D1 = -dot(N1, a);

	N2 = normalize(cross(N, c - b));
	D2 = -dot(N2, b);

	N3 = normalize(cross(N, d - c));
	D3 = -dot(N3, c);

	N4 = normalize(cross(N, a - d));
	D4 = -dot(N4, d);
}

bool CQuad::Inside(vec3 &Point)
{
	if(dot(N1, Point) + D1 < 0.0f) return false;
	if(dot(N2, Point) + D2 < 0.0f) return false;
	if(dot(N3, Point) + D3 < 0.0f) return false;
	if(dot(N4, Point) + D4 < 0.0f) return false;

	return true;
}

bool CQuad::Intersect(vec3 &Origin, const vec3 &Ray, float MaxDistance, float &Distance, vec3 &Point)
{
	// Intersections++;

	float NdotR = -dot(N, Ray);

	if(NdotR > 0.0f) // || (Refraction > 0.0f && NdotR < 0.0f))
	{
		Distance = (dot(N, Origin) + D) / NdotR;

		if(Distance >= 0.0f && Distance < MaxDistance)
		{
			Point = Ray * Distance + Origin;

			return Inside(Point);
		}
	}

	return false;
}

bool CQuad::Intersect(vec3 &Origin, const vec3 &Ray, float MaxDistance, float &Distance)
{
	// Intersections++;

	float NdotR = -dot(N, Ray);

	if(NdotR > 0.0f) // || (Refraction > 0.0f && NdotR < 0.0f))
	{
		Distance = (dot(N, Origin) + D) / NdotR;

		if(Distance >= 0.0f && Distance < MaxDistance)
		{
			return Inside(Ray * Distance + Origin);
		}
	}

	return false;
}

bool CQuad::Intersect(vec3 &Origin, const vec3 &Ray, float MaxDistance)
{
	// Intersections++;

	float NdotR = -dot(N, Ray);

	if(NdotR > 0.0f) // || (Refraction > 0.0f && NdotR < 0.0f))
	{
		float Distance = (dot(N, Origin) + D) / NdotR;

		if(Distance >= 0.0f && Distance < MaxDistance)
		{
			return Inside(Ray * Distance + Origin);
		}
	}

	return false;
}

// ----------------------------------------------------------------------------------------------------------------------------

// UINT CSphere::Intersections;

CSphere::CSphere()
{
}

CSphere::CSphere(const vec3 &Position, float Radius, const vec3 &Color, CTexture *Texture, float Reflection, float Refraction, float Eta) : Position(Position), Radius(Radius), Color(Color), Texture(Texture), Reflection(Reflection), Refraction(Refraction), Eta(Eta)
{
	Radius2 = Radius * Radius;
	ODRadius = 1.0f / Radius;
	ODEta = 1.0f / Eta;
}

bool CSphere::Intersect(vec3 &Origin, const vec3 &Ray, float MaxDistance, float &Distance, vec3 &Point)
{
	// Intersections++;

	vec3 L = Position - Origin;

	float LdotR = dot(L, Ray);

	if(LdotR > 0.0f)
	{
		float D2 = length2(L) - LdotR * LdotR;

		if(D2 < Radius2)
		{
			Distance = LdotR - sqrt(Radius2 - D2);

			if(Distance >= 0.0f && Distance < MaxDistance)
			{
				Point = Ray * Distance + Origin;

				return true;
			}
		}
	}

	return false;
}

bool CSphere::Intersect(vec3 &Origin, const vec3 &Ray, float MaxDistance, float &Distance)
{
	// Intersections++;

	vec3 L = Position - Origin;

	float LdotR = dot(L, Ray);

	if(LdotR > 0.0f)
	{
		float D2 = length2(L) - LdotR * LdotR;

		if(D2 < Radius2)
		{
			Distance = LdotR - sqrt(Radius2 - D2);

			if(Distance >= 0.0f && Distance < MaxDistance)
			{
				return true;
			}
		}
	}

	return false;
}

bool CSphere::Intersect(vec3 &Origin, const vec3 &Ray, float MaxDistance)
{
	// Intersections++;

	vec3 L = Position - Origin;

	float LdotR = dot(L, Ray);

	if(LdotR > 0.0f)
	{
		float D2 = length2(L) - LdotR * LdotR;

		if(D2 < Radius2)
		{
			float Distance = LdotR - sqrt(Radius2 - D2);

			if(Distance >= 0.0f && Distance < MaxDistance)
			{
				return true;
			}
		}
	}

	return false;
}

// ----------------------------------------------------------------------------------------------------------------------------

CLight::CLight()
{
    Ambient = 1.0f;
    Diffuse = 1.0f;

    ConstantAttenuation = 1.0f;
    LinearAttenuation = 0.0f;
    QuadraticAttenuation = 0.0f;

	Sphere = NULL;
	Quad = NULL;
}

CLight::~CLight()
{
	if(Sphere)
	{
		delete Sphere;
	}
	else
	{
		delete Quad;
	}
}

// ----------------------------------------------------------------------------------------------------------------------------

CCamera::CCamera()
{
	X = vec3(1.0, 0.0, 0.0);
	Y = vec3(0.0, 1.0, 0.0);
	Z = vec3(0.0, 0.0, 1.0);

	Reference = vec3(0.0, 0.0, 0.0);
	Position = vec3(0.0, 0.0, 5.0);

	Bin = BiasMatrixInverse();
}

CCamera::~CCamera()
{
}

void CCamera::CalculateRayMatrix()
{
	Vin[0] = X.x; Vin[4] = Y.x; Vin[8] = Z.x;
	Vin[1] = X.y; Vin[5] = Y.y; Vin[9] = Z.y;
	Vin[2] = X.z; Vin[6] = Y.z; Vin[10] = Z.z;

	RayMatrix = Vin * Pin * Bin * VPin;
}

void CCamera::LookAt(const vec3 &Reference, const vec3 &Position, bool RotateAroundReference)
{
	this->Reference = Reference;
	this->Position = Position;

	Z = normalize(Position - Reference);
	X = normalize(cross(vec3(0.0f, 1.0f, 0.0f), Z));
	Y = cross(Z, X);

	if(!RotateAroundReference)
	{
		this->Reference = this->Position;
		this->Position += Z * 0.05f;
	}

	CalculateRayMatrix();
}

bool CCamera::OnKeyDown(UINT nChar)
{
	float Distance = 0.125f;

	if(GetKeyState(VK_CONTROL) & 0x80)
	{
		Distance *= 0.5f;
	}

	if(GetKeyState(VK_SHIFT) & 0x80)
	{
		Distance *= 2.0f;
	}

	vec3 Up(0.0f, 1.0f, 0.0f);
	vec3 Right = X;
	vec3 Forward = cross(Up, Right);

	Up *= Distance;
	Right *= Distance;
	Forward *= Distance;

	vec3 Movement;

	if(nChar == 'W')
	{
		Movement += Forward;
	}

	if(nChar == 'S')
	{
		Movement -= Forward;
	}

	if(nChar == 'A')
	{
		Movement -= Right;
	}

	if(nChar == 'D')
	{
		Movement += Right;
	}

	if(nChar == 'R')
	{
		Movement += Up;
	}

	if(nChar == 'F')
	{
		Movement -= Up;
	}

	Reference += Movement;
	Position += Movement;

	return Movement.x != 0.0f || Movement.y != 0.0f || Movement.z != 0.0f;
}

void CCamera::OnMouseMove(int dx, int dy)
{
	float sensitivity = 0.25f;

	float hangle = (float)dx * sensitivity;
	float vangle = (float)dy * sensitivity;

	Position -= Reference;

	Y = rotate(Y, vangle, X);
	Z = rotate(Z, vangle, X);

	if(Y.y < 0.0f)
	{
		Z = vec3(0.0f, Z.y > 0.0f ? 1.0f : -1.0f, 0.0f);
		Y = cross(Z, X);
	}

	X = rotate(X, hangle, vec3(0.0f, 1.0f, 0.0f));
	Y = rotate(Y, hangle, vec3(0.0f, 1.0f, 0.0f));
	Z = rotate(Z, hangle, vec3(0.0f, 1.0f, 0.0f));

	Position = Reference + Z * length(Position);

	CalculateRayMatrix();
}

void CCamera::OnMouseWheel(short zDelta)
{
	Position -= Reference;

	if(zDelta < 0 && length(Position) < 500.0f)
	{
		Position += Position * 0.1f;
	}

	if(zDelta > 0 && length(Position) > 0.05f)
	{
		Position -= Position * 0.1f;
	}

	Position += Reference;
}

CCamera Camera;

// ----------------------------------------------------------------------------------------------------------------------------

RTData::RTData()
{
	Distance = 1048576.0f;

	Quad = NULL;
	Light = NULL;
	Sphere = NULL;
}

// ----------------------------------------------------------------------------------------------------------------------------

CRayTracer::CRayTracer()
{
	ColorBuffer = NULL;
	HDRColorBuffer = NULL;

	Samples = 1;
	GISamples = 16;
	
	ODGISamples = 1.0f / (float)GISamples;
	AmbientOcclusionIntensity = 0.5f;
	ODGISamplesMAmbientOcclusionIntensity = ODGISamples * AmbientOcclusionIntensity;

	Quads = NULL;
	Spheres = NULL;
	Lights = NULL;

	LastQuad = NULL;
	LastSphere = NULL;
	LastLight = NULL;

	QuadsCount = 0;
	SpheresCount = 0;
	LightsCount = 0;

	Textures = true;
	SoftShadows = false;
	AmbientOcclusion = false;

	srand(GetTickCount());
}

CRayTracer::~CRayTracer()
{
}

bool CRayTracer::Init()
{
	if(InitScene() == false)
	{
		return false;
	}

	LastQuad = Quads + QuadsCount;
	LastSphere = Spheres + SpheresCount;
	LastLight = Lights + LightsCount;

	return true;
}

void CRayTracer::RayTrace(int Line)
{
	if(ColorBuffer == NULL || HDRColorBuffer == NULL) return;

	vec3 *hdrcolorbuffer;
	BYTE *colorbuffer = LineWidth * Line * 3 + ColorBuffer;

	if(Samples == 1)
	{
		hdrcolorbuffer = Width * Line + HDRColorBuffer;

		for(int x = 0; x < Width; x++)
		{
			vec3 Color = RayTrace(Camera.Position, normalize(Camera.RayMatrix * vec3((float)x, (float)Line, 0.0f)));

			hdrcolorbuffer->r = Color.r;
			hdrcolorbuffer->g = Color.g;
			hdrcolorbuffer->b = Color.b;

			hdrcolorbuffer++;

			colorbuffer[2] = Color.r <= 0.0f ? 0 : Color.r >= 1.0 ? 255 : (BYTE)(Color.r * 255);
			colorbuffer[1] = Color.g <= 0.0f ? 0 : Color.g >= 1.0 ? 255 : (BYTE)(Color.g * 255);
			colorbuffer[0] = Color.b <= 0.0f ? 0 : Color.b >= 1.0 ? 255 : (BYTE)(Color.b * 255);

			colorbuffer += 3;
		}
	}
	else
	{
		int Y = Line * Samples;

		for(int X = 0; X < WidthMSamples; X += Samples)
		{
			vec3 SamplesSum;

			for(int yy = 0; yy < Samples; yy++)
			{
				int Yyy = Y + yy;

				hdrcolorbuffer = WidthMSamples * Yyy + X + HDRColorBuffer;

				for(int xx = 0; xx < Samples; xx++)
				{
					vec3 Color = RayTrace(Camera.Position, normalize(Camera.RayMatrix * vec3((float)(X + xx), (float)Yyy, 0.0f)));

					hdrcolorbuffer->r = Color.r;
					hdrcolorbuffer->g = Color.g;
					hdrcolorbuffer->b = Color.b;

					hdrcolorbuffer++;

					SamplesSum.r += Color.r <= 0.0f ? 0.0f : Color.r >= 1.0 ? 1.0f : Color.r;
					SamplesSum.g += Color.g <= 0.0f ? 0.0f : Color.g >= 1.0 ? 1.0f : Color.g;
					SamplesSum.b += Color.b <= 0.0f ? 0.0f : Color.b >= 1.0 ? 1.0f : Color.b;
				}
			}

			SamplesSum.r *= ODSamples2;
			SamplesSum.g *= ODSamples2;
			SamplesSum.b *= ODSamples2;

			colorbuffer[2] = (BYTE)(SamplesSum.r * 255);
			colorbuffer[1] = (BYTE)(SamplesSum.g * 255);
			colorbuffer[0] = (BYTE)(SamplesSum.b * 255);

			colorbuffer += 3;
		}
	}
}

void CRayTracer::Resize(int Width, int Height)
{
	this->Width = Width;
	this->Height = Height;

	if(ColorBuffer != NULL)
	{
		delete [] ColorBuffer;
		ColorBuffer = NULL;
	}

	if(HDRColorBuffer != NULL)
	{
		delete [] HDRColorBuffer;
		HDRColorBuffer = NULL;
	}

	if(Width > 0 && Height > 0)
	{
		LineWidth = Width;

		int WidthMod4 = Width % 4;

		if(WidthMod4 > 0)
		{
			LineWidth += 4 - WidthMod4;
		}

		ColorBuffer = new BYTE[LineWidth * Height * 3];

		memset(&ColorBufferInfo, 0, sizeof(BITMAPINFOHEADER));
		ColorBufferInfo.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
		ColorBufferInfo.bmiHeader.biPlanes = 1;
		ColorBufferInfo.bmiHeader.biBitCount = 24;
		ColorBufferInfo.bmiHeader.biCompression = BI_RGB;
		ColorBufferInfo.bmiHeader.biWidth = LineWidth;
		ColorBufferInfo.bmiHeader.biHeight = Height;

		WidthMSamples = Width * Samples;
		HeightMSamples = Height * Samples;
		WidthMHeightMSamples2 = WidthMSamples * HeightMSamples;
		ODSamples2 = 1.0f / (float)(Samples * Samples);

		HDRColorBuffer = new vec3[WidthMHeightMSamples2];

		Camera.VPin[0] = 1.0f / (float)(WidthMSamples - 1);
		Camera.VPin[5] = 1.0f / (float)(HeightMSamples - 1);

		float tany = tan(45.0f / 360.0f * (float)M_PI), aspect = (float)Width / (float)Height;

		Camera.Pin[0] = tany * aspect;
		Camera.Pin[5] = tany;
		Camera.Pin[10] = 0.0f;
		Camera.Pin[14] = -1.0f;

		Camera.CalculateRayMatrix();
	}
}

void CRayTracer::Destroy()
{
	DestroyTextures();

	if(Quads != NULL)
	{
		delete [] Quads;
		Quads = NULL;
		QuadsCount = 0;
		LastQuad = NULL;
	}

	if(Spheres != NULL)
	{
		delete [] Spheres;
		Spheres = NULL;
		SpheresCount = 0;
		LastSphere = NULL;
	}

	if(Lights != NULL)
	{
		delete [] Lights;
		Lights = NULL;
		LightsCount = 0;
		LastLight = NULL;
	}

	if(ColorBuffer != NULL)
	{
		delete [] ColorBuffer;
		ColorBuffer = NULL;
	}

	if(HDRColorBuffer != NULL)
	{
		delete [] HDRColorBuffer;
		HDRColorBuffer = NULL;
	}
}

void CRayTracer::ClearColorBuffer()
{
	if(ColorBuffer != NULL)
	{
		memset(ColorBuffer, 0, LineWidth * Height * 3);
	}
}

int CRayTracer::GetSamples()
{
	return Samples * Samples;
}

void CRayTracer::MapHDRColors()
{
	if(ColorBuffer == NULL || HDRColorBuffer == NULL) return;

	float SumLum = 0.0f, LumWhite = 0.0f;
	int LumNotNull = 0;

	vec3 *Color = HDRColorBuffer;

	for(int i = 0; i < WidthMHeightMSamples2; i++)
	{
		float Luminance = (Color->r * 0.2125f + Color->g * 0.7154f + Color->b * 0.0721f);

		if(Luminance > 0.0f)
		{
			SumLum += Luminance;

			LumNotNull++;

			LumWhite = LumWhite > Luminance ? LumWhite : Luminance;
		}

		Color++;
	}

	float AvgLum = SumLum / (float)LumNotNull;

	LumWhite /= AvgLum;

	float LumWhite2 = LumWhite * LumWhite;

	Color = HDRColorBuffer;

	vec3 ColorMMappingFactor;

	for(int i = 0; i < WidthMHeightMSamples2; i++)
	{
		float Luminance = (Color->r * 0.2125f + Color->g * 0.7154f + Color->b * 0.0721f);
			
		float LumRel = Luminance / AvgLum;
		float MappingFactor = LumRel * (1.0f + LumRel / LumWhite2) / (1.0f + LumRel);

		ColorMMappingFactor.r = Color->r * MappingFactor;
		ColorMMappingFactor.g = Color->g * MappingFactor;
		ColorMMappingFactor.b = Color->b * MappingFactor;
		
		Color->r = ColorMMappingFactor.r <= 0.0f ? 0.0f : ColorMMappingFactor.r >= 1.0f ? 1.0f : ColorMMappingFactor.r;
		Color->g = ColorMMappingFactor.g <= 0.0f ? 0.0f : ColorMMappingFactor.g >= 1.0f ? 1.0f : ColorMMappingFactor.g;
		Color->b = ColorMMappingFactor.b <= 0.0f ? 0.0f : ColorMMappingFactor.b >= 1.0f ? 1.0f : ColorMMappingFactor.b;

		Color++;
	}

	int LineWidthSWidthM3 = (LineWidth - Width) * 3;

	BYTE *colorbuffer = ColorBuffer;

	if(Samples == 1)
	{
		Color = HDRColorBuffer;

		for(int y = 0; y < Height; y++)
		{
			for(int x = 0; x < Width; x++)
			{
				colorbuffer[2] = (BYTE)(Color->r * 255);
				colorbuffer[1] = (BYTE)(Color->g * 255);
				colorbuffer[0] = (BYTE)(Color->b * 255);

				Color++;
				colorbuffer += 3;
			}

			colorbuffer += LineWidthSWidthM3;
		}
	}
	else
	{
		for(int y = 0, Y = 0; y < Height; y++, Y += Samples)
		{
			for(int X = 0; X < WidthMSamples; X += Samples)
			{
				vec3 ColorSum;

				for(int yy = 0; yy < Samples; yy++)
				{
					Color = WidthMSamples * (Y + yy) + X + HDRColorBuffer;

					for(int xx = 0; xx < Samples; xx++)
					{
						ColorSum.r += Color->r;
						ColorSum.g += Color->g;
						ColorSum.b += Color->b;

						Color++;
					}
				}

				ColorSum.r *= ODSamples2;
				ColorSum.g *= ODSamples2;
				ColorSum.b *= ODSamples2;

				colorbuffer[2] = (BYTE)(ColorSum.r * 255);
				colorbuffer[1] = (BYTE)(ColorSum.g * 255);
				colorbuffer[0] = (BYTE)(ColorSum.b * 255);

				colorbuffer += 3;
			}

			colorbuffer += LineWidthSWidthM3;
		}
	}
}

bool CRayTracer::SetSamples(int Samples)
{
	if(this->Samples == Samples) return false;

	this->Samples = Samples;

	Resize(Width, Height);

	return true;
}

void CRayTracer::SwapBuffers(HDC hDC)
{
	if(ColorBuffer != NULL)
	{
		StretchDIBits(hDC, 0, 0, Width, Height, 0, 0, Width, Height, ColorBuffer, &ColorBufferInfo, DIB_RGB_COLORS, SRCCOPY);
	}
}

bool CRayTracer::Shadow(void *Object, vec3 &Point, vec3 &LightDirection, float LightDistance)
{
	for(CSphere *Sphere = Spheres; Sphere < LastSphere; Sphere++)
	{
		if(Sphere == Object) continue;

		if(Sphere->Intersect(Point, LightDirection, LightDistance))
		{
			return true;
		}
	}

	for(CQuad *Quad = Quads; Quad < LastQuad; Quad++)
	{
		if(Quad == Object) continue;

		if(Quad->Intersect(Point, LightDirection, LightDistance))
		{
			return true;
		}
	}

	return false;
}

vec3 CRayTracer::LightIntensity(void *Object, vec3 &Point, vec3 &Normal, vec3 &LightPosition, CLight *Light, float AO)
{
	vec3 LightDirection = LightPosition - Point;

	float LightDistance2 = length2(LightDirection);
	float LightDistance = sqrt(LightDistance2);

	LightDirection *= 1.0f / LightDistance;

	float Attenuation = Light->QuadraticAttenuation * LightDistance2 + Light->LinearAttenuation * LightDistance + Light->ConstantAttenuation;

	float NdotLD = dot(Normal, LightDirection);

	if(NdotLD > 0.0f)
	{
		if(Light->Sphere)
		{
			if(Shadow(Object, Point, LightDirection, LightDistance) == false)
			{
				return Light->Sphere->Color * ((Light->Ambient * AO + Light->Diffuse * NdotLD) / Attenuation);
			}
		}
		else
		{
			float LNdotLD = -dot(Light->Quad->N, LightDirection);

			if(LNdotLD > 0.0f)
			{
				if(Shadow(Object, Point, LightDirection, LightDistance) == false)
				{
					return Light->Quad->Color * ((Light->Ambient * AO + Light->Diffuse * NdotLD * LNdotLD) / Attenuation);
				}
			}
		}
	}

	return (Light->Sphere ? Light->Sphere->Color : Light->Quad->Color) * (Light->Ambient * AO / Attenuation);
}

float TDRM = 2.0f / (float)RAND_MAX;

float CRayTracer::AmbientOcclusionFactor(void *Object, vec3 &Point, vec3 &Normal)
{
	float AO = 0.0f;

	for(int i = 0; i < GISamples; i++)
	{
		vec3 RandomRay = normalize(vec3(TDRM * (float)rand() - 1.0f, TDRM * (float)rand() - 1.0f, TDRM * (float)rand() - 1.0f));

		float NdotRR = dot(Normal, RandomRay);

		if(NdotRR < 0.0f)
		{
			RandomRay = -RandomRay;
			NdotRR = -NdotRR;
		}

		float Distance = 1048576.0f, TestDistance;

		for(CSphere *Sphere = Spheres; Sphere < LastSphere; Sphere++)
		{
			if(Sphere == Object) continue;

			if(Sphere->Intersect(Point, RandomRay, Distance, TestDistance))
			{
				Distance = TestDistance;
			}
		}

		for(CQuad *Quad = Quads; Quad < LastQuad; Quad++)
		{
			if(Quad == Object) continue;

			if(Quad->Intersect(Point, RandomRay, Distance, TestDistance))
			{
				Distance = TestDistance;
			}
		}

		AO += NdotRR / (1.0f + Distance * Distance);
	}

	return 1.0f - AO * ODGISamplesMAmbientOcclusionIntensity;
}

float ODRM = 1.0f / (float)RAND_MAX;

void CRayTracer::IlluminatePoint(void *Object, vec3 &Point, vec3 &Normal, vec3 &Color)
{
	float AO = 1.0f;

	if(AmbientOcclusion)
	{
		AO = AmbientOcclusionFactor(Object, Point, Normal);
	}

	if(LightsCount == 0)
	{
		float NdotCD = dot(Normal, normalize(Camera.Position - Point));

		if(NdotCD > 0.0f)
		{
			Color *= 0.5f * (AO + NdotCD);
		}
		else
		{
			Color *= 0.5f * AO;
		}
	}
	else if(SoftShadows == false)
	{
		vec3 LightsIntensitiesSum;

		for(CLight *Light = Lights; Light < LastLight; Light++)
		{
			LightsIntensitiesSum += LightIntensity(Object, Point, Normal, Light->Sphere ? Light->Sphere->Position : Light->Quad->m, Light, AO);
		}

		Color *= LightsIntensitiesSum;
	}
	else
	{
		vec3 LightsIntensitiesSum;

		for(CLight *Light = Lights; Light < LastLight; Light++)
		{
			if(Light->Sphere)
			{
				for(int i = 0; i < GISamples; i++)
				{
					vec3 RandomRay = /*normalize(*/vec3(TDRM * (float)rand() - 1.0f, TDRM * (float)rand() - 1.0f, TDRM * (float)rand() - 1.0f)/*)*/;

					vec3 RandomLightPosition = RandomRay * Light->Sphere->Radius + Light->Sphere->Position;

					LightsIntensitiesSum += LightIntensity(Object, Point, Normal, RandomLightPosition, Light, AO);
				}
			}
			else
			{
				for(int i = 0; i < GISamples; i++)
				{
					float s = ODRM * (float)rand();
					float t = ODRM * (float)rand();

					vec3 RandomLightPosition = Light->Quad->ab * s + Light->Quad->ad * t + Light->Quad->a;

					LightsIntensitiesSum += LightIntensity(Object, Point, Normal, RandomLightPosition, Light, AO);
				}
			}
		}

		Color *= LightsIntensitiesSum * ODGISamples;
	}
}

float M_1_PI_2 = (float)M_1_PI * 0.5f;

vec3 CRayTracer::RayTrace(vec3 &Origin, const vec3 &Ray, UINT Depth, void *Object)
{
	RTData Data;

	for(CSphere *Sphere = Spheres; Sphere < LastSphere; Sphere++)
	{
		if(Sphere == Object) continue;

		if(Sphere->Intersect(Origin, Ray, Data.Distance, Data.TestDistance, Data.TestPoint))
		{
			Data.Point = Data.TestPoint;
			Data.Distance = Data.TestDistance;
			Data.Sphere = Sphere;
		}
	}

	for(CQuad *Quad = Quads; Quad < LastQuad; Quad++)
	{
		if(Quad == Object) continue;

		if(Quad->Intersect(Origin, Ray, Data.Distance, Data.TestDistance, Data.TestPoint))
		{
			Data.Point = Data.TestPoint;
			Data.Distance = Data.TestDistance;
			Data.Quad = Quad;
		}
	}

	for(CLight *Light = Lights; Light < LastLight; Light++)
	{
		if(Light->Sphere)
		{
			if(Light->Sphere->Intersect(Origin, Ray, Data.Distance, Data.TestDistance, Data.TestPoint))
			{
				Data.Point = Data.TestPoint;
				Data.Distance = Data.TestDistance;
				Data.Light = Light;
			}
		}
		else
		{
			if(Light->Quad->Intersect(Origin, Ray, Data.Distance, Data.TestDistance, Data.TestPoint))
			{
				Data.Point = Data.TestPoint;
				Data.Distance = Data.TestDistance;
				Data.Light = Light;
			}
		}
	}

	if(Data.Light)
	{
		Data.Color = Data.Light->Sphere ? Data.Light->Sphere->Color : Data.Light->Quad->Color;
	}
	else if(Data.Quad)
	{
		Data.Color = Data.Quad->Color;

		if(Textures && Data.Quad->Texture)
		{
			float s = dot(Data.Quad->T, Data.Point) - Data.Quad->O.x;
			float t = dot(Data.Quad->B, Data.Point) - Data.Quad->O.y;

			Data.Color *= Data.Quad->Texture->GetColorBilinear(s, t);
		}

		IlluminatePoint(Data.Quad, Data.Point, Data.Quad->N, Data.Color);
		
		if(Data.Quad->Reflection > 0.0f)
		{
			vec3 ReflectedRay = reflect(Ray, Data.Quad->N);

			Data.Color = mix(Data.Color, RayTrace(Data.Point, ReflectedRay, Depth + 1, Data.Quad), Data.Quad->Reflection);
		}

		/*if(Data.Quad->Refraction > 0.0f)
		{
			float Angle = -dot(Data.Quad->N, Ray);

			vec3 Normal;
			float Eta;
			
			if(Angle > 0.0f)
			{
				Normal = Data.Quad->N;
				Eta = Data.Quad->ODEta;
			}
			else
			{
				Normal = -Data.Quad->N;
				Eta = Data.Quad->Eta;
			}

			vec3 RefractedRay = refract(Ray, Normal, Eta);

			if(RefractedRay.x == 0.0f && RefractedRay.y == 0.0f && RefractedRay.z == 0.0f)
			{
				RefractedRay = reflect(Ray, Normal);
			}

			Data.Color = mix(Data.Color, RayTrace(Data.Point, RefractedRay, Depth + 1, Data.Quad), Data.Quad->Refraction);
		}*/
	}
	else if(Data.Sphere)
	{
		Data.Color = Data.Sphere->Color;

		vec3 Normal = (Data.Point - Data.Sphere->Position) * Data.Sphere->ODRadius;

		if(Textures && Data.Sphere->Texture)
		{
			float s = atan2(Normal.x, Normal.z) * M_1_PI_2 + 0.5f;
			float t = asin(Normal.y < -1.0f ? -1.0f : Normal.y > 1.0f ? 1.0f : Normal.y) * (float)M_1_PI + 0.5f;

			Data.Color *= Data.Sphere->Texture->GetColorBilinear(s, t);
		}

		IlluminatePoint(Data.Sphere, Data.Point, Normal, Data.Color);

		if(Data.Sphere->Refraction > 0.0f)
		{
			vec3 RefractedRay = refract(Ray, Normal, Data.Sphere->ODEta);

			vec3 L = Data.Sphere->Position - Data.Point;
			float LdotRR = dot(L, RefractedRay);
			float D2 = length2(L) - LdotRR * LdotRR;
			float Distance = LdotRR + sqrt(Data.Sphere->Radius2 - D2);

			vec3 NewPoint = RefractedRay * Distance + Data.Point;

			vec3 NewNormal = (Data.Sphere->Position - NewPoint) * Data.Sphere->ODRadius;

			RefractedRay = refract(RefractedRay, NewNormal, Data.Sphere->Eta);

			Data.Color = mix(Data.Color, RayTrace(NewPoint, RefractedRay, Depth + 1, Data.Sphere), Data.Sphere->Refraction);
		}

		if(Data.Sphere->Reflection > 0.0f)
		{
			vec3 ReflectedRay = reflect(Ray, Normal);

			Data.Color = mix(Data.Color, RayTrace(Data.Point, ReflectedRay, Depth + 1, Data.Sphere), Data.Sphere->Reflection);
		}
	}

	return Data.Color;
}

// ----------------------------------------------------------------------------------------------------------------------------

bool CMyRayTracer::InitScene()
{
	bool Error = false;

	Error |= !Floor.CreateTexture2D("floor.jpg");

	Error |= !Cube.CreateTexture2D("cube.jpg");

	Error |= !Earth.CreateTexture2D("earth.jpg");

	if(Error)
	{
		return false;
	}

	if(0) // Textured cube
	{
		QuadsCount = 6;

		Quads = new CQuad[QuadsCount];

		Quads[0] =  CQuad(vec3(-0.5f, -0.5f,  0.5f), vec3( 0.5f, -0.5f,  0.5f), vec3( 0.5f,  0.5f,  0.5f), vec3(-0.5f,  0.5f, 0.5f), vec3(1.0f, 1.0f, 1.0f), &Cube);
		Quads[1] =  CQuad(vec3( 0.5f, -0.5f, -0.5f), vec3(-0.5f, -0.5f, -0.5f), vec3(-0.5f,  0.5f, -0.5f), vec3( 0.5f,  0.5f,-0.5f), vec3(1.0f, 1.0f, 1.0f), &Cube);
		Quads[2] =  CQuad(vec3( 0.5f, -0.5f,  0.5f), vec3( 0.5f, -0.5f, -0.5f), vec3( 0.5f,  0.5f, -0.5f), vec3( 0.5f,  0.5f, 0.5f), vec3(1.0f, 1.0f, 1.0f), &Cube);
		Quads[3] =  CQuad(vec3(-0.5f, -0.5f, -0.5f), vec3(-0.5f, -0.5f,  0.5f), vec3(-0.5f,  0.5f,  0.5f), vec3(-0.5f,  0.5f,-0.5f), vec3(1.0f, 1.0f, 1.0f), &Cube);
		Quads[4] =  CQuad(vec3(-0.5f,  0.5f,  0.5f), vec3( 0.5f,  0.5f,  0.5f), vec3( 0.5f,  0.5f, -0.5f), vec3(-0.5f,  0.5f,-0.5f), vec3(1.0f, 1.0f, 1.0f), &Cube);
		Quads[5] =  CQuad(vec3(-0.5f, -0.5f, -0.5f), vec3( 0.5f, -0.5f, -0.5f), vec3( 0.5f, -0.5f,  0.5f), vec3(-0.5f, -0.5f, 0.5f), vec3(1.0f, 1.0f, 1.0f), &Cube);
	}
	else if(0) // Textured sphere
	{
		SpheresCount = 1;

		Spheres = new CSphere[SpheresCount];

		Spheres[0] = CSphere(vec3(0.0f, 0.0f, 0.0f), 0.5f, vec3(1.0f, 1.0f, 1.0f), &Earth);
	}
	else if(0) // 100 random spheres
	{
		SpheresCount = 100;

		Spheres = new CSphere[SpheresCount];

		for(int i = 0; i < SpheresCount; i++)
		{
			#define rnd (float)rand() / (float)RAND_MAX

			vec3 Position = (vec3(rnd, rnd, rnd) * 2.0f - 1.0f) * 2.5f;
			float Radius = 0.125f + rnd * 0.25f;
			vec3 Color = vec3(rnd, rnd, rnd) * 2.0f;
			float Reflection = 0.25f + rnd * 0.5f;

			Spheres[i] = CSphere(Position, Radius, Color, NULL, Reflection);
		}
	}
	else if(0) // 50 random cubes
	{
		QuadsCount = 300;

		Quads = new CQuad[QuadsCount];

		for(int i = 0; i < QuadsCount; i += 6)
		{
			#define rnd (float)rand() / (float)RAND_MAX

			float S = 0.5f + rnd * 0.5f;
			vec3 T = (vec3(rnd, rnd, rnd) * 2.0f - 1.0f) * 2.5f;
			vec3 Color = vec3(rnd, rnd, rnd) * 2.0f;
			float Reflection = 0.25f + rnd * 0.5f;

			Quads[i + 0] =  CQuad(vec3(-0.5f, -0.5f,  0.5f) * S + T, vec3( 0.5f, -0.5f,  0.5f) * S + T, vec3( 0.5f,  0.5f,  0.5f) * S + T, vec3(-0.5f,  0.5f, 0.5f) * S + T, Color, NULL, Reflection);
			Quads[i + 1] =  CQuad(vec3( 0.5f, -0.5f, -0.5f) * S + T, vec3(-0.5f, -0.5f, -0.5f) * S + T, vec3(-0.5f,  0.5f, -0.5f) * S + T, vec3( 0.5f,  0.5f,-0.5f) * S + T, Color, NULL, Reflection);
			Quads[i + 2] =  CQuad(vec3( 0.5f, -0.5f,  0.5f) * S + T, vec3( 0.5f, -0.5f, -0.5f) * S + T, vec3( 0.5f,  0.5f, -0.5f) * S + T, vec3( 0.5f,  0.5f, 0.5f) * S + T, Color, NULL, Reflection);
			Quads[i + 3] =  CQuad(vec3(-0.5f, -0.5f, -0.5f) * S + T, vec3(-0.5f, -0.5f,  0.5f) * S + T, vec3(-0.5f,  0.5f,  0.5f) * S + T, vec3(-0.5f,  0.5f,-0.5f) * S + T, Color, NULL, Reflection);
			Quads[i + 4] =  CQuad(vec3(-0.5f,  0.5f,  0.5f) * S + T, vec3( 0.5f,  0.5f,  0.5f) * S + T, vec3( 0.5f,  0.5f, -0.5f) * S + T, vec3(-0.5f,  0.5f,-0.5f) * S + T, Color, NULL, Reflection);
			Quads[i + 5] =  CQuad(vec3(-0.5f, -0.5f, -0.5f) * S + T, vec3( 0.5f, -0.5f, -0.5f) * S + T, vec3( 0.5f, -0.5f,  0.5f) * S + T, vec3(-0.5f, -0.5f, 0.5f) * S + T, Color, NULL, Reflection);
		}
	}
	else if(0) // Cornell box
	{
		SpheresCount = 1;

		Spheres = new CSphere[SpheresCount];

		Spheres[0] = CSphere(vec3(0.0f, -1.5f, 1.0f), 0.5f, vec3(0.0f, 0.5f, 1.0f), NULL, 0.125f, 0.875f, 1.52f);

		QuadsCount = 17;

		Quads = new CQuad[QuadsCount + LightsCount];

		mat4x4 R = RotationMatrix(22.5f, vec3(0.0f, 1.0f, 0.0f));
		vec3 V = vec3(1.0f, 0.0f, 0.0f);

		Quads[0] =  CQuad(R * vec3(-0.5f, -2.0f,  0.5f) + V, R * vec3( 0.5f, -2.0f,  0.5f) + V, R * vec3( 0.5f, -1.0f,  0.5f) + V, R * vec3(-0.5f, -1.0f,  0.5f) + V, vec3(1.0f, 1.0f, 1.0f), &Cube);
		Quads[1] =  CQuad(R * vec3( 0.5f, -2.0f, -0.5f) + V, R * vec3(-0.5f, -2.0f, -0.5f) + V, R * vec3(-0.5f, -1.0f, -0.5f) + V, R * vec3( 0.5f, -1.0f, -0.5f) + V, vec3(1.0f, 1.0f, 1.0f), &Cube);
		Quads[2] =  CQuad(R * vec3( 0.5f, -2.0f,  0.5f) + V, R * vec3( 0.5f, -2.0f, -0.5f) + V, R * vec3( 0.5f, -1.0f, -0.5f) + V, R * vec3( 0.5f, -1.0f,  0.5f) + V, vec3(1.0f, 1.0f, 1.0f), &Cube);
		Quads[3] =  CQuad(R * vec3(-0.5f, -2.0f, -0.5f) + V, R * vec3(-0.5f, -2.0f,  0.5f) + V, R * vec3(-0.5f, -1.0f,  0.5f) + V, R * vec3(-0.5f, -1.0f, -0.5f) + V, vec3(1.0f, 1.0f, 1.0f), &Cube);
		Quads[4] =  CQuad(R * vec3(-0.5f, -1.0f,  0.5f) + V, R * vec3( 0.5f, -1.0f,  0.5f) + V, R * vec3( 0.5f, -1.0f, -0.5f) + V, R * vec3(-0.5f, -1.0f, -0.5f) + V, vec3(1.0f, 1.0f, 1.0f), &Cube);
		Quads[5] =  CQuad(R * vec3(-0.5f, -2.0f, -0.5f) + V, R * vec3( 0.5f, -2.0f, -0.5f) + V, R * vec3( 0.5f, -2.0f,  0.5f) + V, R * vec3(-0.5f, -2.0f,  0.5f) + V, vec3(1.0f, 1.0f, 1.0f), &Cube);
		
		Quads[6] =  CQuad(vec3(-2.0f, -2.0f,  2.0f), vec3( 2.0f, -2.0f,  2.0f), vec3( 2.0f, -2.0f, -2.0f), vec3(-2.0f, -2.0f, -2.0f), vec3(1.0f, 1.0f, 1.0f), &Floor, 0.0625f);
		Quads[7] =  CQuad(vec3(-2.0f,  2.0f, -2.0f), vec3( 2.0f,  2.0f, -2.0f), vec3( 2.0f,  2.0f,  2.0f), vec3(-2.0f,  2.0f,  2.0f), vec3(1.0f, 1.0f, 1.0f));
		Quads[8] =  CQuad(vec3(-2.0f, -2.0f, -2.0f), vec3( 2.0f, -2.0f, -2.0f), vec3( 2.0f,  2.0f, -2.0f), vec3(-2.0f,  2.0f, -2.0f), vec3(1.0f, 1.0f, 1.0f));
		Quads[9] =  CQuad(vec3( 2.0f, -2.0f,  2.0f), vec3(-2.0f, -2.0f,  2.0f), vec3(-2.0f,  2.0f,  2.0f), vec3( 2.0f,  2.0f,  2.0f), vec3(1.0f, 1.0f, 1.0f));
		Quads[10] = CQuad(vec3( 2.0f, -2.0f, -2.0f), vec3( 2.0f, -2.0f,  2.0f), vec3( 2.0f,  2.0f,  2.0f), vec3( 2.0f,  2.0f, -2.0f), vec3(0.0f, 1.0f, 0.0f));
		Quads[11] = CQuad(vec3(-2.0f, -2.0f,  2.0f), vec3(-2.0f, -2.0f, -2.0f), vec3(-2.0f,  2.0f, -2.0f), vec3(-2.0f,  2.0f,  2.0f), vec3(1.0f, 0.0f, 0.0f));

		Quads[12] = CQuad(vec3(-0.5f,  1.875f,  0.5f), vec3( 0.5f,  1.875f,  0.5f), vec3( 0.5f,  1.875f, -0.5f), vec3(-0.5f,  1.875f, -0.5f), vec3(1.0f, 1.0f, 1.0f));

		Quads[13] = CQuad(vec3(-0.5f,  1.875f - 0.125f,  0.5f), vec3( 0.5f,  1.875f - 0.125f,  0.5f), vec3( 0.5f,  2.0f - 0.125f,  0.5f), vec3(-0.5f,  2.0f - 0.125f,  0.5f), vec3(1.0f, 1.0f, 1.0f));
		Quads[14] = CQuad(vec3( 0.5f,  1.875f - 0.125f, -0.5f), vec3(-0.5f,  1.875f - 0.125f, -0.5f), vec3(-0.5f,  2.0f - 0.125f, -0.5f), vec3( 0.5f,  2.0f - 0.125f, -0.5f), vec3(1.0f, 1.0f, 1.0f));
		Quads[15] = CQuad(vec3(-0.5f,  1.875f - 0.125f, -0.5f), vec3(-0.5f,  1.875f - 0.125f,  0.5f), vec3(-0.5f,  2.0f - 0.125f,  0.5f), vec3(-0.5f,  2.0f - 0.125f, -0.5f), vec3(1.0f, 1.0f, 1.0f));
		Quads[16] = CQuad(vec3( 0.5f,  1.875f - 0.125f,  0.5f), vec3( 0.5f,  1.875f - 0.125f, -0.5f), vec3( 0.5f,  2.0f - 0.125f, -0.5f), vec3( 0.5f,  2.0f - 0.125f,  0.5f), vec3(1.0f, 1.0f, 1.0f));

		LightsCount = 1;

		Lights = new CLight[LightsCount];

		Lights[0].Quad = new CQuad(vec3(-0.5f,  1.875f - 0.125f, -0.5f), vec3( 0.5f,  1.875f - 0.125f, -0.5f), vec3( 0.5f,  1.875f - 0.125f,  0.5f), vec3(-0.5f,  1.875f - 0.125f,  0.5f), vec3(3.0f, 3.0f, 3.0f));
		Lights[0].Ambient = 0.25f;
		Lights[0].Diffuse = 0.75f;
		Lights[0].QuadraticAttenuation = 0.0625f;
	}
	else
	{
		SpheresCount = 3;

		Spheres = new CSphere[SpheresCount];

		Spheres[0] = CSphere(vec3(-2.0f, -1.0f,  2.0f), 0.5f, vec3(0.0f, 0.5f, 1.0f), NULL, 0.875f);
		Spheres[1] = CSphere(vec3( 0.0f, -1.5f,  2.0f), 0.5f, vec3(0.0f, 0.5f, 1.0f), NULL, 0.125f, 0.875f, 1.52f);
		Spheres[2] = CSphere(vec3( 2.0f, -1.5f, -2.0f), 0.5f, vec3(1.0f, 1.0f, 1.0f), &Earth);

		QuadsCount = 21;
		// QuadsCount = 31;

		Quads = new CQuad[QuadsCount];

		LightsCount = 1;
		// LightsCount = 2;
		// LightsCount = 3;

		Lights = new CLight[LightsCount];

		mat4x4 R = RotationMatrix(22.5f, vec3(0.0f, 1.0f, 0.0f));
		vec3 V = vec3(2.0f, 0.0f, 2.0f);

		Quads[0] =  CQuad(R * vec3(-0.5f, -2.0f,  0.5f) + V, R * vec3( 0.5f, -2.0f,  0.5f) + V, R * vec3( 0.5f, -1.0f,  0.5f) + V, R * vec3(-0.5f, -1.0f,  0.5f) + V, vec3(1.0f, 1.0f, 1.0f), &Cube);
		Quads[1] =  CQuad(R * vec3( 0.5f, -2.0f, -0.5f) + V, R * vec3(-0.5f, -2.0f, -0.5f) + V, R * vec3(-0.5f, -1.0f, -0.5f) + V, R * vec3( 0.5f, -1.0f, -0.5f) + V, vec3(1.0f, 1.0f, 1.0f), &Cube);
		Quads[2] =  CQuad(R * vec3( 0.5f, -2.0f,  0.5f) + V, R * vec3( 0.5f, -2.0f, -0.5f) + V, R * vec3( 0.5f, -1.0f, -0.5f) + V, R * vec3( 0.5f, -1.0f,  0.5f) + V, vec3(1.0f, 1.0f, 1.0f), &Cube);
		Quads[3] =  CQuad(R * vec3(-0.5f, -2.0f, -0.5f) + V, R * vec3(-0.5f, -2.0f,  0.5f) + V, R * vec3(-0.5f, -1.0f,  0.5f) + V, R * vec3(-0.5f, -1.0f, -0.5f) + V, vec3(1.0f, 1.0f, 1.0f), &Cube);
		Quads[4] =  CQuad(R * vec3(-0.5f, -1.0f,  0.5f) + V, R * vec3( 0.5f, -1.0f,  0.5f) + V, R * vec3( 0.5f, -1.0f, -0.5f) + V, R * vec3(-0.5f, -1.0f, -0.5f) + V, vec3(1.0f, 1.0f, 1.0f), &Cube);
		Quads[5] =  CQuad(R * vec3(-0.5f, -2.0f, -0.5f) + V, R * vec3( 0.5f, -2.0f, -0.5f) + V, R * vec3( 0.5f, -2.0f,  0.5f) + V, R * vec3(-0.5f, -2.0f,  0.5f) + V, vec3(1.0f, 1.0f, 1.0f), &Cube);
		
		Quads[6] =  CQuad(vec3(-0.0f, -2.0f,  4.0f), vec3( 4.0f, -2.0f,  4.0f), vec3( 4.0f, -2.0f, -4.0f), vec3(-0.0f, -2.0f, -4.0f), vec3(1.0f, 1.0f, 1.0f), &Floor, 0.0625f);
		Quads[7] =  CQuad(vec3(-4.0f, -2.0f,  4.0f), vec3( 0.0f, -2.0f,  4.0f), vec3( 0.0f, -2.0f,  0.0f), vec3(-4.0f, -2.0f,  0.0f), vec3(1.0f, 1.0f, 1.0f), &Floor, 0.0625f);
		Quads[8] =  CQuad(vec3( 0.0f,  2.0f, -4.0f), vec3( 4.0f,  2.0f, -4.0f), vec3( 4.0f,  2.0f,  4.0f), vec3( 0.0f,  2.0f,  4.0f), vec3(1.0f, 1.0f, 1.0f));
		Quads[9] =  CQuad(vec3(-4.0f,  2.0f,  0.0f), vec3( 0.0f,  2.0f,  0.0f), vec3( 0.0f,  2.0f,  4.0f), vec3(-4.0f,  2.0f,  4.0f), vec3(1.0f, 1.0f, 1.0f));
		Quads[10] = CQuad(vec3(-0.0f, -2.0f, -4.0f), vec3( 4.0f, -2.0f, -4.0f), vec3( 4.0f,  2.0f, -4.0f), vec3(-0.0f,  2.0f, -4.0f), vec3(1.0f, 1.0f, 1.0f));
		Quads[11] = CQuad(vec3( 4.0f, -2.0f,  4.0f), vec3(-4.0f, -2.0f,  4.0f), vec3(-4.0f,  2.0f,  4.0f), vec3( 4.0f,  2.0f,  4.0f), vec3(1.0f, 1.0f, 1.0f));
		Quads[12] = CQuad(vec3( 4.0f, -2.0f, -4.0f), vec3( 4.0f, -2.0f,  4.0f), vec3( 4.0f,  2.0f,  4.0f), vec3( 4.0f,  2.0f, -4.0f), vec3(0.0f, 1.0f, 0.0f));
		Quads[13] = CQuad(vec3(-4.0f, -2.0f,  4.0f), vec3(-4.0f, -2.0f, -0.0f), vec3(-4.0f,  2.0f, -0.0f), vec3(-4.0f,  2.0f,  4.0f), vec3(1.0f, 0.0f, 0.0f));
		Quads[14] = CQuad(vec3(-4.0f, -2.0f,  0.0f), vec3( 0.0f, -2.0f,  0.0f), vec3( 0.0f,  2.0f,  0.0f), vec3(-4.0f,  2.0f,  0.0f), vec3(1.0f, 1.0f, 1.0f));
		Quads[15] = CQuad(vec3( 0.0f, -2.0f,  0.0f), vec3( 0.0f, -2.0f, -4.0f), vec3( 0.0f,  2.0f, -4.0f), vec3( 0.0f,  2.0f,  0.0f), vec3(1.0f, 1.0f, 1.0f));

		vec3 S = vec3(-2.0f, 0.0f, 2.0f);

		Quads[16] = CQuad(vec3(-0.5f,  1.875f,  0.5f) + S, vec3( 0.5f,  1.875f,  0.5f) + S, vec3( 0.5f,  1.875f, -0.5f) + S, vec3(-0.5f,  1.875f, -0.5f) + S, vec3(1.0f, 1.0f, 1.0f));
		Quads[17] = CQuad(vec3(-0.5f,  1.875f - 0.125f,  0.5f) + S, vec3( 0.5f,  1.875f - 0.125f,  0.5f) + S, vec3( 0.5f,  2.0f - 0.125f,  0.5f) + S, vec3(-0.5f,  2.0f - 0.125f,  0.5f) + S, vec3(1.0f, 1.0f, 1.0f));
		Quads[18] = CQuad(vec3( 0.5f,  1.875f - 0.125f, -0.5f) + S, vec3(-0.5f,  1.875f - 0.125f, -0.5f) + S, vec3(-0.5f,  2.0f - 0.125f, -0.5f) + S, vec3( 0.5f,  2.0f - 0.125f, -0.5f) + S, vec3(1.0f, 1.0f, 1.0f));
		Quads[19] = CQuad(vec3(-0.5f,  1.875f - 0.125f, -0.5f) + S, vec3(-0.5f,  1.875f - 0.125f,  0.5f) + S, vec3(-0.5f,  2.0f - 0.125f,  0.5f) + S, vec3(-0.5f,  2.0f - 0.125f, -0.5f) + S, vec3(1.0f, 1.0f, 1.0f));
		Quads[20] = CQuad(vec3( 0.5f,  1.875f - 0.125f,  0.5f) + S, vec3( 0.5f,  1.875f - 0.125f, -0.5f) + S, vec3( 0.5f,  2.0f - 0.125f, -0.5f) + S, vec3( 0.5f,  2.0f - 0.125f,  0.5f) + S, vec3(1.0f, 1.0f, 1.0f));

		Lights[0].Quad = new CQuad(vec3(-0.5f,  1.875f - 0.125f, -0.5f) + S, vec3( 0.5f,  1.875f - 0.125f, -0.5f) + S, vec3( 0.5f,  1.875f - 0.125f,  0.5f) + S, vec3(-0.5f,  1.875f - 0.125f,  0.5f) + S, vec3(3.0f, 3.0f, 3.0f));
		// Lights[0].Quad = new CQuad(vec3(-0.5f,  1.875f - 0.125f, -0.5f) + S, vec3( 0.5f,  1.875f - 0.125f, -0.5f) + S, vec3( 0.5f,  1.875f - 0.125f,  0.5f) + S, vec3(-0.5f,  1.875f - 0.125f,  0.5f) + S, vec3(1.0f, 1.0f, 1.0f));
		Lights[0].Ambient = 0.25f;
		Lights[0].Diffuse = 0.75f;
		// Lights[0].LinearAttenuation = 0.09375f;
		// Lights[0].LinearAttenuation = 0.125f;

		// Lights[1].Sphere = new CSphere(vec3( 2.0f, 0.0f, 2.0f), 0.03125f, vec3(1.0f, 1.0f, 1.0f));
		// Lights[1].Ambient = 0.25f;
		// Lights[1].Diffuse = 0.75f;
		// Lights[1].LinearAttenuation = 0.125f;

		/* Lights[0].Quad = new CQuad(vec3(-0.5f,  1.875f - 0.125f, -0.5f) + S, vec3( 0.5f,  1.875f - 0.125f, -0.5f) + S, vec3( 0.5f,  1.875f - 0.125f,  0.5f) + S, vec3(-0.5f,  1.875f - 0.125f,  0.5f) + S, vec3(3.0f, 0.0f, 0.0f));
		// Lights[0].Quad = new CQuad(vec3(-0.5f,  1.875f - 0.125f, -0.5f) + S, vec3( 0.5f,  1.875f - 0.125f, -0.5f) + S, vec3( 0.5f,  1.875f - 0.125f,  0.5f) + S, vec3(-0.5f,  1.875f - 0.125f,  0.5f) + S, vec3(1.0f, 1.0f, 1.0f));
		Lights[0].Ambient = 0.25f;
		Lights[0].Diffuse = 0.75f;
		Lights[0].LinearAttenuation = 0.09375f;
		// Lights[0].LinearAttenuation = 0.125f;

		S.x += 2.0f;

		Quads[21] = CQuad(vec3(-0.5f,  1.875f,  0.5f) + S, vec3( 0.5f,  1.875f,  0.5f) + S, vec3( 0.5f,  1.875f, -0.5f) + S, vec3(-0.5f,  1.875f, -0.5f) + S, vec3(1.0f, 1.0f, 1.0f));
		Quads[22] = CQuad(vec3(-0.5f,  1.875f - 0.125f,  0.5f) + S, vec3( 0.5f,  1.875f - 0.125f,  0.5f) + S, vec3( 0.5f,  2.0f - 0.125f,  0.5f) + S, vec3(-0.5f,  2.0f - 0.125f,  0.5f) + S, vec3(1.0f, 1.0f, 1.0f));
		Quads[23] = CQuad(vec3( 0.5f,  1.875f - 0.125f, -0.5f) + S, vec3(-0.5f,  1.875f - 0.125f, -0.5f) + S, vec3(-0.5f,  2.0f - 0.125f, -0.5f) + S, vec3( 0.5f,  2.0f - 0.125f, -0.5f) + S, vec3(1.0f, 1.0f, 1.0f));
		Quads[24] = CQuad(vec3(-0.5f,  1.875f - 0.125f, -0.5f) + S, vec3(-0.5f,  1.875f - 0.125f,  0.5f) + S, vec3(-0.5f,  2.0f - 0.125f,  0.5f) + S, vec3(-0.5f,  2.0f - 0.125f, -0.5f) + S, vec3(1.0f, 1.0f, 1.0f));
		Quads[25] = CQuad(vec3( 0.5f,  1.875f - 0.125f,  0.5f) + S, vec3( 0.5f,  1.875f - 0.125f, -0.5f) + S, vec3( 0.5f,  2.0f - 0.125f, -0.5f) + S, vec3( 0.5f,  2.0f - 0.125f,  0.5f) + S, vec3(1.0f, 1.0f, 1.0f));

		Lights[1].Quad = new CQuad(vec3(-0.5f,  1.875f - 0.125f, -0.5f) + S, vec3( 0.5f,  1.875f - 0.125f, -0.5f) + S, vec3( 0.5f,  1.875f - 0.125f,  0.5f) + S, vec3(-0.5f,  1.875f - 0.125f,  0.5f) + S, vec3(0.0f, 3.0f, 0.0f));
		// Lights[1].Quad = new CQuad(vec3(-0.5f,  1.875f - 0.125f, -0.5f) + S, vec3( 0.5f,  1.875f - 0.125f, -0.5f) + S, vec3( 0.5f,  1.875f - 0.125f,  0.5f) + S, vec3(-0.5f,  1.875f - 0.125f,  0.5f) + S, vec3(1.0f, 1.0f, 1.0f));
		Lights[1].Ambient = 0.25f;
		Lights[1].Diffuse = 0.75f;
		Lights[1].LinearAttenuation = 0.09375f;
		// Lights[1].LinearAttenuation = 0.125f;

		S.x += 2.0f;

		Quads[26] = CQuad(vec3(-0.5f,  1.875f,  0.5f) + S, vec3( 0.5f,  1.875f,  0.5f) + S, vec3( 0.5f,  1.875f, -0.5f) + S, vec3(-0.5f,  1.875f, -0.5f) + S, vec3(1.0f, 1.0f, 1.0f));
		Quads[27] = CQuad(vec3(-0.5f,  1.875f - 0.125f,  0.5f) + S, vec3( 0.5f,  1.875f - 0.125f,  0.5f) + S, vec3( 0.5f,  2.0f - 0.125f,  0.5f) + S, vec3(-0.5f,  2.0f - 0.125f,  0.5f) + S, vec3(1.0f, 1.0f, 1.0f));
		Quads[28] = CQuad(vec3( 0.5f,  1.875f - 0.125f, -0.5f) + S, vec3(-0.5f,  1.875f - 0.125f, -0.5f) + S, vec3(-0.5f,  2.0f - 0.125f, -0.5f) + S, vec3( 0.5f,  2.0f - 0.125f, -0.5f) + S, vec3(1.0f, 1.0f, 1.0f));
		Quads[29] = CQuad(vec3(-0.5f,  1.875f - 0.125f, -0.5f) + S, vec3(-0.5f,  1.875f - 0.125f,  0.5f) + S, vec3(-0.5f,  2.0f - 0.125f,  0.5f) + S, vec3(-0.5f,  2.0f - 0.125f, -0.5f) + S, vec3(1.0f, 1.0f, 1.0f));
		Quads[30] = CQuad(vec3( 0.5f,  1.875f - 0.125f,  0.5f) + S, vec3( 0.5f,  1.875f - 0.125f, -0.5f) + S, vec3( 0.5f,  2.0f - 0.125f, -0.5f) + S, vec3( 0.5f,  2.0f - 0.125f,  0.5f) + S, vec3(1.0f, 1.0f, 1.0f));

		Lights[2].Quad = new CQuad(vec3(-0.5f,  1.875f - 0.125f, -0.5f) + S, vec3( 0.5f,  1.875f - 0.125f, -0.5f) + S, vec3( 0.5f,  1.875f - 0.125f,  0.5f) + S, vec3(-0.5f,  1.875f - 0.125f,  0.5f) + S, vec3(0.0f, 0.0f, 3.0f));
		// Lights[2].Quad = new CQuad(vec3(-0.5f,  1.875f - 0.125f, -0.5f) + S, vec3( 0.5f,  1.875f - 0.125f, -0.5f) + S, vec3( 0.5f,  1.875f - 0.125f,  0.5f) + S, vec3(-0.5f,  1.875f - 0.125f,  0.5f) + S, vec3(1.0f, 1.0f, 1.0f));
		Lights[2].Ambient = 0.25f;
		Lights[2].Diffuse = 0.75f;
		Lights[2].LinearAttenuation = 0.09375f;
		// Lights[2].LinearAttenuation = 0.125f; */
	}

	Camera.LookAt(vec3(0.0f), vec3(0.0f, 0.0f, 8.75f), true);
	// Camera.LookAt(vec3(0.0f), rotate(vec3(0.0f, 0.0f, 8.75f), 45.0f, vec3(0.0f, 1.0f, 0.0f)), true);
	// Camera.LookAt(vec3(0.0f), rotate(vec3(0.0f, 0.0f, 8.75f), 135.0f, vec3(0.0f, 1.0f, 0.0f)), true);
	// Camera.LookAt(vec3(0.0f), rotate(vec3(0.0f, 0.0f, 8.75f), 67.5f, vec3(0.0f, 1.0f, 0.0f)), true);

	return true;
}

void CMyRayTracer::DestroyTextures()
{
	Floor.Destroy();
	Cube.Destroy();
	Earth.Destroy();
}

CMyRayTracer RayTracer;

// ----------------------------------------------------------------------------------------------------------------------------

CWnd::CWnd()
{
    char *moduledirectory = new char[256];
    GetModuleFileName(GetModuleHandle(NULL), moduledirectory, 256);
    *(strrchr(moduledirectory, '\\') + 1) = 0;
    ModuleDirectory = moduledirectory;
    delete [] moduledirectory;
}

CWnd::~CWnd()
{
}

bool CWnd::Create(HINSTANCE hInstance, char *WindowName, int Width, int Height)
{
	WNDCLASSEX WndClassEx;

	memset(&WndClassEx, 0, sizeof(WNDCLASSEX));

	WndClassEx.cbSize = sizeof(WNDCLASSEX);
	WndClassEx.style = CS_OWNDC | CS_HREDRAW | CS_VREDRAW;
	WndClassEx.lpfnWndProc = WndProc;
	WndClassEx.hInstance = hInstance;
	WndClassEx.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	WndClassEx.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	WndClassEx.hCursor = LoadCursor(NULL, IDC_ARROW);
	WndClassEx.lpszClassName = "Win32CPURayTracerWindow";

	if(RegisterClassEx(&WndClassEx) == 0)
	{
		ErrorLog.Set("RegisterClassEx failed!");
		return false;
	}

	this->WindowName = WindowName;

	this->Width = Width;
	this->Height = Height;

	DWORD Style = WS_OVERLAPPEDWINDOW | WS_CLIPSIBLINGS | WS_CLIPCHILDREN;

	if((hWnd = CreateWindowEx(WS_EX_APPWINDOW, WndClassEx.lpszClassName, WindowName, Style, 0, 0, Width, Height, NULL, NULL, hInstance, NULL)) == NULL)
	{
		ErrorLog.Set("CreateWindowEx failed!");
		return false;
	}

	if((hDC = GetDC(hWnd)) == NULL)
	{
		ErrorLog.Set("GetDC failed!");
		return false;
	}

	return RayTracer.Init();
}

void CWnd::RePaint()
{
	Line = 0;
	InvalidateRect(hWnd, NULL, FALSE);
}

void CWnd::Show(bool Maximized)
{
	RECT dRect, wRect, cRect;

	GetWindowRect(GetDesktopWindow(), &dRect);
	GetWindowRect(hWnd, &wRect);
	GetClientRect(hWnd, &cRect);

	wRect.right += Width - cRect.right;
	wRect.bottom += Height - cRect.bottom;

	wRect.right -= wRect.left;
	wRect.bottom -= wRect.top;

	wRect.left = dRect.right / 2 - wRect.right / 2;
	wRect.top = dRect.bottom / 2 - wRect.bottom / 2;

	MoveWindow(hWnd, wRect.left, wRect.top, wRect.right, wRect.bottom, FALSE);

	ShowWindow(hWnd, Maximized ? SW_SHOWMAXIMIZED : SW_SHOWNORMAL);
}

void CWnd::MsgLoop()
{
	MSG Msg;

	while(GetMessage(&Msg, NULL, 0, 0) > 0)
	{
		TranslateMessage(&Msg);
		DispatchMessage(&Msg);
	}
}

void CWnd::Destroy()
{
	RayTracer.Destroy();

	DestroyWindow(hWnd);
}

void CWnd::OnKeyDown(UINT Key)
{
	switch(Key)
	{
		case '1':
			if(RayTracer.SetSamples(1)) RePaint();
			break;

		case '2':
			if(RayTracer.SetSamples(2)) RePaint();
			break;

		case '3':
			if(RayTracer.SetSamples(3)) RePaint();
			break;

		case '4':
			if(RayTracer.SetSamples(4)) RePaint();
			break;

		case VK_F1:
			RayTracer.Textures = !RayTracer.Textures;
			RePaint();
			break;

		case VK_F2:
			RayTracer.SoftShadows = !RayTracer.SoftShadows;
			RePaint();
			break;

		case VK_F3:
			RayTracer.AmbientOcclusion = !RayTracer.AmbientOcclusion;
			RePaint();
			break;
	}

	if(Camera.OnKeyDown(Key))
	{
		RePaint();
	}
}

void CWnd::OnMouseMove(int cx, int cy)
{
	if(GetKeyState(VK_RBUTTON) & 0x80)
	{
		Camera.OnMouseMove(LastCurPos.x - cx, LastCurPos.y - cy);

		LastCurPos.x = cx;
		LastCurPos.y = cy;

		RePaint();
	}
}

void CWnd::OnMouseWheel(short zDelta)
{
	Camera.OnMouseWheel(zDelta);

	RePaint();
}

void CWnd::OnPaint()
{
	PAINTSTRUCT ps;

	BeginPaint(hWnd, &ps);

	static DWORD Start;
	static bool RayTracing;

	if(Line == 0)
	{
		RayTracer.ClearColorBuffer();

		// CQuad::Intersections = 0;
		// CSphere::Intersections = 0;

		Start = GetTickCount();

		RayTracing = true;
	}

	DWORD start = GetTickCount();

	while(Line < Height && GetTickCount() - start < 250)
	{
		RayTracer.RayTrace(Line++);
	}

	RayTracer.SwapBuffers(hDC);

	if(RayTracing)
	{
		if(Line == Height)
		{
			RayTracing = false;
			RayTracer.MapHDRColors();
		}

		DWORD End = GetTickCount();

		CString text = WindowName;

		text.Append(" - %dx%d", Width, Height);
		text.Append(", Supersampling %dx", RayTracer.GetSamples());
		text.Append(", Time: %.03f s", (float)(End - Start) * 0.001f);
		// text.Append(", %.02f / %.02f mil. (quad / sphere) intersection tests", (float)CQuad::Intersections * 0.000001f, (float)CSphere::Intersections * 0.000001f);

		SetWindowText(hWnd, text);

		InvalidateRect(hWnd, NULL, FALSE);
	}

	EndPaint(hWnd, &ps);
}

void CWnd::OnRButtonDown(int cx, int cy)
{
	LastCurPos.x = cx;
	LastCurPos.y = cy;
}

void CWnd::OnSize(int Width, int Height)
{
	this->Width = Width;
	this->Height = Height;

	RayTracer.Resize(Width, Height);

	RePaint();
}

CWnd Wnd;

// ----------------------------------------------------------------------------------------------------------------------------

LRESULT CALLBACK WndProc(HWND hWnd, UINT uiMsg, WPARAM wParam, LPARAM lParam)
{
	switch(uiMsg)
	{
		case WM_CLOSE:
			PostQuitMessage(0);
			break;

		case WM_MOUSEMOVE:
			Wnd.OnMouseMove(LOWORD(lParam), HIWORD(lParam));
			break;

		case 0x020A: // WM_MOUSWHEEL
			Wnd.OnMouseWheel(HIWORD(wParam));
			break;

		case WM_KEYDOWN:
			Wnd.OnKeyDown((UINT)wParam);
			break;

		case WM_PAINT:
			Wnd.OnPaint();
			break;

		case WM_RBUTTONDOWN:
			Wnd.OnRButtonDown(LOWORD(lParam), HIWORD(lParam));
			break;

		case WM_SIZE:
			Wnd.OnSize(LOWORD(lParam), HIWORD(lParam));
			break;

		default:
			return DefWindowProc(hWnd, uiMsg, wParam, lParam);
	}

	return 0;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR sCmdLine, int iShow)
{
	SetThreadPriority(GetCurrentThread(), THREAD_PRIORITY_HIGHEST);

	if(Wnd.Create(hInstance, "CPU ray tracer", 800, 600))
	{
		Wnd.Show();
		Wnd.MsgLoop();
	}
	else
	{
		MessageBox(NULL, ErrorLog, "Error", MB_OK | MB_ICONERROR);
	}

	Wnd.Destroy();

	return 0;
}
