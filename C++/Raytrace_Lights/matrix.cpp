#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include "matrix.h"
using namespace std;

Matrix::Matrix() {
	mat.assign(4,vector<double>(4,0));
	for (int i=0;i<4;i++) mat[i][i] = 1;
}

Matrix::Matrix(Matrix& t) {
	mat.assign(4,vector<double>(4,0));
	for (int i=0;i<4;i++) mat[i][i] = 1;
	for (int i=0;i<4;i++) {
		for (int j=0;j<4;j++) 
			mat[i][j] = t.mat[i][j];
	}
}
Matrix::Matrix(const Matrix& t) {
	mat.assign(4,vector<double>(4,0));
	for (int i=0;i<4;i++) mat[i][i] = 1;
	for (int i=0;i<4;i++) {
		for (int j=0;j<4;j++) 
			mat[i][j] = t.mat[i][j];
	}
}

Matrix::Matrix(Affine type, double angle) {
	mat.assign(4,vector<double>(4,0));
	for (int i=0;i<4;i++) mat[i][i] = 1;
	switch(type) {
		case ROTATEX:
			mat[1][1] = cos(angle);
			mat[2][2] = mat[1][1];
			mat[1][2] = -1 * sin(angle);
			mat[2][1] = -1 * mat[1][2];
			break;
		case ROTATEY:
			mat[0][0] = cos(angle);
			mat[2][2] = mat[0][0];
			mat[0][2] = sin(angle);
			mat[2][0] = -1 * mat[0][2];
			break;
		case ROTATEZ:
			mat[0][0] = cos(angle);
			mat[1][1] = mat[0][0];
			mat[0][1] = -1 * sin(angle);
			mat[1][0] = -1 * mat[0][1];
			break;
		default:
			break;
	}
}


Matrix::Matrix(Affine type, Vec3 v, Vec3 extra) {
	mat.assign(4,vector<double>(4,0));
	for (int i=0;i<4;i++) mat[i][i] = 1;
	switch(type) {
		case SHEAR:
			mat[1][0] = v.x;
			mat[2][0] = v.y;
			mat[0][1] = v.z;
			mat[2][1] = extra.x;
			mat[0][2] = extra.y;
			mat[1][2] = extra.z;
			break;
		default:
			break;
	}
}

Matrix::Matrix(Affine type, Vec3 v) {
	mat.assign(4,vector<double>(4,0));
	for (int i=0;i<4;i++) mat[i][i] = 1;
	switch(type) {
		case SCALE:
			mat[0][0] = v.x;
			mat[1][1] = v.y;
			mat[2][2] = v.z;
			mat[3][3] = 1;
			break;
		case TRANSLATE:
			mat[0][3] = v.x;
			mat[1][3] = v.y;
			mat[2][3] = v.z;
			mat[3][3] = 1;
			break;
		default:
			break;
	}
}

Matrix Matrix::operator * (const Matrix& v) const {
	Matrix temp;
	for (int i=0;i<4;i++) {
		for (int j=0;j<4;j++) {
			if (i==j) temp.mat[i][j]--;
			for (int k=0;k<4;k++) {
				temp.mat[i][j] += mat[i][k]*v.mat[k][j];
			}
		}
	}
	return temp;
}
Matrix::Matrix(double V[16]){
	mat.assign(4,vector<double>(4,0));
	for(int i=0; i<16; i++){
		mat[i/4][i%4] =  V[i];
	}
}

Matrix Matrix::transpose() {
	Matrix temp;
	for (int i=0;i<4;i++) {
		for (int j=0;j<4;j++) {
			temp.mat[i][j] = mat[j][i];
		}
	}
	return temp;
}

void Matrix::swapRows(int i, int j) {
	for (int k=0;k<4;k++) 
		swap(mat[i][k],mat[j][k]);
}

void Matrix::divideRow(int i, double temp) {
	for (int j=0;j<4;j++) 
		mat[i][j]/=temp;
}

void Matrix::subRow(int i, int j, double temp) {
	for (int k=0;k<4;k++) 
		mat[i][k] -= mat[j][k]*temp;
}

int Matrix::getRow(int i) {
	for (int j=i;j<4;j++) {
		if (mat[j][i]!=0)
			return j;
	}
}

void Matrix::print() {
	for (int i=0;i<4;i++) {
		for (int j=0;j<4;j++) {
			cout<<mat[i][j]<<" ";
		}
		cout<<endl;
	}
}

Vec3 Matrix::transform(Vec3 point, int w) {
	Vec3 temp;
	temp.x = point.dot(Vec3(mat[0][0],mat[0][1],mat[0][2])) + mat[0][3]*w;
	temp.y = point.dot(Vec3(mat[1][0],mat[1][1],mat[1][2])) + mat[1][3]*w;
	temp.z = point.dot(Vec3(mat[2][0],mat[2][1],mat[2][2])) + mat[2][3]*w;
	return temp;
}

Matrix Matrix::inverse() {
	Matrix temp(*this), identity;
	for (int i=0;i<4;i++) {
		int j = temp.getRow(i);
		if (j!=i) {
			temp.swapRows(i,j);
			identity.swapRows(i,j);
		}
		double t = temp.mat[i][i];
		temp.divideRow(i,t);
		identity.divideRow(i,t);
		for (j=0;j<4;j++) {
			if (j!=i) {
				t = temp.mat[j][i];
				temp.subRow(j,i,t);
				identity.subRow(j,i,t);
			}
		}
	}
	return identity;
}

