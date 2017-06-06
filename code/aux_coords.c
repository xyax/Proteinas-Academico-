#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "aux_coords.h"


/**Analisa se o número de argumentos é par.
 @param recebe um string e a proteina.
 @return Retorna 0 se ímpar(FALSE) e algo diferente de 0 se par (TRUE). */
int numero_de_args_par(char *args, proteina *p){
	int nargs = 0;int i = 0;
	while(args[i]!='\0'){
		while(isalnum(args[i]) || args[i] == '-') i++;
		while(isspace(args[i])) i++;
		nargs++;
	}
	(*p).size.test = nargs/2;
	return !(nargs%2);
}

/**Testa se uma string possui apenas dígitos. 
 @param recebe um string.
 @return 1 se for digito. Retorna 0 se não for digito **/
int so_numeros(char *ag){
	int i = 0,b = 1;
	while(ag[i]!='\0'){
		if(!(isdigit(ag[i])) && ag[i]!='-') b = 0;
		if(ag[i]=='-' && !(isdigit(ag[i+1]))) b = 0;
		i++;
		while(!(isspace(ag[i])) && (ag[i]!='\0')){
			if(!(isdigit(ag[i]))) b = 0;
			i++;
		}
		while(isspace(ag[i]) && (ag[i]!='\0')) i++;
	}
	return b;
}

/**Guarda as coordenadas na estrutura coordenadas
 @param recebe uma string de coordenadas e a proteina*/

void guarda_coords(char *args, proteina *p){
	int i = 0;
	while(sscanf(args,"%d %d %[^\n]", &(*p).coordenadas[i].x, &(*p).coordenadas[i].y, args) == 3) i++;
}

/**Imprime as coordenadas
@param Proteina. */
void imprime_coords(proteina *p){
	int i = 0;
	while(i < ((*p).size.coords-1)){
		printf("(%d, %d) ",(*p).coordenadas[i].x,(*p).coordenadas[i].y);
		i++;
		}
	printf("(%d, %d)\n",(*p).coordenadas[i].x,(*p).coordenadas[i].y);
	}

