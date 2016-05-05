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

E abso(E val){
	if(val < 0 )
		return -1 * val;
	else
		return val;
	}

Matrix triangle(const Matrix m){
	Matrix D=copyMatrix(m);
  int i,k,tmp;
  E pivot;
  for(k=0;k<(D->nrows-1);k++){
    tmp=k;
    while(tmp<(D->nrows-1) && abso((pivot=getElt(D,tmp,k)))<0.0001){
      tmp++;
    }
    swapLine(D,tmp,k);
    for(i=k+1;i<D->nrows;i++){
      combineLine(D,(-getElt(D,i,k)/pivot),k,1,i);
    }
  }

  return D;
}

E determinant(const Matrix m){
	if(m->nrows != m->ncol){
		fprintf(stderr,"La matrice n'est pas carré");
		return 0;
	}
	Matrix D=triangle(m);
	int i,k;
	E deter=1;
	for(i=D->nrows-1;i>0;i--){
		for(k=i-1;k>=0;k--){
			if(abso(getElt(D,i,i))<0.00001){
				deleteMatrix(D);
				return 0.;
			}
      combineLine(D,(-getElt(D,k,i)/getElt(D,i,i)),i,1,k);
		}
	}
	for(i=0;i<m->nrows;i++){
		deter*=getElt(D,i,i);
	}
	deleteMatrix(D);
	return deter;
}

Matrix solve_gauss_simple(const Matrix A,const Matrix B){
	if(abso(determinant(A))<0.00001){
		fprintf(stderr,"La matrice n'est pas inversible\n");
		return NULL;
	}
  Matrix X=newMatrix(B->nrows,B->ncol);
  Matrix D=copyMatrix(A);
	Matrix Bcpy=copyMatrix(B);
  int i,j,k,tmp;
  E pivot;
  for(k=0;k<(D->nrows-1);k++){
    tmp=k;
    while(tmp<(D->nrows-1) && abso((pivot=getElt(D,tmp,k)))<0.0001){
      tmp++;
    }
    swapLine(D,tmp,k);
		swapLine(Bcpy,tmp,k);
    for(i=k+1;i<D->nrows;i++){
			combineLine(Bcpy,(-getElt(D,i,k)/pivot),k,1,i);
      combineLine(D,(-getElt(D,i,k)/pivot),k,1,i);
    }
  }
	for(i=D->nrows-1;i>=0;i--){
		setElt(X,i,0,getElt(Bcpy,i,0));
		for(j=i+1;j<(D->nrows);j++){
			setElt(X,i,0,getElt(X,i,0)-getElt(D,i,j)*getElt(X,j,0));
		}
		setElt(X,i,0,getElt(X,i,0)/getElt(D,i,i));
	}
	deleteMatrix(D);
	deleteMatrix(Bcpy);
  return X;
}

Matrix inverse(const Matrix m){
	if(m->nrows!=m->ncol){
		fprintf(stderr,"La matrice n'est pas carré\n");
		return NULL;
	}
	if(abso(determinant(m))<0.00001){
		fprintf(stderr,"La matrice n'est pas inversible\n");
		return NULL;
	}
	Matrix I=Identite(m->nrows);
	Matrix A=copyMatrix(m);
	int i,k,tmp;
  E pivot;
	for(k=0;k<(A->nrows-1);k++){
    tmp=k;
    while(tmp<(A->nrows-1) && abso((pivot=getElt(A,tmp,k)))<0.0001){
      tmp++;
    }
    swapLine(A,tmp,k);
		swapLine(I,tmp,k);
    for(i=k+1;i<A->nrows;i++){
			combineLine(I,(-getElt(A,i,k)/pivot),k,1,i);
      combineLine(A,(-getElt(A,i,k)/pivot),k,1,i);
    }
  }
	for(i=A->nrows-1;i>0;i--){
		for(k=i-1;k>=0;k--){
			combineLine(I,(-getElt(A,k,i)/getElt(A,i,i)),i,1,k);
      combineLine(A,(-getElt(A,k,i)/getElt(A,i,i)),i,1,k);
		}
	}
	for(i=0;i<A->nrows;i++){
		combineLine(I,(1/getElt(A,i,i)),i,0,i);
		combineLine(A,(1/getElt(A,i,i)),i,0,i);
	}
	deleteMatrix(A);
	return I;
}

