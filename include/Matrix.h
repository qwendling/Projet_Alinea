#ifndef __MATRIX_H__
#define __MATRIX_H__

#include <stdio.h>
#include <stdlib.h>

typedef double E;

typedef struct{
	E *mat;
	int nrows,ncol;} *Matrix,std_matrix;

Matrix newMatrix(int nbrows, int nbcolumns);
E getElt(Matrix m, int row, int column);
void setElt(Matrix m, int row, int column, E val);
void deleteMatrix(Matrix m);
void displayMatrix(Matrix m);
Matrix Identite(int taille);
Matrix copyMatrix(const Matrix m);
Matrix aleatoire(int row, int col ,E min, E max);
E scalAleatoire(E min, E max);

#endif
