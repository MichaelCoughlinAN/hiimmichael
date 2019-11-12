#include "matrix.h"

Matrix::Matrix(){
  for (int i = 0; i<4; i++) {
    for (int j = 0; j < 4; j++) {
      if (i == j) mat[i][j] = 1;
      else mat[i][j] = 0;
    }
  }
}

void Matrix::zeroMat(){
  for (int i = 0; i<4; i++) {
    for (int j = 0; j < 4; j++) {
      mat[i][j] = 0;
    }
  }
}

void Matrix::identityMat(){
  for (int i = 0; i<4; i++) {
    for (int j = 0; j < 4; j++) {
      if (i == j) mat[i][j] = 1;
      else mat[i][j] = 0;
    }
  }
}

Matrix Matrix::operator+(const Matrix& right){
  Matrix res;
  for (int i = 0; i<4; i++) {
    for (int j = 0; j< 4; j++){
      res.mat[i][j] = mat[i][j] + right.mat[i][j];
    }
  }
  return res;
}

Matrix Matrix::operator-(const Matrix& right){
  Matrix res;
  for (int i = 0; i<4; i++) {
    for (int j = 0; j< 4; j++){
      res.mat[i][j] = mat[i][j] - right.mat[i][j];
    }
  }
  return res;
}

Matrix Matrix::operator*(const float& scalar){
  Matrix res;
  for (int i = 0; i<4; i++) {
    for (int j = 0; j< 4; j++){
      res.mat[i][j] = mat[i][j]*scalar;
    }
  }
  return res;
}

Matrix Matrix::mult(Matrix m){
  Matrix res;
  for (int i = 0; i<4; i++) {
    for (int j = 0; j< 4; j++){
      for (int k = 0; k<4; k++) {
        res.mat[i][j] += mat[i][k]*m.mat[k][j];
      }
    }
  }
  return res;
}

Matrix Matrix::transpose(){
  Matrix res;
  for (int i = 0; i<4; i++) {
    for (int j = 0; j< 4; j++){
      res.mat[i][j] = mat[j][i];
    }
  }
  return res;
}

float Matrix::det(){
  float detA = 0;
  detA += mat[0][0]*(mat[1][1]*mat[2][2]*mat[3][3] + mat[1][2]*mat[2][3]*mat[3][1]+ mat[1][3]*mat[2][1]*mat[3][2] -
                       mat[1][3]*mat[2][2]*mat[3][1] + mat[1][2]*mat[2][1]*mat[3][3]+ mat[1][1]*mat[2][3]*mat[3][2]);
  detA -= mat[0][1]*(mat[1][0]*mat[2][2]*mat[3][3] + mat[1][2]*mat[2][3]*mat[3][0]+ mat[1][3]*mat[2][0]*mat[3][2] -
                       mat[1][3]*mat[2][2]*mat[3][0] + mat[1][2]*mat[2][0]*mat[3][3]+ mat[1][0]*mat[2][3]*mat[3][2]);
  detA += mat[0][2]*(mat[1][0]*mat[2][1]*mat[3][3] + mat[1][1]*mat[2][3]*mat[3][0]+ mat[1][3]*mat[2][0]*mat[3][1] -
                       mat[1][3]*mat[2][1]*mat[3][0] + mat[1][1]*mat[2][0]*mat[3][3]+ mat[1][0]*mat[2][3]*mat[3][1]);
  detA -= mat[0][3]*(mat[1][0]*mat[2][1]*mat[3][2] + mat[1][1]*mat[2][2]*mat[3][0]+ mat[1][2]*mat[2][0]*mat[3][1] -
                       mat[1][2]*mat[2][1]*mat[3][0] + mat[1][1]*mat[2][0]*mat[3][2]+ mat[1][0]*mat[2][2]*mat[3][1]);
  return detA;
}

