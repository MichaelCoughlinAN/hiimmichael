#ifndef VECTOR2DH
#define VECTOR2DH

#include <math.h>
#include <iostream>

class Vector2D {
private:
	double v[2];
public:
	Vector2D() { v[0] = 0.0; v[1] = 0.0; }
	Vector2D(double x, double y) { v[0] = x; v[1] = y; }
	Vector2D() {}

	inline double x() const { return v[0]; }
	inline double y() const { return v[1]; }
	inline void set(const double& x, const double& y) 
                       { v[0] = x; v[1] = y; }

	inline float* vecfData() {
		float* vecf = new float[2];
		vecf[0] = (float) v[0];
		vecf[1] = (float) v[1];
		return vecf;
	}

	inline void normalize() {
		double length = this->length();

		if (length > 0) {
			v[0] = v[0] / length;
			v[1] = v[1] / length;
		}
	}

	inline const double length() {
		return sqrt( (v[0] * v[0]) + (v[1] * v[1]) );
	}

	inline const double dot(const Vector2D& rhs) {
		return ( v[0] * rhs.x() + v[1] * rhs.y() );
	}

	inline const double cross(const Vector2D& rhs) {
		return ( v[0] * rhs.y() - rhs.x() * v[1] );
	}

	inline const friend Vector2D operator+(const Vector2D& lhs,
                                               const Vector2D& rhs) {
		return Vector2D( lhs.x() + rhs.x(), lhs.y() + rhs.y() );
	}

	inline const friend Vector2D operator-(const Vector2D& lhs,
                                               const Vector2D& rhs) {
		return Vector2D( lhs.x() - rhs.x(), lhs.y() - rhs.y() );
	}


	inline const friend Vector2D operator*(const double& lhs,
                                               const Vector2D& rhs) {
		return Vector2D( lhs * rhs.x(), lhs * rhs.y() );
	}


	inline const friend Vector2D operator/(const Vector2D& lhs, 
                                               const double& rhs) {
		return Vector2D( lhs.x() / rhs, lhs.y() / rhs );
	}


	inline friend ostream& operator<<(ostream &out, const Vector2D& vec) {
		out << "[" << vec.x() << ", " << vec.y() << "]";
		return out;
	}

	inline const double operator[](const int& i) {
		return (i >= 0 && i <= 1) ? v[i] : 0;
	}
/*
*/

	inline const bool operator==(const Vector2D& rhs) {
		return ( v[0] == rhs.x() && v[1] == rhs.y() ) ? 1 : 0;
	}

	inline const bool operator!=(const Vector2D& rhs) {
		return ( v[0] != rhs.x() || v[1] != rhs.y() ) ? 1 : 0;
	}

};

#endif
