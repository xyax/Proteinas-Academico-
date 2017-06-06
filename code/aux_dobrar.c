#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "aux_dobrar.h"

/**Guarda as dobras na estrutura e o tamanho.
@param recebe string de argumentos de dobra e a proteina.
@return 1 . **/
int guarda_dobras_e_coordenadas(char *ag, proteina *p){
	strcpy((*p).dobras,ag);
	(*p).size.coords = strlen((*p).dobras) +1;
	dobra_coordenadas(ag, p);
	return 1;
}

/**Dobra a sequência de proteínas para as coordenadas respectivas.
@param string de dobras e a proteina. */
void dobra_coordenadas(char *ag, proteina *p){
	char last = 'd';
	int i = 1;
	(*p).coordenadas[0].x=0;
	(*p).coordenadas[0].y=0;
	if(ag[0]=='F'){
		last='d';
		(*p).coordenadas[1].x=1;
		(*p).coordenadas[1].y=0;
	} else {
		if(ag[0]=='D'){
			(*p).coordenadas[1].x=0;
			(*p).coordenadas[1].y=-1;
			last='b';
		} else {
			if(ag[0]=='E'){
				last = 'c';
				(*p).coordenadas[1].x=0;
				(*p).coordenadas[1].y=1;
			}
		}
	}
	while(i<((*p).size.coords)){
		switch(char_to_int(last)){
			case 1:	switch(char_to_int(ag[i])){
						case 1:	last = 'c';
								(*p).coordenadas[i+1].x = (*p).coordenadas[i].x;
								(*p).coordenadas[i+1].y = (*p).coordenadas[i].y+1;
								break;
						case 2:	last = 'd';
								(*p).coordenadas[i+1].x = (*p).coordenadas[i].x+1;
								(*p).coordenadas[i+1].y = (*p).coordenadas[i].y;
								break;
						case 3: last = 'e';
								(*p).coordenadas[i+1].x = (*p).coordenadas[i].x-1;
								(*p).coordenadas[i+1].y = (*p).coordenadas[i].y;
								break;
					}break;
			case 2: switch(char_to_int(ag[i])){
						case 1:	last = 'd';
								(*p).coordenadas[i+1].x = (*p).coordenadas[i].x+1;
								(*p).coordenadas[i+1].y = (*p).coordenadas[i].y;
								break;
						case 2:	last = 'b';
								(*p).coordenadas[i+1].x = (*p).coordenadas[i].x;
								(*p).coordenadas[i+1].y = (*p).coordenadas[i].y-1;
								break;
						case 3: last = 'c';
								(*p).coordenadas[i+1].x = (*p).coordenadas[i].x;
								(*p).coordenadas[i+1].y = (*p).coordenadas[i].y+1;
								break;
					}break;
			case 3:	switch(char_to_int(ag[i])){
						case 1:	last = 'e';
								(*p).coordenadas[i+1].x = (*p).coordenadas[i].x-1;
								(*p).coordenadas[i+1].y = (*p).coordenadas[i].y;
								break;
						case 2:	last = 'c';
								(*p).coordenadas[i+1].x = (*p).coordenadas[i].x;
								(*p).coordenadas[i+1].y = (*p).coordenadas[i].y+1;
								break;
						case 3: last = 'b';
								(*p).coordenadas[i+1].x = (*p).coordenadas[i].x;
								(*p).coordenadas[i+1].y = (*p).coordenadas[i].y-1;
								break;
					}break;
			case 4:	switch(char_to_int(ag[i])){
						case 1:	last = 'b';
								(*p).coordenadas[i+1].x = (*p).coordenadas[i].x;
								(*p).coordenadas[i+1].y = (*p).coordenadas[i].y-1;
								break;
						case 2:	last = 'e';
								(*p).coordenadas[i+1].x = (*p).coordenadas[i].x-1;
								(*p).coordenadas[i+1].y = (*p).coordenadas[i].y;
								break;
						case 3: last = 'd';
								(*p).coordenadas[i+1].x = (*p).coordenadas[i].x+1;
								(*p).coordenadas[i+1].y = (*p).coordenadas[i].y;
								break;
					}break;
		}
		i++;
	}
	(*p).esta_colocada = 'c';
}

/**retorna um inteiro respectivo a um dos caracteres.
 @param um caracter.
 @return um inteiro conforme o caracter. */
int char_to_int(char c){
	if(c=='F' || c=='c')
		return 1;
	else 
		if(c=='D' || c=='d')
			return 2;
		else
			if(c=='E' || c=='e')
				return 3;
			else
				if(c=='b')
					return 4;
				else
					return 0;
}
