#include "cmd.h"

Variable tabVar[4096];
VarMatrix tabVarMat[4096];

int hach(char* name){
  unsigned int i;
  int h=0;
  for(i=0;i<strlen(name);i++){
    h+=name[i]<<i;
  }
  return h%4096;
}

char **separe( char *chaine, const char *separateurs ){
	char **tab;
	int i, s, m, size=10;

	tab = malloc( size * sizeof(char*) );
	m = 0;
	i = 0;
	while( chaine[i] != 0 )
	{
		// saute un séparateur
		for( s=0 ; separateurs[s]!=0 ; s++ )
			if( chaine[i] == separateurs[s] )
				break;
		if( separateurs[s]!=0 )
		{
			chaine[i++] = 0;	// met un fin de chaine à la place du séparateur et avance
			continue;	// les séparateurs n'ont pas été épuisés
		}

		if( chaine[i] != 0 )
			tab[m++] = chaine+i;
		if( m == size )
		{
			// si j'atteinds la limite de la taille de mon tableau, je l'agrandis.
			size += 10;
			tab = realloc( tab, size * sizeof(char*) );
		}
		// saute les caractères non séparateurs
		for( ; chaine[i]!=0 ; i++ )
		{
			for( s=0 ; separateurs[s]!=0 ; s++ )
				if( chaine[i] == separateurs[s] )
					break;
			if( separateurs[s]!=0 )
				break;	// trouvé un caractère séparateur, j'arrête d'avancer et je passe au mot suivant
		}
	}
	tab[m] = NULL;
	return( tab );
}

int bufflen(char** buff){
  int i=0;
  for(;*buff;buff++){
    i++;
  }
  return i;
}

int est_float(char *number){
  int i=0;
  int nbPoint=0;
  int size=strlen(number);
  while(i<size && number[i]==' ')
    i++;
  if(i!=size && number[i]=='-')
    i++;
  for(;i<size;i++){
    if(number[i]>='0' && number[i]<='9')
      continue;
    if(number[i]=='.'){
      nbPoint++;
      if(nbPoint>1){
        return 0;
      }
      continue;
    }
    if(number[i]==' '){
      break;
    }
    return 0;
  }
  for(;i<size;i++){
    if(number[i]!=' '){
      return 0;
    }
  }
  return 1;
}

Variable existeVar(Variable v,char *key){
  if(v==NULL){
    return NULL;
  }
  if(strcmp(v->name,key)==0){
    return v;
  }
  return existeVar(v->next,key);
}

Variable adjVar(Variable v,E x,char* key){
  Variable e=existeVar(v,key);
  if(e!=NULL){
    e->val=x;
    return v;
  }
  Variable new=malloc(sizeof(var));
  new->name=malloc(strlen(key)+1);
  new->name=strcpy(new->name,key);
  new->val=x;
  new->next=v;

  return new;
}

void createVar(char *key,char *val){
  int h=hach(key);
  if(est_float(val)==0){
    fprintf(stderr,"%s n'est pas un float\n",val);
    return;
  }
  tabVar[h]=adjVar(tabVar[h],atof(val),key);
  printf("variable créée\n");
}

void supVar(Variable v){
  if(v==NULL){
    return;
  }
  Variable tmp=v->next;
  free(v->name);
  free(v);
  supVar(tmp);
}

char* SuppSpace(char *str){
  int i=0;
  int size=strlen(str);

  while(i<size && str[i]==' ')
    i++;
  if(i==size-1){
    if(i==0)
      return str;
    return NULL;
  }
  int j=size-1;
  while(j>i && str[j]==' ')
    j--;
  char* new=malloc(j-i+1);
  int k;
  for(k=0;i<=j;k++,i++){
    new[k]=str[i];
  }
  new[k]='\0';
  return new;
}

int countChar(char *str,char c){
  int count=0,i;
  int size=strlen(str);
  for(i=0;i<size;i++){
    if(str[i]==c)
      count++;
  }
  return count;
}

VarMatrix existeMatrix(char* key,VarMatrix v){
  if(v==NULL){
    return NULL;
  }
  if(strcmp(v->name,key)==0){
    return v;
  }
  return existeMatrix(key,v);
}

VarMatrix adjVarMat(VarMatrix v,Matrix m,char* key){
  VarMatrix e=existeMatrix(key,v);
  if(e!=NULL){
    deleteMatrix(e->val);
    e->val=m;
    return v;
  }
  VarMatrix new=malloc(sizeof(varMat));
  new->val=m;
  new->next=v;
  new->name=malloc(strlen(key)+1);
  new->name=strcpy(new->name,key);
  return new;
}