Matrix Matrix::inverse(){
  Matrix m;
  
  m.mat[0][0] = m.mat[1][2]*m.mat[2][3]*m.mat[3][1] - m.mat[1][3]*m.mat[2][2]*m.mat[3][1] + m.mat[1][3]*m.mat[2][1]*m.mat[3][2] - m.mat[1][1]*m.mat[2][3]*m.mat[3][2] - m.mat[1][2]*m.mat[2][1]*m.mat[3][3] + m.mat[1][1]*m.mat[2][2]*m.mat[3][3];
  m.mat[0][1] = m.mat[0][3]*m.mat[2][2]*m.mat[3][1] - m.mat[0][2]*m.mat[2][3]*m.mat[3][1] - m.mat[0][3]*m.mat[2][1]*m.mat[3][2] + m.mat[0][1]*m.mat[2][3]*m.mat[3][2] + m.mat[0][2]*m.mat[2][1]*m.mat[3][3] - m.mat[0][1]*m.mat[2][2]*m.mat[3][3];
  m.mat[0][2] = m.mat[0][2]*m.mat[1][3]*m.mat[3][1] - m.mat[0][3]*m.mat[1][2]*m.mat[3][1] + m.mat[0][3]*m.mat[1][1]*m.mat[3][2] - m.mat[0][1]*m.mat[1][3]*m.mat[3][2] - m.mat[0][2]*m.mat[1][1]*m.mat[3][3] + m.mat[0][1]*m.mat[1][2]*m.mat[3][3];
  m.mat[0][3] = m.mat[0][3]*m.mat[1][2]*m.mat[2][1] - m.mat[0][2]*m.mat[1][3]*m.mat[2][1] - m.mat[0][3]*m.mat[1][1]*m.mat[2][2] + m.mat[0][1]*m.mat[1][3]*m.mat[2][2] + m.mat[0][2]*m.mat[1][1]*m.mat[2][3] - m.mat[0][1]*m.mat[1][2]*m.mat[2][3];
  m.mat[1][0] = m.mat[1][3]*m.mat[2][2]*m.mat[3][0] - m.mat[1][2]*m.mat[2][3]*m.mat[3][0] - m.mat[1][3]*m.mat[2][0]*m.mat[3][2] + m.mat[1][0]*m.mat[2][3]*m.mat[3][2] + m.mat[1][2]*m.mat[2][0]*m.mat[3][3] - m.mat[1][0]*m.mat[2][2]*m.mat[3][3];
  m.mat[1][1] = m.mat[0][2]*m.mat[2][3]*m.mat[3][0] - m.mat[0][3]*m.mat[2][2]*m.mat[3][0] + m.mat[0][3]*m.mat[2][0]*m.mat[3][2] - m.mat[0][0]*m.mat[2][3]*m.mat[3][2] - m.mat[0][2]*m.mat[2][0]*m.mat[3][3] + m.mat[0][0]*m.mat[2][2]*m.mat[3][3];
  m.mat[1][2] = m.mat[0][3]*m.mat[1][2]*m.mat[3][0] - m.mat[0][2]*m.mat[1][3]*m.mat[3][0] - m.mat[0][3]*m.mat[1][0]*m.mat[3][2] + m.mat[0][0]*m.mat[1][3]*m.mat[3][2] + m.mat[0][2]*m.mat[1][0]*m.mat[3][3] - m.mat[0][0]*m.mat[1][2]*m.mat[3][3];
  m.mat[1][3] = m.mat[0][2]*m.mat[1][3]*m.mat[2][0] - m.mat[0][3]*m.mat[1][2]*m.mat[2][0] + m.mat[0][3]*m.mat[1][0]*m.mat[2][2] - m.mat[0][0]*m.mat[1][3]*m.mat[2][2] - m.mat[0][2]*m.mat[1][0]*m.mat[2][3] + m.mat[0][0]*m.mat[1][2]*m.mat[2][3];
  m.mat[2][0] = m.mat[1][1]*m.mat[2][3]*m.mat[3][0] - m.mat[1][3]*m.mat[2][1]*m.mat[3][0] + m.mat[1][3]*m.mat[2][0]*m.mat[3][1] - m.mat[1][0]*m.mat[2][3]*m.mat[3][1] - m.mat[1][1]*m.mat[2][0]*m.mat[3][3] + m.mat[1][0]*m.mat[2][1]*m.mat[3][3];
  m.mat[2][1] = m.mat[0][3]*m.mat[2][1]*m.mat[3][0] - m.mat[0][1]*m.mat[2][3]*m.mat[3][0] - m.mat[0][3]*m.mat[2][0]*m.mat[3][1] + m.mat[0][0]*m.mat[2][3]*m.mat[3][1] + m.mat[0][1]*m.mat[2][0]*m.mat[3][3] - m.mat[0][0]*m.mat[2][1]*m.mat[3][3];
  m.mat[2][2] = m.mat[0][1]*m.mat[1][3]*m.mat[3][0] - m.mat[0][3]*m.mat[1][1]*m.mat[3][0] + m.mat[0][3]*m.mat[1][0]*m.mat[3][1] - m.mat[0][0]*m.mat[1][3]*m.mat[3][1] - m.mat[0][1]*m.mat[1][0]*m.mat[3][3] + m.mat[0][0]*m.mat[1][1]*m.mat[3][3];
  m.mat[2][3] = m.mat[0][3]*m.mat[1][1]*m.mat[2][0] - m.mat[0][1]*m.mat[1][3]*m.mat[2][0] - m.mat[0][3]*m.mat[1][0]*m.mat[2][1] + m.mat[0][0]*m.mat[1][3]*m.mat[2][1] + m.mat[0][1]*m.mat[1][0]*m.mat[2][3] - m.mat[0][0]*m.mat[1][1]*m.mat[2][3];
  m.mat[3][0] = m.mat[1][2]*m.mat[2][1]*m.mat[3][0] - m.mat[1][1]*m.mat[2][2]*m.mat[3][0] - m.mat[1][2]*m.mat[2][0]*m.mat[3][1] + m.mat[1][0]*m.mat[2][2]*m.mat[3][1] + m.mat[1][1]*m.mat[2][0]*m.mat[3][2] - m.mat[1][0]*m.mat[2][1]*m.mat[3][2];
  m.mat[3][1] = m.mat[0][1]*m.mat[2][2]*m.mat[3][0] - m.mat[0][2]*m.mat[2][1]*m.mat[3][0] + m.mat[0][2]*m.mat[2][0]*m.mat[3][1] - m.mat[0][0]*m.mat[2][2]*m.mat[3][1] - m.mat[0][1]*m.mat[2][0]*m.mat[3][2] + m.mat[0][0]*m.mat[2][1]*m.mat[3][2];
  m.mat[3][2] = m.mat[0][2]*m.mat[1][1]*m.mat[3][0] - m.mat[0][1]*m.mat[1][2]*m.mat[3][0] - m.mat[0][2]*m.mat[1][0]*m.mat[3][1] + m.mat[0][0]*m.mat[1][2]*m.mat[3][1] + m.mat[0][1]*m.mat[1][0]*m.mat[3][2] - m.mat[0][0]*m.mat[1][1]*m.mat[3][2];
  m.mat[3][3] = m.mat[0][1]*m.mat[1][2]*m.mat[2][0] - m.mat[0][2]*m.mat[1][1]*m.mat[2][0] + m.mat[0][2]*m.mat[1][0]*m.mat[2][1] - m.mat[0][0]*m.mat[1][2]*m.mat[2][1] - m.mat[0][1]*m.mat[1][0]*m.mat[2][2] + m.mat[0][0]*m.mat[1][1]*m.mat[2][2];
  
  for (int i = 0; i<4; i++) {
    for (int j = 0; j< 4; j++){
      m.mat[i][j] *= (1.0/m.det());
    }
  }
  
  return m;
}

