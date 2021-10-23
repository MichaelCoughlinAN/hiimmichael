#include <iostream>
#include <vector>
#include <cmath>
#include "object.h"
using namespace std;


// Object
/*********************************************************************************************************************/

Object::Object(Vec3 surfaceColor, double transparency, Type objectType, Vec3 phongCoeffs){
	this->surfaceColor = surfaceColor;
	this->transparency = transparency;
	this->objectType = objectType;
	this->phongCoeffs = phongCoeffs;
}

/*********************************************************************************************************************/
// Sphere Object
/*********************************************************************************************************************/
Sphere::Sphere(Vec3 center, double radius, Vec3 surfaceColor, double transparency, Type objectType, Matrix mat, Vec3 phongCoeffs)
	:Object(surfaceColor, transparency, objectType, phongCoeffs) {
	this->transformMatrix = Matrix(mat);
	this->inverseMatrix = (this->transformMatrix).inverse();
	this->transposeMatrix = (this->inverseMatrix).transpose();
	this->center = center;
	this->radius = radius;
}

/*
	Sphere intersection
		- solving equation for a point on ray which is at distance r from center
*/
double Sphere::intersectionPoints(const Vec3 &ro, const Vec3 &rd) {
	/*Transformation done to ray origin and ray direction for world  -> object coordinates*/
	Vec3 rayOrigin = ro;
	Vec3 rayDirection = rd;
	rayOrigin = inverseMatrix.transform(ro, 1);
	rayDirection = inverseMatrix.transform(rd, 0);
	double Ird = rayDirection.length();
	rayDirection.normalize();

	vector<double> points;
	double a, b, c;
	a = rayDirection.length2();
	b = 2 * rayDirection.dot(rayOrigin - center);
	c = (rayOrigin - center).length2() - radius*radius;
	double discriminant = b*b - 4*a*c;
	if (discriminant < 0) return -1;
	else {
		discriminant = sqrt(discriminant);
		double t1 = ((-1 * b) + discriminant) / (2 * a);
		double t2 = ((-1 * b) - discriminant) / (2 * a);
		points.push_back(t1);
		points.push_back(t2);
	}
	double minT = INFINITY;
	bool flag = false;
	for(int i=0;i<points.size();i++){
		if(points[i]>=0 && minT > points[i]) {
			minT = points[i];
			flag = true;
		}
	}

	if (flag)
		return minT/Ird;
	else
		return -1;
}
Vec3 Sphere::getNormal(const Vec3 point){
	/*for normal first convert p to object space than find normal and then normal converted to world space and normalized*/
	Vec3 p = inverseMatrix.transform(point, 1);
	return transposeMatrix.transform((p - center).normalize(), 0).normalize();
}
/*********************************************************************************************************************/

// Cylinder Object
/*********************************************************************************************************************/
Cylinder::Cylinder(Vec3 center, Vec3 upVector, double radius, double height, Vec3 surfaceColor, double transparency, Type objectType, Matrix mat, Vec3 phongCoeffs)
	:Object(surfaceColor, transparency, objectType, phongCoeffs) {
	this->transformMatrix = Matrix(mat);
	this->inverseMatrix = (this->transformMatrix).inverse();
	this->transposeMatrix = (this->inverseMatrix).transpose();
	this->center = center;
	this->upVector = upVector.normalize();
	this->radius = radius;
	this->height = height;
}

