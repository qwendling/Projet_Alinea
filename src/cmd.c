#include "cmd.h"

int hach(char* name){
  unsigned int i,h=0;
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

int main(){
  char input[4096];
  Variable tabVar[4096];
  VarMatrix tabVarMat[4096];
  while(1){
    fgets(input,4096,stdin);
    input[strlen(input)-1]='\0';
    if(strcmp(input,"quit")==0){
      break;
    }
  }
  return 0;
}