int rank(const Matrix m){
	int r=m->nrows;
	Matrix D=triangle(m);
	int i,j;
	for(i=0;i<m->nrows;i++){
		for(j=0;j<=m->ncol;j++){
			if(j==m->ncol){
				r--;
				break;
			}
			if(getElt(D,i,j)>0.00001)
				break;
		}
	}
	return r;
}

//m1 correspond à notre l et m2 à u
E sommeAux(Matrix m1, Matrix m2, int positioni, int positionj ){
	E somme=0,k;
	for(k=0; k <= positioni-1; k++){
		somme += getElt(m1,positioni,k) * getElt(m2, k, positionj);
		}
	return somme;
	}

E sommeAux2(Matrix m1, Matrix m2, int positioni, int positionj ){
	E somme=0,k;
	for(k=0; k <= positioni-1; k++){
		somme += getElt(m1,positionj,k) * getElt(m2, k, positioni);
		}
	return somme;
	}

E sommeAux3(Matrix m1, Matrix m2, int positionN){
	E somme=0,k;
	for(k=0; k <= positionN-1; k++){
		somme += getElt(m1,positionN,k) * getElt(m2, k, positionN);
		}
	return somme;
	}

Matrix * decompositionLU(const Matrix m){
	int i,j,n=m->nrows;
	Matrix l = Identite(n);
	Matrix u = newMatrix(n,n);

	for(i=0;i< n -1;i++){
		for(j=i;j < n; j++){
			setElt(u,i,j, getElt(m,i,j) - sommeAux(l,u,i,j));
			}
		for(j=i+1; j < n; j++){
			setElt(l,j,i, ( (1. / getElt(u,i,i)) * (getElt(m,j,i) - sommeAux2(l,u,i,j))));
			}
			printf(" itération : %d \n", i);
			displayMatrix(l);
			displayMatrix(u);
		}

	setElt(u,n-1,n-1, getElt(m, n-1,n-1 ) - sommeAux3(l,u,n-1));

	Matrix * lu = (Matrix *) malloc( sizeof(std_matrix) * 2);
	lu[0] =l;
	lu[1] = u;

	return lu;
	}


int approxMat(Matrix m1, Matrix m2, E precision){
	int i,j;
	for(i=0;i<m1->nrows;i++){
		for(j=0;j<m1->ncol;j++){
			if(  abso (getElt(m1,i,j)) - abso(getElt(m2,i,j)) > precision){
				return 0;}
			}
		}
	return 1;
	}

E maxComposante(Matrix m){
	E max = getElt(m,0,0);
	int i,j;
	for(i=0;i< m->nrows;i++){
		for(j=0;j< m->ncol;j++){
			if(max < getElt(m,i,j))
				max = getElt(m,i,j);
			}
		}
	return max;
	}

couple approximation_vp(const Matrix a, E precision){
	Matrix u = newMatrix(a->ncol,1);
	int i;
	for(i=0;i<u->nrows;i++)
		setElt(u,i,0,0.1);
	setElt(u,0,0,1);
	Matrix unew = copyMatrix(u);
	E vp = 1;
	E vpnew = vp;
	do{
		vp = vpnew;
		u = copyMatrix(unew);
			//	displayMatrix(u);
		unew = mult(a,u);
		//printf("valeur de unew : \n");
		//displayMatrix(unew);
		vpnew = maxComposante(unew);
		unew = multScalaire(unew,(1/vpnew));
		}
	while( abso( vpnew - vp ) > precision || !approxMat(unew,u,precision) );

	couple cp = (couple) malloc(sizeof(struct scouple));
	cp->valp = vpnew;
	cp->vectp = unew;
	return cp;
	}

couple* liste_vp(const Matrix a, E precision){
	int i,n=a->nrows;
	couple * tab = (couple *) malloc( n * sizeof(struct scouple) );
	Matrix b = copyMatrix(a);
	couple btransp;
	for(i=0;i<n;i++){
		tab[i] = approximation_vp(b,precision);
		btransp = approximation_vp( transpose(b) , precision);
		b= soustraction(a , multScalaire( mult(multScalaire( tab[i]->vectp, tab[i]->valp), transpose( btransp->vectp) ), 1/ getElt(mult(transpose(btransp->vectp), tab[i]->vectp),0,0) ));
		}
	return tab;
	}
