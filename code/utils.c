#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "utils.h"



/**Testa se os argumentos são todos 'F' ou 'D' ou 'E'.
@param recebe um string com os argumentos do comando dobras. Recebe também a proteina.
@return  1 se string contiver F's ou D's ou E's. . Retorna 0 caso contrário. */
int F_ou_D_ou_E(char *ag, proteina *p){
	int i = 0;
	int b = 1;
	while(ag[i]!='\0'){
		if(ag[i]!='F' && ag[i]!='D' && ag[i]!='E') b = 0;
		i++;
	}
	if(b) (*p).size.dobras=i;
	return b;
}


/**Introduz 'F' enquanto o tamanho do dobrar for menor ao tamanho da sequência seq - 1 
@param recebe string com os argumentos do comando dobras e a proteina.
@return string de argumentos completada com caracteres'F' **/
char *completa_Fs(char *ag, proteina *p){
	static char buf[MAX_SIZE];
	int i = (*p).size.dobras;

	if(ag == NULL)
		buf[0] = 'F';
	else
		strcpy(buf, ag);

	while(i< (*p).size.AsBs-1){
		buf[i]='F';
		i++;
	}
	buf[i]='\0';
	return buf;
}


