#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "aux_energia.h"

/**Dada uma posição da string calcula as cargas energéticas nas posições ortogonais ao ponto.
@param posição do array, cargas energéticas e a proteina.
@return calculo da energia. */			

int procura_vizinho(int i, int e1, int e2, int e3, proteina *p){
	int j,e = 0;
	if(i==((*p).size.coords-1)){
		if((*p).coordenadas[i-1].x != (*p).coordenadas[i].x-1 || (*p).coordenadas[i-1].y != (*p).coordenadas[i].y)
			for(j=i-3;j>=0;j--){
				if((*p).coordenadas[j].x == (*p).coordenadas[i].x-1 && (*p).coordenadas[j].y == (*p).coordenadas[i].y){
					if((*p).AsBs[i] == 'A' && (*p).AsBs[j] == 'A') e += e1;
					else
						if((*p).AsBs[i] == 'B' && (*p).AsBs[j] == 'B') e += e2;
						else e += e3;
				}
			}
		if((*p).coordenadas[i-1].x != (*p).coordenadas[i].x+1 || (*p).coordenadas[i-1].y != (*p).coordenadas[i].y)
			for(j=i-3;j>=0;j--){
				if((*p).coordenadas[j].x == (*p).coordenadas[i].x+1 && (*p).coordenadas[j].y == (*p).coordenadas[i].y){
					if((*p).AsBs[i] == 'A' && (*p).AsBs[j] == 'A') e += e1;
					else
						if((*p).AsBs[i] == 'B' && (*p).AsBs[j] == 'B') e += e2;
						else e += e3;
				}
			}
		if((*p).coordenadas[i-1].x != (*p).coordenadas[i].x || (*p).coordenadas[i-1].y != (*p).coordenadas[i].y+1)
			for(j=i-3;j>=0;j--){
				if((*p).coordenadas[j].x == (*p).coordenadas[i].x && (*p).coordenadas[j].y == (*p).coordenadas[i].y+1){
					if((*p).AsBs[i] == 'A' && (*p).AsBs[j] == 'A') e += e1;
					else
						if((*p).AsBs[i] == 'B' && (*p).AsBs[j] == 'B') e += e2;
						else e += e3;
					}
			}
		if((*p).coordenadas[i-1].x != (*p).coordenadas[i].x || (*p).coordenadas[i-1].y != (*p).coordenadas[i].y-1)
			for(j=i-3;j>=0;j--){
				if((*p).coordenadas[j].x == (*p).coordenadas[i].x && (*p).coordenadas[j].y == (*p).coordenadas[i].y-1){
					if((*p).AsBs[i] == 'A' && (*p).AsBs[j] == 'A') e += e1;
					else
						if((*p).AsBs[i] == 'B' && (*p).AsBs[j] == 'B') e += e2;
						else e += e3;
					}
			}
	} else {
		if(((*p).coordenadas[i-1].x != (*p).coordenadas[i].x-1 || (*p).coordenadas[i-1].y != (*p).coordenadas[i].y) && 
			((*p).coordenadas[i+1].x != (*p).coordenadas[i].x-1 || (*p).coordenadas[i+1].y != (*p).coordenadas[i].y)){
			for(j=i-3;j>=0;j--){
					if((*p).coordenadas[j].x == (*p).coordenadas[i].x-1 && (*p).coordenadas[j].y == (*p).coordenadas[i].y){
						if((*p).AsBs[i] == 'A' && (*p).AsBs[j] == 'A') e += e1;
						else
							if((*p).AsBs[i] == 'B' && (*p).AsBs[j] == 'B') e += e2;
							else e += e3;
					}
				}
		}
		if(((*p).coordenadas[i-1].x != (*p).coordenadas[i].x+1 || (*p).coordenadas[i-1].y != (*p).coordenadas[i].y) &&
		((*p).coordenadas[i+1].x != (*p).coordenadas[i].x+1 || (*p).coordenadas[i+1].y != (*p).coordenadas[i].y)){
			for(j=i-3;j>=0;j--){
				if((*p).coordenadas[j].x == (*p).coordenadas[i].x+1 && (*p).coordenadas[j].y == (*p).coordenadas[i].y){
					if((*p).AsBs[i] == 'A' && (*p).AsBs[j] == 'A') e += e1;
					else
						if((*p).AsBs[i] == 'B' && (*p).AsBs[j] == 'B') e += e2;
						else e += e3;
					}
			}
		}
		if(((*p).coordenadas[i-1].x != (*p).coordenadas[i].x || (*p).coordenadas[i-1].y != (*p).coordenadas[i].y+1) &&
		((*p).coordenadas[i+1].x != (*p).coordenadas[i].x || (*p).coordenadas[i+1].y != (*p).coordenadas[i].y+1)){
			for(j=i-3;j>=0;j--){
				if((*p).coordenadas[j].x == (*p).coordenadas[i].x && (*p).coordenadas[j].y == (*p).coordenadas[i].y+1){
					if((*p).AsBs[i] == 'A' && (*p).AsBs[j] == 'A') e += e1;
					else
						if((*p).AsBs[i] == 'B' && (*p).AsBs[j] == 'B') e += e2;
						else e += e3;
					}
			}
		}
		if(((*p).coordenadas[i-1].x != (*p).coordenadas[i].x || (*p).coordenadas[i-1].y != (*p).coordenadas[i].y-1) &&
		((*p).coordenadas[i+1].x != (*p).coordenadas[i].x || (*p).coordenadas[i+1].y != (*p).coordenadas[i].y-1)){
			for(j=i-3;j>=0;j--){
				if((*p).coordenadas[j].x == (*p).coordenadas[i].x && (*p).coordenadas[j].y == (*p).coordenadas[i].y-1){
					if((*p).AsBs[i] == 'A' && (*p).AsBs[j] == 'A') e += e1;
					else
						if((*p).AsBs[i] == 'B' && (*p).AsBs[j] == 'B') e += e2;
						else e += e3;
					}
			}
		}
	}
	return e;
}
			
