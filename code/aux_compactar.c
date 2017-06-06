#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "aux_compactar.h"

/**Compacta uma sequência de 'A' e 'B' em grupos de 3 de 2 e de 1, de forma a obter uma string com o menor número possível de caracteres.
@param Proteina. */
void compacta(proteina *p){
	strcpy((*p).volatil,(*p).AsBs);
	(*p).size.compact=(*p).size.AsBs;
	g3(0, 3, 0, 1, p);
	g2(0, 2, 0, 1, p);
	g1(0, 1, 0, 1, p);
}
/**Agrupa em grupos de 3, recursivamente uma string de 'A' e 'B'
@param Marcadores de posições e incrementador. Recebe também a proteina. */
void g3(int i, int j, int k, int conta, proteina *p){
	if((j+2)<(*p).size.compact){
		if(((*p).volatil[i]=='A' || (*p).volatil[i]=='B') && ((*p).volatil[i+1]=='A' || (*p).volatil[i+1]=='B') && 
		((*p).volatil[i+2]=='A' || (*p).volatil[i+2]=='B') && ((*p).volatil[j]=='A' || (*p).volatil[j]=='B') &&
		((*p).volatil[j+1]=='A' || (*p).volatil[j+1]=='B') && ((*p).volatil[j+2]=='A' || (*p).volatil[j+2]=='B')){
			if(((*p).volatil[i]==(*p).volatil[j] && (*p).volatil[i+1]==(*p).volatil[j+1] && (*p).volatil[i+2]==(*p).volatil[j+2]) &&
			((*p).volatil[i]!=(*p).volatil[i+1] || (*p).volatil[i]!=(*p).volatil[i+2])){
				conta++;
				g3(i,j+3,k,conta, p);
			} else {
				if(conta > 2){
					(*p).compact[k]='('; k++;
					(*p).compact[k]=(*p).volatil[i]; k++;
					(*p).compact[k]=(*p).volatil[i+1]; k++;
					(*p).compact[k]=(*p).volatil[i+2]; k++;
					(*p).compact[k]=')'; k++;
					itoa0(conta,&k, p);
					g3(j,j+3,k,1, p);
				} else {
					(*p).compact[k]=(*p).volatil[i]; k++;
					g3(i+1,i+4,k,1, p);
				}
			}
		} else {
			if(conta > 2){
				(*p).compact[k]='('; k++;
				(*p).compact[k]=(*p).volatil[i]; k++;
				(*p).compact[k]=(*p).volatil[i+1]; k++;
				(*p).compact[k]=(*p).volatil[i+2]; k++;
				(*p).compact[k]=')'; k++;
				itoa0(conta,&k, p);
				g3(j,j+3,k,1, p);
			} else {
				(*p).compact[k]=(*p).volatil[i]; k++;
				g3(i+1,i+4,k,1, p);
			}
		}
	} else {
		if(conta > 2){
			(*p).compact[k]='('; k++;
			(*p).compact[k]=(*p).volatil[i]; k++;
			(*p).compact[k]=(*p).volatil[i+1]; k++;
			(*p).compact[k]=(*p).volatil[i+2]; k++;
			(*p).compact[k]=')'; k++;
			itoa0(conta,&k, p);
			(*p).compact[k]='\0';
			(*p).size.compact = k;
			strcpy((*p).volatil,(*p).compact);
		} else {
			while(i<(*p).size.compact){
				(*p).compact[k] = (*p).volatil[i];
				i++; k++;
			}
			(*p).compact[k] = '\0';
			(*p).size.compact = k;
			strcpy((*p).volatil,(*p).compact);
		}
	}
}
/**Agrupa em grupos de 2, recursivamente uma string de 'A' e 'B'
@param Marcadores de posições e incrementador. Recebe também a proteina. */
void g2(int i, int j, int k, int conta, proteina *p){
	if((j+1)<(*p).size.compact+1){
		if(((*p).volatil[i]=='A' || (*p).volatil[i]=='B') && ((*p).volatil[i+1]=='A' || (*p).volatil[i+1]=='B') &&
		((*p).volatil[j]=='A' || (*p).volatil[j]=='B') && ((*p).volatil[j+1]=='A' || (*p).volatil[j+1]=='B')){
			if(((*p).volatil[i]==(*p).volatil[j] && (*p).volatil[i+1]==(*p).volatil[j+1]) && ((*p).volatil[i]!=(*p).volatil[i+1])){
				conta++;
				g2(i,j+2,k,conta, p);
			} else {
				if(conta > 2){
					(*p).compact[k]='('; k++;
					(*p).compact[k]=(*p).volatil[i]; k++;
					(*p).compact[k]=(*p).volatil[i+1]; k++;
					(*p).compact[k]=')'; k++;
					itoa0(conta,&k, p);				
					g2(j,j+2,k,1, p);
				} else {
					(*p).compact[k]=(*p).volatil[i]; k++;
					g2(i+1,i+3,k,1, p);
				}
			}
		} else {
			if(conta > 2){
				(*p).compact[k]='('; k++;
				(*p).compact[k]=(*p).volatil[i]; k++;
				(*p).compact[k]=(*p).volatil[i+1]; k++;
				(*p).compact[k]=')'; k++;
				itoa0(conta,&k, p);
				g2(j,j+2,k,1, p);
			} else {
				(*p).compact[k]=(*p).volatil[i]; k++;
				g2(i+1,i+3,k,1, p);
			}
		}
	} else {
		if(conta > 2){
			(*p).compact[k]='('; k++;
			(*p).compact[k]=(*p).volatil[i]; k++;
			(*p).compact[k]=(*p).volatil[i+1]; k++;
			(*p).compact[k]=')'; k++;
			itoa0(conta,&k, p);
			(*p).compact[k]='\0';
			(*p).size.compact=k;
		} else {
			while(i<(*p).size.compact){
				(*p).compact[k] = (*p).volatil[i];
				i++; k++;
			}
			(*p).compact[k] = '\0';
			(*p).size.compact = k;
			strcpy((*p).volatil,(*p).compact);
		}
	}
}
/**Agrupa em grupos de 1, recursivamente uma string de 'A' e 'B'
@param Marcadores de posições e incrementador. Recebe também a proteina. */