Vec Matrix::matVec_mult(Vec pt){
  float rx = mat[0][0]*pt.x + mat[0][1]*pt.y + mat[0][2]*pt.z + mat[0][3];
  float ry = mat[1][0]*pt.x + mat[1][1]*pt.y + mat[1][2]*pt.z + mat[1][3];
  float rz = mat[2][0]*pt.x + mat[2][1]*pt.y + mat[2][2]*pt.z + mat[2][3];
  Vec res(rx, ry, rz);
  return res;
}

// transformation of direction vector (i.e., no translation)
Vec Matrix::matDir_mult(Vec dir){
  float rx = mat[0][0]*dir.x + mat[0][1]*dir.y + mat[0][2]*dir.z;
  float ry = mat[1][0]*dir.x + mat[1][1]*dir.y + mat[1][2]*dir.z;
  float rz = mat[2][0]*dir.x + mat[2][1]*dir.y + mat[2][2]*dir.z;
  Vec res(rx, ry, rz);
  return res;
}

void Matrix::translate(Vec pos){
  identityMat();
  mat[0][3] = pos.x;
  mat[1][3] = pos.y;
  mat[2][3] = pos.z;
}

void Matrix::scale(Vec scal){
  identityMat();
  mat[0][0]*=scal.x;
  mat[1][1]*=scal.y;
  mat[2][2]*=scal.z;
}

void Matrix::print(){
  for (int i = 0; i< 4; i++) {
    printf("| ");
    for (int j = 0; j < 4; j++) {
      printf("%f ", mat[i][j]);
    }
    printf("|\n");
  }
}