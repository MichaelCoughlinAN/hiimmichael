#ifndef OBJECT_H
#define OBJECT_H

#include <vector>
#include "vec3.h"
#include "matrix.h"
using namespace std;

enum Type {SPECULAR, DIFFUSED}; 

class Object {

public:

	Vec3 surfaceColor;
	double transparency;
	Type objectType;
	Vec3 phongCoeffs;
	Matrix transformMatrix;
	Matrix inverseMatrix;
	Matrix transposeMatrix;

	Object(Vec3 surfaceColor, double transparency, Type objectType, Vec3 phongCoeffs);
	virtual double intersectionPoints(const Vec3 &rayOrigin, const Vec3 &rayDirection) = 0;
	virtual Vec3 getNormal(const Vec3 point) = 0;
};

class Sphere : public Object {

public:

	Vec3 center;
	double radius;

	Sphere(Vec3 center, double radius, Vec3 surfaceColor, double transparency, Type objectType, Matrix mat, Vec3 phongCoeffs);
	double intersectionPoints(const Vec3 &rayOrigin, const Vec3 &rayDirection);
	Vec3 getNormal(const Vec3 point);
};

class Cylinder : public Object {

public:
	Vec3 center;
	double radius, height;
	Vec3 upVector;

	Cylinder(Vec3 center, Vec3 upVector, double radius, double height, Vec3 surfaceColor, double transparency, Type objectType, Matrix mat, Vec3 phongCoeffs);
	double intersectionPoints(const Vec3 &rayOrigin, const Vec3 &rayDirection);
	Vec3 getNormal(const Vec3 point);
};

class Cone : public Object {

public:

	double radius, height, alpha;
	Vec3 upVector;
	Vec3 center;

	Cone(Vec3 center, Vec3 upVector, double alpha, double height, Vec3 surfaceColor, double transparency, Type objectType, Matrix mat, Vec3 phongCoeffs);
	double intersectionPoints(const Vec3 &rayOrigin, const Vec3 &rayDirection);
	Vec3 getNormal(const Vec3 point);
};

class Triangle : public Object {

public:

	Vec3 p1, p2, p3;

	Triangle(Vec3 p1, Vec3 p2, Vec3 p3, Vec3 surfaceColor, double transparency, Type objectType, Matrix mat, Vec3 phongCoeffs);
	double intersectionPoints(const Vec3 &rayOrigin, const Vec3 &rayDirection);
	Vec3 getNormal(const Vec3 point);
};

#endif