void createMatrix(char *key,char* mat){
  int i;
  int size=strlen(mat);
  int nbligne=0,nbcol=0,nbcoltmp,sizetmp;
  if(size==0){
    fprintf(stderr,"Aucun argument pour le création de matrice\n");
    return;
  }
  char** buffer=separe(mat,",");
  int sizebuff=bufflen(buffer);
  for(i=0;i<sizebuff;i++){
    if(buffer[i][0]=='['){
      sizetmp=strlen(buffer[i]);
      if(sizetmp==1){
        fprintf(stderr,"Aucune valeur trouvée pour une case de la matrice \n");
        return;
      }
      if(buffer[i][sizetmp-1]==']'){
        if(sizetmp==2){
          fprintf(stderr,"Aucune valeur trouvée pour une case de la matrice \n");
          return;
        }
        buffer[i][sizetmp-1]='\0';
        if(est_float(buffer[i]+1)==0){
          fprintf(stderr,"Unexpected %s\n",buffer[i]+1);
          return;
        }
        if(nbcol==0)
          nbcol=1;
        else
          if(nbcol!=1){
            fprintf(stderr,"Toute les lignes n'ont pas la meme taille\n");
            return;
          }
        nbligne++;
        continue;
      }
      if(est_float(buffer[i]+1)==0){
        fprintf(stderr,"Unexpected %s\n",buffer[i]+1);
        return;
      }
      nbcoltmp=1;
      i++;
      nbligne++;
      for(;i<sizebuff;i++){
        sizetmp=strlen(buffer[i]);
        if(buffer[i][sizetmp-1]==']'){
          if(sizetmp==1){
            fprintf(stderr,"Aucune valeur trouvée pour une case de la matrice \n");
            return;
          }
          buffer[i][sizetmp-1]='\0';
          if(est_float(buffer[i])==0){
            fprintf(stderr,"Unexpected %s\n",buffer[i]);
            return;
          }
          nbcoltmp++;
          break;
        }
        if(est_float(buffer[i])==0){
        fprintf(stderr,"Unexpected '%c'\n",buffer[i][0]);
        free(buffer);
        return;
        }
        nbcoltmp++;
      }
      if(nbcol==0){
        nbcol=nbcoltmp;
      }
      else{
        if(nbcol!=nbcoltmp){
          fprintf(stderr,"Toute les lignes n'ont pas la meme taille\n");
          return;
        }
      }
      if(i==sizebuff){
        fprintf(stderr,"Expected ']'\n");
      }
      continue;
    }
    fprintf(stderr,"Unexpected '%c'\n",buffer[i][0]);
    free(buffer);
    return;
  }
  Matrix new=newMatrix(nbligne,nbcol);
  int row=0,col;
  for(i=0;i<sizebuff;i++,row++){
    if(buffer[i][0]=='['){
      col=0;
      setElt(new,row,col,atof(buffer[i]+1));
      col++;
      i++;
      for(;col<nbcol;i++,col++){
        setElt(new,row,col,atof(buffer[i]));
      }
      i--;
    }
  }
  displayMatrix(new);
  int h=hach(key);
  tabVarMat[h]=adjVarMat(tabVarMat[h],new,key);
  free(buffer);
}

Variable rechercheVar(char *key){
  return existeVar(tabVar[hach(key)],key);
}

VarMatrix rechercheVarMat(char *key){
  return existeMatrix(key,tabVarMat[hach(key)]);
}

void afficheVar(char *key){
  VarMatrix tmpMat=rechercheVarMat(key);
  Variable tmpVar;
  if(tmpMat==NULL){
    tmpVar=rechercheVar(key);
    if(tmpVar==NULL){
      fprintf(stderr,"Variable non reconnu\n");
      return;
    }
    printf("%lf\n",tmpVar->val);
  }else{
    displayMatrix(tmpMat->val);
  }
}

Matrix addInter(char* arg){
  char **buffer=separe(arg,",");
  if(bufflen(buffer)!=2){
    fprintf(stderr,"Nombre d'argument invalide\n");
    free(buffer);
    return NULL;
  }
  VarMatrix arg1=rechercheVarMat(buffer[0]);
  if(arg1==NULL){
    fprintf(stderr,"%s n'est pas une matrice\n",buffer[0]);
    free(buffer);
    return NULL;
  }
  VarMatrix arg2=rechercheVarMat(buffer[1]);
  if(arg2==NULL){
    fprintf(stderr,"%s n'est pas une matrice\n",buffer[1]);
    free(buffer);
    return NULL;
  }
  free(buffer);
  return addition(arg1->val,arg2->val);
}

