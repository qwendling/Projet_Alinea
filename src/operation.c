#include "operation.h"

Matrix addition(const Matrix m,const Matrix n){
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

Matrix soustraction(const Matrix m,const Matrix n){
	if((m->nrows != n->nrows) || (m->ncol != n->ncol)){
		fprintf(stderr,"Arguments invalide pour la soustraction de matrice");
		return NULL;
	}
	int i,j;
	Matrix sub=newMatrix(m->nrows,m->ncol);
	for(i=0;i<m->nrows;i++)
		for(j=0;j<m->ncol;j++)
				setElt(sub,i,j,getElt(m,i,j)-getElt(n,i,j));
	return sub;
}

Matrix mult(const Matrix m,const Matrix n){
	if(m->ncol != n->nrows){
		fprintf(stderr,"Arguments invalide pour a multiplication de matrice\n");
		exit(1);
	}
	int i,j,k;
	Matrix mult=newMatrix(m->nrows,n->ncol);
	for(i=0;i<m->nrows;i++)
		for(j=0;j<n->ncol;j++)
			for(k=0;k<n->nrows;k++)
				setElt(mult,i,j,getElt(mult,i,j)+getElt(m,i,k)*getElt(n,k,j));
	return mult;
}

Matrix multScalaire(const Matrix m,E x){
  Matrix multSca=newMatrix(m->nrows,m->ncol);
  int i,j;
  for(i=0;i<m->nrows;i++){
    for(j=0;j<m->ncol;j++){
      setElt(multSca,i,j,x*getElt(m,i,j));
    }
  }
  return multSca;
}

Matrix transpose(const Matrix m){
	Matrix trans=newMatrix(m->ncol,m->nrows);
	int j,i;
	for(i=0;i<m->nrows;i++)
		for(j=0;j<m->ncol;j++)
				setElt(trans,j,i,getElt(m,i,j));
	return trans;
}

Matrix expo(const Matrix m,int exposant){
  Matrix ex=copyMatrix(m),tmp;
  int i;
  if(exposant==0){
    return Identite(m->nrows);
  }
  for(i=1;i<exposant;i++){
    tmp=mult(m,ex);
    deleteMatrix(ex);
    ex=tmp;
  }
  return ex;
}

void swapLine(Matrix V,int l1,int l2){
  int j;
  E tmp;
	if(l1==l2)
		return;
  for(j=0;j<V->ncol;j++){
    tmp=getElt(V,l1,j);
    setElt(V,l1,j,getElt(V,l2,j));
    setElt(V,l2,j,tmp);
  }
}

void combineLine(Matrix V,E c1,int l1,E c2,int l2){
  int j;
  E tmp;
  for(j=0;j<V->ncol;j++){
    tmp=c1*getElt(V,l1,j);
    setElt(V,l2,j,tmp+c2*getElt(V,l2,j));
  }
}

Matrix triangle(const Matrix m){
	Matrix D=copyMatrix(A);
  int i,j,k,tmp;
  E pivot;
  for(k=0;k<(D->nrows-1);k++){
    tmp=k;
    while((pivot=getElt(D,tmp,k))<0.0001){
      tmp++;
    }
    swapLine(D,tmp,k);
		printf("%f\n",pivot);
    for(i=k+1;i<D->nrows;i++){
      combineLine(D,(-getElt(D,i,k)/pivot),k,1,i);
    }
  }
  return D;
}
