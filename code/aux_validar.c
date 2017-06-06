#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "aux_validar.h"

/** A função coordenadas_ortogonais testa se as coordenadas consecutivas são ortogonais.
@param A proteina.
@return se ortogonais retorna 1, senão 0. */
int coordenadas_ortogonais(proteina *p){
	int b,i;
	b = i = 1;
	while(i < (*p).size.coords){
		if(abs((*p).coordenadas[i].x - (*p).coordenadas[i-1].x)>1 || abs((*p).coordenadas[i].y - (*p).coordenadas[i-1].y)>1) b=0;
		else if((*p).coordenadas[i].x != (*p).coordenadas[i-1].x && (*p).coordenadas[i].y != (*p).coordenadas[i-1].y) b = 0;
		i++;
	}
	return b;
}

/**testa se todas as coordenadas das proteínas são diferentes.
@param Proteina.
@return retorna 1 se as coordenadas são diferentes, senão retorna 0. */
int coordenadas_diferentes(proteina *p){
	int j,i = 0,b = 1;
	while(i<(*p).size.coords-1){
		for(j=i+1;j<(*p).size.coords;j++)
			if((*p).coordenadas[i].x == (*p).coordenadas[j].x && (*p).coordenadas[i].y == (*p).coordenadas[j].y) b = 0;
		i++;
	}
	return b;
}