// source : http://mrl.nyu.edu/~dzorin/rend05/lecture2.pdf
/*
	Cylinder Intersection 
		- First solving a point on ray at distance r from a infinite line which is axis of cylinder
		- then cut cylinder through two planes and check if the interscetion is still there
		- if not then check if intersection on plane is within range of cylinder
*/
double Cylinder::intersectionPoints(const Vec3 &ro, const Vec3 &rd) {
	Vec3 rayOrigin = ro;
	Vec3 rayDirection = rd;
	rayOrigin = inverseMatrix.transform(ro, 1);
	rayDirection = inverseMatrix.transform(rd, 0);
	double Ird = rayDirection.length();
	rayDirection.normalize();

	vector<double> points;
	Vec3 alpha = upVector * rayDirection.dot(upVector);
	Vec3 deltaP = (rayOrigin - center);
	Vec3 beta = upVector * deltaP.dot(upVector);
	Vec3 center2 = center + upVector*height;

	double a = (rayDirection - alpha).length2();
	double b = 2 * ((rayDirection - alpha).dot(deltaP - beta));
	double c = (deltaP - beta).length2() - radius*radius;

	double discriminant = b*b - 4*a*c;
	if (discriminant < 0) return -1;
	else {
		discriminant = sqrt(discriminant);
		double t1 = ((-1 * b) + discriminant) / (2 * a);
		double t2 = ((-1 * b) - discriminant) / (2 * a);
		if(t1>=0){
			if(upVector.dot((rayOrigin - center) + rayDirection * t1)>0 && upVector.dot((rayOrigin - center2) + rayDirection * t1)<0)
				points.push_back(t1);
		}
		if(t2>=0)
			if(upVector.dot((rayOrigin - center) + rayDirection * t2)>0 && upVector.dot((rayOrigin - center2) + rayDirection * t2)<0)
				points.push_back(t2);
	}

	float denom = rayDirection.dot(upVector);
	if (denom > 1e-6) {
		Vec3 co = center - rayOrigin;
		double t3 = co.dot(upVector) / denom;
		if(t3 > 0 && (rayDirection * t3 - co).length2() <= radius*radius)
			points.push_back(t3);
	} else if (denom < 1e-6) {
		Vec3 co2 = center2 - rayOrigin;
		double t4 = co2.dot(upVector) / denom;
		if(t4 > 0 && (rayDirection * t4 - co2).length2() <= radius*radius)
			points.push_back(t4);
	}

	double minT = INFINITY;
	bool flag = false;
	for(int i=0;i<points.size();i++){
		if(minT > points[i] && points[i]>=0) {
			minT = points[i];
			flag = true;
		}
	}
	if(flag)
		return minT/Ird;
	else
		return -1;
}
Vec3 Cylinder::getNormal(const Vec3 p){
	Vec3 point = inverseMatrix.transform(p, 1);
	Vec3 co = point - center;
	Vec3 co2 = co - upVector*height;
	if(co.length2() <= radius * radius)
		return transposeMatrix.transform(upVector, 0).normalize();
	if(co2.length2() <= radius * radius)
		return transposeMatrix.transform(upVector, 0).normalize();
	Vec3 normal = co - co.project(upVector);
	return transposeMatrix.transform(normal, 0).normalize();
}
/*********************************************************************************************************************/

// Cone Object
/*********************************************************************************************************************/
Cone::Cone(Vec3 center, Vec3 upVector, double alpha, double height, Vec3 surfaceColor, double transparency, Type objectType, Matrix mat, Vec3 phongCoeffs)
	:Object(surfaceColor, transparency, objectType, phongCoeffs) {
	this->transformMatrix = Matrix(mat);
	this->inverseMatrix = (this->transformMatrix).inverse();
	this->transposeMatrix = (this->inverseMatrix).transpose();
	this->center = center;
	this->upVector = upVector.normalize();
	this->alpha = alpha;
	this->radius = height * tan(alpha);
	this->height = height;
}
// source : http://mrl.nyu.edu/~dzorin/rend05/lecture2.pdf

