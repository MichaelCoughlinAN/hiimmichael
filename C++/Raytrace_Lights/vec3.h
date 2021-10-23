#ifndef VEC3_H
#define VEC3_H

class Vec3 {

public:
	double x,y,z;

	Vec3();
	Vec3(double);
	Vec3(double,double,double);


	Vec3 operator * (const double&) const;
	Vec3 operator * (const Vec3&) const;
	Vec3 operator - (const Vec3&) const;
	Vec3 operator + (const Vec3&) const;
	Vec3& operator -= (const Vec3&);
	Vec3& operator += (const Vec3&);
	Vec3& operator = (const Vec3&);
	bool operator == (const Vec3&)const;

	double length() const;
	double length2() const;
	double dot(const Vec3&) const;

	Vec3 cross(const Vec3&) const;
	Vec3& normalize();
	Vec3 project(const Vec3&) const;
	void print() const;
};


#endif