#include "operation.h"

Matrix addition(Matrix m,Matrix n){
	if((m->nrows != n->nrows) || (m->ncol != n->ncol)){
		fprintf(stderr,"Arguments invalide pour l'addition de matrice");
		return NULL;
	}
	int i,j;
	Matrix add=newMatrix(m->nrows,m->ncol);
	for(i=0;i<m->nrows;i++)
		for(j=0;j<m->ncol;j++)
				setElt(add,i,j,getElt(m,i,j)+getElt(n,i,j));
	return add;
}

Matrix mult(Matrix m,Matrix n){
	if(m->ncol != n->nrows){
		fprintf(stderr,"Arguments invalide pour a multiplication de matrice\n");
		exit(1);
	}
	int i,j,k;
	Matrix mult=newMatrix(m->nrows,m->ncol);
	for(i=0;i<n->nrows;i++)
		for(j=0;j<n->ncol;j++)
			for(k=0;k<n->nrows;k++)
				setElt(mult,i,j,getElt(mult,i,j)+getElt(m,i,k)*getElt(n,k,j));
	return mult;
}

Matrix transpose(Matrix m){
	Matrix trans=newMatrix(m->ncol,m->nrows);
	int j,i;
	for(i=0;i<m->nrows;i++)
		for(j=0;j<m->ncol;j++)
				setElt(trans,j,i,getElt(m,i,j));
	return trans;
}