/*
	Cone Intersection 
		- First solving a point on ray at for an infinite cone with apex at center2
		- then cut cone through two planes and check if the interscetion is still there
		- if not then check if intersection on plane is within range of cone
*/
double Cone::intersectionPoints(const Vec3 &ro, const Vec3 &rd) {
	Vec3 rayOrigin = ro;
	Vec3 rayDirection = rd;
	rayOrigin = inverseMatrix.transform(ro, 1);
	rayDirection = inverseMatrix.transform(rd, 0);
	double Ird = rayDirection.length();
	rayDirection.normalize();

	vector<double> points;
	double cos2a = cos(alpha)*cos(alpha);
	double sin2a = 1 - cos2a;
	Vec3 pa = center + upVector * height;
	Vec3 va = upVector * -1;
	Vec3 deltaP = (rayOrigin - pa);

	double c1 = rayDirection.dot(va);
	Vec3 c2 = va * c1;
	double c3 = deltaP.dot(va);
	Vec3 c4 = va * c3;

	double a = cos2a * (rayDirection - c2).length2() - sin2a * c1 * c1;
	double b = 2* cos2a * (rayDirection - c2).dot(deltaP - c4) - 2 * sin2a * (c1 * c3);
	double c = cos2a * (deltaP - c4).length2() - sin2a * (c3 * c3);


	double discriminant = b*b - 4*a*c;
	if (discriminant < 0) return -1;
	else {
		discriminant = sqrt(discriminant);
		double t1 = ((-1 * b) + discriminant) / (2 * a);
		double t2 = ((-1 * b) - discriminant) / (2 * a);
		if(t1>=0){
			if(upVector.dot((rayOrigin - center) + rayDirection * t1)>0 && upVector.dot((rayOrigin - pa) + rayDirection * t1)<0)
				points.push_back(t1);
		}
		if(t2>=0)
			if(upVector.dot((rayOrigin - center) + rayDirection * t2)>0 && upVector.dot((rayOrigin - pa) + rayDirection * t2)<0)
				points.push_back(t2);
	}

	float denom = rayDirection.dot(upVector);
	if (denom > 1e-6) {
		Vec3 co = center - rayOrigin;
		double t3 = co.dot(upVector) / denom;
		if(t3 > 0 && (rayDirection * t3 - co).length2() <= radius*radius)
			points.push_back(t3);
	}

	double minT = INFINITY;
	bool flag = false;
	for(int i=0;i<points.size();i++){
		if(minT > points[i] && points[i]>=0) {
			minT = points[i];
			flag = true;
		}
	}
	if(flag)
		return minT/Ird;
	else
		return -1;
}
Vec3 Cone::getNormal(const Vec3 p){
	Vec3 point = inverseMatrix.transform(p, 1);
	if(abs((point - center).dot(upVector)) < 1e-4){
		return transformMatrix.transform(upVector * -1, 0).normalize();
	}
	Vec3 top = center + upVector * height;
	Vec3 perp = (upVector * -1).cross(point - top);
	return transposeMatrix.transform(((point - top).cross(perp)).normalize(), 0).normalize();
}
/*********************************************************************************************************************/

// Triangle Object
/*********************************************************************************************************************/
Triangle::Triangle(Vec3 p1, Vec3 p2, Vec3 p3, Vec3 surfaceColor, double transparency, Type objectType, Matrix mat, Vec3 phongCoeffs)
	:Object(surfaceColor, transparency, objectType, phongCoeffs) {
	this->transformMatrix = Matrix(mat);
	this->inverseMatrix = (this->transformMatrix).inverse();
	this->transposeMatrix = (this->inverseMatrix).transpose();
	this->p1 = p1;
	this->p2 = p2;
	this->p3 = p3;
}


// Source : http://www.lighthouse3d.com/tutorials/maths/ray-triangle-intersection/
/*Triangle intersection*/
double Triangle::intersectionPoints(const Vec3 &ro, const Vec3 &rd) {
	Vec3 rayOrigin = ro;
	Vec3 rayDirection = rd;
	rayOrigin = inverseMatrix.transform(ro, 1);
	rayDirection = inverseMatrix.transform(rd, 0);
	double Ird = rayDirection.length();
	rayDirection.normalize();

	vector<double> points;
	Vec3 e1,e2,h,s,q;
	double a,f,u,v,t;

	e1 = p2 - p1;
	e2 = p3 - p1;
	h = rayDirection.cross(e2);
	a = e1.dot(h);

	if (a > -0.00001 && a < 0.00001)
		return(-1);

	f = 1/a;
	s = rayOrigin - p1;
	u = f * (s.dot(h));

	if (u < 0.0 || u > 1.0)
		return(-1);

	q = s.cross(e1);
	v = f * rayDirection.dot(q);

	if (v < 0.0 || u + v > 1.0)
		return(-1);


	t = f * e2.dot(q);

	if (t > 0.00001) {
		return(t/Ird);
	}
	else
		return (-1);
}
Vec3 Triangle::getNormal(const Vec3 point){
	return transposeMatrix.transform((p2 -p1).cross(p3 - p1).normalize(), 0).normalize();
}
/*********************************************************************************************************************/