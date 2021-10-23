#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
#include <vector>
#include "vec3.h"
using namespace std;

enum Affine {ROTATEX,ROTATEY,ROTATEZ,SCALE,TRANSLATE,SHEAR};

class Matrix {
public:
	vector<vector<double> > mat;
	Matrix();
	Matrix(const Matrix& t);
	Matrix(Matrix& t);
	Matrix(Affine type, Vec3 v, Vec3 extra);
	Matrix(Affine type, double angle);
	Matrix(Affine type, Vec3 v);
	Matrix(double* V);

	void swapRows(int i, int j);
	void divideRow(int i, double temp);
	int getRow(int i);
	Vec3 transform(Vec3 point, int w);
	void subRow(int i, int j, double temp);
	Matrix operator * (const Matrix& v) const;
	void print();
	Matrix transpose();
	Matrix inverse();
};

#endif