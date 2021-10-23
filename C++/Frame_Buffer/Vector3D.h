#ifndef VECTOR3DH
#define VECTOR3DH

// File Vector3D.h for CS 5721 Homework Assignment 1
// Requires no corresponding Vector3D.cpp file
// Doug Dunham
// Sept. 13, 2008

#include <math.h>
#include <iostream>

class Vector3D
{
public:
	Vector3D() { v[0] = 0.0; v[1] = 0.0; v[2] = 0.0; }
	Vector3D(double x, double y, double z) { v[0] = x; v[1] = y; v[2] = z; }
	virtual ~Vector3D() {}

	inline double x() const { return v[0]; }
	inline double y() const { return v[1]; }
	inline double z() const { return v[2]; }
	inline void set(const double& x, const double& y, const double& z)
                       { v[0] = x; v[1] = y; v[2] = z; }

	inline float* vecfData()
	{
		float* tmp = new float[2];

		tmp[0] = (float) v[0];
		tmp[1] = (float) v[1];
		tmp[2] = (float) v[2];

		return tmp;
	}

	inline void normalize()
	{
		double length = this->length();

		if (length > 0)
		{
			v[0] = v[0] / length;
			v[1] = v[1] / length;
			v[2] = v[2] / length;
		}
	}

	inline const double length() {
		return sqrt( (v[0] * v[0]) + (v[1] * v[1]) + (v[2] * v[2]) );
	}

	inline const double dot(const Vector3D& rhs) {
		return ( v[0] * rhs.x() + v[1] * rhs.y() + v[2] * rhs.z() );
	}

	inline const Vector3D cross(const Vector3D& rhs) {
		return Vector3D( v[1]*rhs.z() - v[2]*rhs.y(), v[2]*rhs.x() - v[0]*rhs.z(), v[0]*rhs.y() - v[1]*rhs.x() );
	}

	inline const friend Vector3D operator+(const Vector3D& lhs, const Vector3D& rhs) {
		return Vector3D( lhs.x() + rhs.x(), lhs.y() + rhs.y(), lhs.z() + rhs.z() );
	}

	inline const friend Vector3D operator-(const Vector3D& lhs, const Vector3D& rhs) {
		return Vector3D( lhs.x() - rhs.x(), lhs.y() - rhs.y(), lhs.z() - rhs.z() );
	}

	inline const friend Vector3D operator*(const double& lhs, const Vector3D& rhs) {
		return Vector3D( lhs * rhs.x(), lhs * rhs.y(), lhs * rhs.z() );
	}

	inline const friend Vector3D operator*(const Vector3D& lhs, const double& rhs) {
		return Vector3D( rhs * lhs.x(), rhs * lhs.y(), rhs * lhs.z() );
	}

	inline friend ostream& operator<<(ostream &out, const Vector3D& vec) {
		out << "[" << vec.x() << ", " << vec.y() << ", " << vec.z() << "]";
		return out;
	}

/*
	inline const double operator[](const int& i) {
		return (i > 0 && i <= 2) ? v[i] : NULL;
	}
*/

	inline const bool operator==(const Vector3D& rhs) {
		return ( v[0] == rhs.x() && v[1] == rhs.y() && v[2] == rhs.z() ) ? 1 : 0;
	}

	inline const bool operator!=(const Vector3D& rhs) {
		return ( v[0] != rhs.x() || v[1] != rhs.y() || v[2] != rhs.z() ) ? 1 : 0;
	}

private:
	double v[3];
};

#endif
