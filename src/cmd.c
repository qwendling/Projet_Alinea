#include "cmd.h"

int main(){
  Matrix Id=Identite(3);
  Matrix ex=newMatrix(3,3);
  Matrix ex2=newMatrix(3,2);
  setElt(ex2,0,0,2.);
  setElt(ex2,1,1,2.);
  setElt(ex2,2,0,2.);
  setElt(ex2,2,0,2.);
  setElt(ex2,1,1,2.);
  Matrix tmp;
  setElt(ex,0,0,5.);
  setElt(ex,1,1,3.);
  setElt(ex,2,2,9.);
  displayMatrix(Id);
  printf("\n");
  displayMatrix(ex);
  tmp=mult(ex,ex2);
  printf("\n");
  displayMatrix(tmp);
  deleteMatrix(tmp);
  tmp=expo(Id,3);
  printf("\n");
  displayMatrix(tmp);
  deleteMatrix(tmp);
  printf("\n");
  displayMatrix(ex2);
  deleteMatrix(ex2);
  deleteMatrix(Id);
  deleteMatrix(ex);
  return 0;
}
