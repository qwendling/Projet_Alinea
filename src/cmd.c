#include "cmd.h"

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
  unsigned int i=0;
  int nbPoint=0;
  while(i<strlen(number) && number[i]==' ')
    i++;
  for(;i<strlen(number);i++){
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
  for(;i<strlen(number);i++){
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

void createVar(char *key,char *val,Variable tabVar[]){
  int h=hach(key);
  if(est_float(val)==0){
    fprintf(stderr,"%s n'est pas un float\n",val);
    return;
  }
  tabVar[h]=adjVar(tabVar[h],atof(val),key);
  printf("variable créée\n");
}

void afficheVar(Variable tabVar[],char *key){
  int i;
  Variable tmp;
  for(i=0;i<4096;i++){
    tmp=existeVar(tabVar[i],key);
    if(tmp!=NULL){
      printf("%lf\n",tmp->val);
      return;
    }
  }
  printf("Variable non reconnu\n");
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

int main(){
  char input[4096];
  Variable tabVar[4096];
  //VarMatrix tabVarMat[4096];
  int i;
  for(i=0;i<4096;i++){
    tabVar[i]=NULL;
    //tabVarMat[i]=NULL;
  }
  char** buffer;
  char **buffer2;
  while(1){
    printf("> ");
    fgets(input,4096,stdin);
    input[strlen(input)-1]='\0';
    if(strcmp(input,"quit")==0){
      for(i=0;i<4096;i++){
        supVar(tabVar[i]);
        //tabVarMat[i]=NULL;
      }
      break;
    }
    buffer=separe(input,":");
    if(bufflen(buffer)>2){
      fprintf(stderr,"Unexpected ':'\n");
      free(buffer);
      continue;
    }
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
        if(strcmp(buffer2[0],"Matrix")==0)
          printf("Tu veux faire une matrix ! \n");
        free(buffer);
        free(buffer2);
        continue;
      }
      buffer[0]=SuppSpace(buffer[0]);
      createVar(buffer[0],buffer[1],tabVar);
      free(buffer);
      free(buffer2);
      continue;
    }
    buffer2=separe(buffer[0],"(");
    if(bufflen(buffer2)==1){
      buffer2[0]=SuppSpace(buffer2[0]);
      afficheVar(tabVar,buffer2[0]);
      free(buffer);
      free(buffer2);
      continue;
    }
    buffer[0]=SuppSpace(buffer[0]);
    printf("%s non reconnu\n",buffer[0]);
    free(buffer);
    free(buffer2);
  }
  return 0;
}
