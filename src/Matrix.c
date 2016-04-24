#include "Matrix.h"

Matrix newMatrix(int nbrows, int nbcolumns){
	Matrix new=malloc(sizeof(std_matrix));
	new->mat=calloc(nbrows*nbcolumns,sizeof(E));
	new->nrows=nbrows;
	new->ncol=nbcolumns;
	return new;
}

E getElt(Matrix m, int row, int column){
	return m->mat[(row*m->ncol)+column];
}

void setElt(Matrix m, int row, int column, E val){
	m->mat[(row*m->ncol)+column]=val;
}

void deleteMatrix(Matrix m){
	free(m->mat);
	free(m);
}

void displayMatrix(Matrix m){
	int i,j;
	for(i=0;i<m->nrows;i++){
		printf("|");
		for(j=0;j<m->ncol;j++)
			printf("%f ",getElt(m,i,j));
		printf("|\n");
	}
}

Matrix Identite(int taille){
	int i,j;
	Matrix m=newMatrix(taille,taille);
	for(i=0;i<m->nrows;i++)
		for(j=0;j<m->ncol;j++)
			if(i==j)
				setElt(m,i,j,1.);
	return m;
}

Matrix copyMatrix(const Matrix m){
	Matrix cpy = newMatrix(m->nrows,m->ncol);
   int j,i;
   for(i=0;i<m->nrows;i++){
     for(j=0;j<m->ncol;j++){
       setElt(cpy,i,j,getElt(m,i,j));
     }
   }
	return cpy;
}