Matrix subInter(char* arg){
  char **buffer=separe(arg,",");
  if(bufflen(buffer)!=2){
    fprintf(stderr,"Nombre d'argument invalide\n");
    free(buffer);
    return NULL;
  }
  VarMatrix arg1=rechercheVarMat(buffer[0]);
  if(arg1==NULL){
    fprintf(stderr,"%s n'est pas une matrice\n",buffer[0]);
    free(buffer);
    return NULL;
  }
  VarMatrix arg2=rechercheVarMat(buffer[1]);
  if(arg2==NULL){
    fprintf(stderr,"%s n'est pas une matrice\n",buffer[1]);
    free(buffer);
    return NULL;
  }
  free(buffer);
  return soustraction(arg1->val,arg2->val);
}

Matrix multInter(char* arg){
  char **buffer=separe(arg,",");
  if(bufflen(buffer)!=2){
    fprintf(stderr,"Nombre d'argument invalide\n");
    free(buffer);
    return NULL;
  }
  VarMatrix arg1=rechercheVarMat(buffer[0]);
  if(arg1==NULL){
    fprintf(stderr,"%s n'est pas une matrice\n",buffer[0]);
    free(buffer);
    return NULL;
  }
  VarMatrix arg2=rechercheVarMat(buffer[1]);
  if(arg2==NULL){
    fprintf(stderr,"%s n'est pas une matrice\n",buffer[1]);
    free(buffer);
    return NULL;
  }
  free(buffer);
  return mult(arg1->val,arg2->val);
}

Matrix transposeInter(char* arg){
  char **buffer=separe(arg,",");
  if(bufflen(buffer)!=1){
    fprintf(stderr,"Nombre d'argument invalide\n");
    free(buffer);
    return NULL;
  }
  VarMatrix arg1=rechercheVarMat(buffer[0]);
  if(arg1==NULL){
    fprintf(stderr,"%s n'est pas une matrice\n",buffer[0]);
    free(buffer);
    return NULL;
  }
  free(buffer);
  return transpose(arg1->val);
}

Matrix multScalaireInter(char* arg){
  char **buffer=separe(arg,",");
  if(bufflen(buffer)!=2){
    fprintf(stderr,"Nombre d'argument invalide\n");
    free(buffer);
    return NULL;
  }
  Variable arg1=rechercheVar(buffer[0]);
  E scal;
  if(arg1==NULL){
    if(est_float(buffer[0])){
      scal=atof(buffer[0]);
    }else{
      fprintf(stderr,"%s n'est pas un float\n",buffer[0]);
      free(buffer);
      return NULL;
    }
  }
  else{
    scal=arg1->val;
  }
  VarMatrix arg2=rechercheVarMat(buffer[1]);
  if(arg2==NULL){
    fprintf(stderr,"%s n'est pas une matrice\n",buffer[1]);
    free(buffer);
    return NULL;
  }
  free(buffer);
  return multScalaire(arg2->val,scal);
}