void g1(int i, int j, int k, int conta, proteina *p){
	if(j<(*p).size.compact){
		if(((*p).volatil[i]=='A' || (*p).volatil[i]=='B') && ((*p).volatil[j]=='A' || (*p).volatil[j]=='B')){
			if((*p).compact[i]==(*p).volatil[j]){
				conta++;
				g1(i,j+1,k,conta, p);
			} else {
				if(conta > 2){
					(*p).compact[k]=(*p).volatil[i]; k++;
					itoa0(conta,&k, p);
					g1(j,j+1,k,1, p);
				} else {
					(*p).compact[k]=(*p).volatil[i]; k++;
					g1(i+1,i+2,k,1, p);
				}
			}
		} else {
			if(conta > 2){
				(*p).compact[k]=(*p).volatil[i]; k++;
				itoa0(conta,&k, p);
				g1(j,j+1,k,1, p);
			} else {
				(*p).compact[k]=(*p).volatil[i]; k++;
				g1(i+1,i+2,k,1, p);
			}
		}
	} else {
		if(conta > 2){
			(*p).compact[k]=(*p).volatil[i]; k++;
			itoa0(conta,&k, p);
			(*p).compact[k]='\0';
			(*p).size.compact=k;
		} else {
			while(i<(*p).size.compact){
				(*p).compact[k] = (*p).volatil[i];
				i++; k++;
			}
			(*p).compact[k] = '\0';
			(*p).size.compact = k;
		}
	}
}


/** Recebe um número e um apontador para um número e colaca o número no array de forma inversa.Repõe-lhe a ordem no campo compact (proteina compactada)
 da proteina na devida posição.
@param Número que se pretende de repetições de (ex: (AB)2) e apontador do número com a posição na proteina compactada. */
void itoa0(int n, int *k, proteina *p){
	char s[MAX_SIZE];
	int i = 0; int w = *k;
	do{
		s[i] = (n % 10) + 48;
		i++;
	} while((n /= 10) > 0);
	s[i] = '\0'; i--;
	while(i>=0){
		(*p).compact[w] = s[i];
		i--; w++;
	}
	*k = w;
}

/**Imprime a string compactada.
@param Proteina. */
void imprime_compactado(proteina *p){
	int i;
	for(i=0;(*p).compact[i]!='\0';i++)
		printf("%c",(*p).compact[i]);
	printf("\n");
}
