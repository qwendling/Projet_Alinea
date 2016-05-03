#ifndef __CMD_H__
#define __CMD_H__

#include <string.h>
#include "operation.h"

typedef struct var{
  char *name;
  float val;
  struct var* next;
}var,*Variable;

typedef struct varMat{
  char *name;
  Matrix val;
  struct varMat* next;
}varMat,*VarMatrix;


#endif