int main(){
  char input[4096];
  int i,tmp;
  for(i=0;i<4096;i++){
    tabVar[i]=NULL;
    tabVarMat[i]=NULL;
  }
  char** buffer;
  char **buffer2;
  Matrix Mattmp;
  while(1){
    printf("> ");
    fgets(input,4096,stdin);
    input[strlen(input)-1]='\0';
    //Si on entre quit on quitte
    if(strcmp(input,"quit")==0){
      for(i=0;i<4096;i++){
        supVar(tabVar[i]);
        //tabVarMat[i]=NULL;
      }
      break;
    }
    buffer=separe(input,":");
    //Si on trouve plusieurs ':' l'entrée est incorrecte
    if(bufflen(buffer)>2){
      fprintf(stderr,"Unexpected ':'\n");
      free(buffer);
      continue;
    }
    //Si on trouve un ':' on dois faire une affectation
    if(bufflen(buffer)==2){
      buffer2=separe(buffer[1],"(");
      if(bufflen(buffer2)>2){
        fprintf(stderr,"Unexpected '('\n");
        free(buffer);
        free(buffer2);
        continue;
      }
      if(bufflen(buffer2)==2){
        buffer2[0]=SuppSpace(buffer2[0]);
        buffer[1]=SuppSpace(buffer[1]);
        tmp=countChar(buffer2[1],')');
        if(tmp==0){
          fprintf(stderr,"Expected ')'\n");
          free(buffer);
          free(buffer2);
          continue;
        }
        if(tmp>1){
          fprintf(stderr,"Unexpected ')'\n");
          free(buffer);
          free(buffer2);
          continue;
        }
        if(strcmp(buffer2[0],"Matrix")==0){
          buffer2[1][strlen(buffer2[1])-1]='\0';
          if(rechercheVar(buffer[0])!=NULL)
            fprintf(stderr,"%s est de type float\n",buffer[0]);
          else
            createMatrix(buffer[0],buffer2[1]);
          free(buffer);
          free(buffer2);
          continue;
        }
        printf("%s non reconnu\n",buffer2[0]);
        free(buffer);
        free(buffer2);
        continue;
      }
      buffer[0]=SuppSpace(buffer[0]);
      if(rechercheVarMat(buffer[0])!=NULL)
        fprintf(stderr,"%s est une Matrice\n",buffer[0]);
      else
        createVar(buffer[0],buffer[1]);
      free(buffer);
      free(buffer2);
      continue;
    }
    //Sinon on regarde si c'est un appel de fonction ou une variable
    buffer2=separe(buffer[0],"(");
    //C'est une varible on affiche ça valeur
    if(bufflen(buffer2)>2){
      fprintf(stderr,"Unexpected '('\n");
      free(buffer);
      free(buffer2);
      continue;
    }
    if(bufflen(buffer2)==1){
      buffer2[0]=SuppSpace(buffer2[0]);
      afficheVar(buffer2[0]);
      free(buffer);
      free(buffer2);
      continue;
    }
    buffer2[0]=SuppSpace(buffer2[0]);
    if(strcmp(buffer2[0],"add")==0){
      if(buffer2[1][strlen(buffer2[1])-1]!=')'){
        fprintf(stderr,"Expected ')'\n");
        free(buffer);
        free(buffer2);
        continue;
      }
      buffer2[1][strlen(buffer2[1])-1]='\0';
      Mattmp=addInter(buffer2[1]);
      if(Mattmp!=NULL){
        displayMatrix(Mattmp);
        deleteMatrix(Mattmp);
      }
      free(buffer);
      free(buffer2);
      continue;
    }
    if(strcmp(buffer2[0],"soustraction")==0){
      if(buffer2[1][strlen(buffer2[1])-1]!=')'){
        fprintf(stderr,"Expected ')'\n");
        free(buffer);
        free(buffer2);
        continue;
      }
      buffer2[1][strlen(buffer2[1])-1]='\0';
      Mattmp=subInter(buffer2[1]);
      if(Mattmp!=NULL){
        displayMatrix(Mattmp);
        deleteMatrix(Mattmp);
      }
      free(buffer);
      free(buffer2);
      continue;
    }
    if(strcmp(buffer2[0],"mult")==0){
      if(buffer2[1][strlen(buffer2[1])-1]!=')'){
        fprintf(stderr,"Expected ')'\n");
        free(buffer);
        free(buffer2);
        continue;
      }
      buffer2[1][strlen(buffer2[1])-1]='\0';
      Mattmp=multInter(buffer2[1]);
      if(Mattmp!=NULL){
        displayMatrix(Mattmp);
        deleteMatrix(Mattmp);
      }
      free(buffer);
      free(buffer2);
      continue;
    }
    if(strcmp(buffer2[0],"multScalaire")==0){
      if(buffer2[1][strlen(buffer2[1])-1]!=')'){
        fprintf(stderr,"Expected ')'\n");
        free(buffer);
        free(buffer2);
        continue;
      }
      buffer2[1][strlen(buffer2[1])-1]='\0';
      Mattmp=multScalaireInter(buffer2[1]);
      if(Mattmp!=NULL){
        displayMatrix(Mattmp);
        deleteMatrix(Mattmp);
      }
      free(buffer);
      free(buffer2);
      continue;
    }
    if(strcmp(buffer2[0],"transpose")==0){
      if(buffer2[1][strlen(buffer2[1])-1]!=')'){
        fprintf(stderr,"Expected ')'\n");
        free(buffer);
        free(buffer2);
        continue;
      }
      buffer2[1][strlen(buffer2[1])-1]='\0';
      Mattmp=transposeInter(buffer2[1]);
      if(Mattmp!=NULL){
        displayMatrix(Mattmp);
        deleteMatrix(Mattmp);
      }
      free(buffer);
      free(buffer2);
      continue;
    }
    //On ne sait pas à quoi correspond l'entrée
    buffer[0]=SuppSpace(buffer[0]);
    printf("%s non reconnu\n",buffer[0]);
    free(buffer);
    free(buffer2);
  }
  return 0;
}
