#ifndef __OPERATION_H__
#define __OPERATION_H__

#include <stdio.h>
#include <stdlib.h>
#include "Matrix.h"

Matrix addition(const Matrix m,const Matrix n);
Matrix soustraction(const Matrix m,const Matrix n);
Matrix mult(const Matrix m,const Matrix n);
Matrix multScalaire(const Matrix m,E x);
Matrix transpose(const Matrix m);
Matrix expo(const Matrix m,int exposant);
Matrix triangle(const Matrix m);
E determinant(const Matrix m);
Matrix inverse(const Matrix m);
int rank(const Matrix m);
Matrix solve_gauss_simple(const Matrix A,const Matrix B);
typedef struct scouple{
	E valp;
	Matrix vectp;
	} *couple;

Matrix * decompositionLU(const Matrix m);
E maxComposante(Matrix m);
int approxMat(Matrix m1, Matrix m2, E precision);
couple approximation_vp(const Matrix a, E precision);
couple * liste_vp(const Matrix a, E precision);
E abso(E val);

#endif
