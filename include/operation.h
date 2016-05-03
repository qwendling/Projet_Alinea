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
int determinant(const Matrix m);
Matrix inverse(const Matrix m);
int rank(const Matrix m);

#endif
