#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#include "estru.h"
#include "prototipos.h"
#include "erro.h"
#include "utils.h"
#include "aux_coords.h"
#include "aux_dobrar.h"
#include "aux_validar.h"
#include "aux_compactar.h"
#include "aux_energia.h"

/**
@return 0  */
int main() {
	proteina p;
	p.size.AsBs = 0;
	p.size.coords = 0;
	p.esta_colocada = '0';
    interpretador(&p);
    return 0;
}
/** manda intrepretar o buffer.
 * @param buffer e proteina*/
void interpretador (proteina *p) {
	char buffer [MAX_SIZE];
	int ciclo = 1;
	while (ciclo && fgets(buffer,MAX_SIZE,stdin)!=NULL) {
		ciclo = interpretar(buffer, p);
	}
}

/**intrepreta o buffer e reencaminha para o comando, caso seja válido
 @return retorna 1 caso comando realizado com sucesso e retorna -1 caso haja qualquer erro.
 @param string com comando e argumentos e a proteina.*/
int interpretar(char *linha, proteina *p) {
    char comando[MAX_SIZE];
    char args[MAX_SIZE];
    int nargs,cmd = -1;
	nargs = sscanf(linha, "%s %[^\n]", comando, args);
	if(strcmp(comando,"sair")==0) cmd = 0;
	else if(strcmp(comando,"seq")==0) cmd = 1;
			else if(strcmp(comando,"coords")==0) cmd = 2;
					else if(strcmp(comando,"dobrar")==0) cmd = 3;
							else if(strcmp(comando,"validar")==0) cmd = 4;
									else if(strcmp(comando,"compactar")==0) cmd = 5;
											else if (strcmp(comando,"gravar")==0) cmd = 6;
													else if (strcmp(comando,"latex")==0) cmd = 7;
															else if(strcmp(comando,"energia")==0) cmd = 8;
	switch(nargs) {
		case 2:	switch(cmd){	
					case 1:	return	cmd_seq(args, p);
					case 2:	return cmd_coords(args, p);
					case 3:	return cmd_dobrar(args, p);
					case 6: return cmd_gravar(args, p);
					case 7: return cmd_latex(args, p);
					case 8: return cmd_energia(args, p);
					default:mensagem_de_erro(E_COMMAND);
							return -1;
				}
		case 1: switch(cmd){	
					case 1:	return cmd_seq(NULL, p);
					case 2:	return cmd_coords(NULL, p);
					case 3:	return cmd_dobrar(NULL, p);
					case 4: return cmd_validar(p);
					case 5:	return cmd_compactar(p);
					case 6: return cmd_gravar(NULL, p);
					case 7: return cmd_latex(NULL, p);
					case 8:	return cmd_energia(NULL, p);
					case 0:	return 0;
					default:mensagem_de_erro(E_COMMAND);
							return -1;
				}
		default:mensagem_de_erro(E_COMMAND);
				return -1;
	}
}

/**Guarda as coordenadas se forem válidas e retorna as coordenadas guardadas se forem invocadas sem argumentos
 @param recebe uma sequência de 'A' e 'B' e uma proteina.
 @return 1 se sequência guardada for válida. Retorna -1 (mensagem de erro) */
int cmd_seq(char *str, proteina *p){

	if(str!= NULL){
		char string_de_caracteres[MAX_SIZE], string_de_digitos[MAX_SIZE], string_descompactada[MAX_SIZE];
		int i, iterador_k, numero_dos_digitos, iterador_output=0, a=0, b=0,ver_frente, FLAG=0;
		
		
		for (i=0; str[i]!='\0'; i++){
			if(str[i] == '('){
				iterador_k=0;
				for (i=i+1; str[i]!=')'; i++){
					if (str[i] == 'A' || str[i] == 'B')
						string_de_caracteres[iterador_k++] = str[i];
					
					else{
						mensagem_de_erro(E_SEQ_INV);
						return -1;
					}
				}
				string_de_caracteres[iterador_k] = '\0';
				i++;
				if(!isdigit(str[i])){
					mensagem_de_erro(E_SEQ_INV);
					return -1;
				}
				iterador_k = 0;
				while (isdigit(str[i]))
					string_de_digitos[iterador_k++] = str[i++];
				
				string_de_digitos[iterador_k] = '\0';
				i--;
				numero_dos_digitos = atoi(string_de_digitos);

				for(a=0; a < numero_dos_digitos ; a++){
					for(b=0; string_de_caracteres[b]!= '\0'; b++)
						string_descompactada[iterador_output++] = string_de_caracteres[b];
				}

			}
			else if(str[i] == 'A' || str[i] == 'B'){
					iterador_k=0;
					string_de_caracteres[iterador_k] = str[i];
					string_de_caracteres[iterador_k+1] = '\0';
					ver_frente = i+1;
					if(str[i]=='\0')
						FLAG = 1;
					if(!isdigit(str[ver_frente])&& FLAG!=1){
						string_descompactada[iterador_output++] = str[i];
					}

					else{

						iterador_k = 0;
						while (isdigit(str[ver_frente]))
							string_de_digitos[iterador_k++] = str[ver_frente++];
						
						string_de_digitos[iterador_k] = '\0';
						i=ver_frente-1;
						numero_dos_digitos = atoi(string_de_digitos);

						for(a=0; a < numero_dos_digitos ; a++){
							for(b=0; string_de_caracteres[b]!= '\0'; b++)
								string_descompactada[iterador_output++] = string_de_caracteres[b];
						}
					}
				}
		
			else{
				mensagem_de_erro(E_SEQ_INV);
				return -1;
				}	
		}
		string_descompactada[iterador_output]= '\0';
		(*p).size.AsBs = strlen(string_descompactada);
		strcpy ((*p).AsBs,string_descompactada);
		(*p).size.coords = 0;
		(*p).esta_colocada = 'n';
		return 1;
	}
	else {
		if((*p).size.AsBs) {
			printf("%s\n", (*p).AsBs);
			return 1;
        } 
		else {
			mensagem_de_erro(E_NO_SEQ);
			return -1;
		}
	}
}


/**Guarda as coordenadas se forem válidas e retorna as coordenadas guardadas se forem invocadas sem argumentos.
 @param recebe uma sequência de coordenadas e a proteina.
 @return 1 se coordenadas guardadas forem válidas. Retorna -1 (mensagem de erro)*/
int cmd_coords(char *ag, proteina *p){
	if(ag!=NULL){
		if(numero_de_args_par(ag, p)){
			if((*p).size.test==(*p).size.AsBs){
				if(so_numeros(ag)){
						guarda_coords(ag, p);
						(*p).size.coords = (*p).size.test;
						(*p).esta_colocada = 'c';
						return 1;
				} else {
					mensagem_de_erro(E_COORDS);
					return -1;
				}
			} else {
				mensagem_de_erro(E_COORDS);
				return -1;
			}
		} else {
			mensagem_de_erro(E_COORDS);
			return -1;
		}
	} else {
		if((*p).size.coords==0){
			mensagem_de_erro(E_NAO_COLOC);
			return -1;
		} else {
			if((*p).esta_colocada=='c'){
				if((*p).size.coords==(*p).size.AsBs){
					imprime_coords(p);
					return 1;
				} else {
					mensagem_de_erro(E_COORDS);
					return -1;
				}
			} else {
				mensagem_de_erro(E_NAO_COLOC);
				return -1;
			}
		}
	}
}

/**Se receber argumentos dobrará conforme a sequência se for invocada sem argumentos dobrará tudo com 'F'.
@param recebe como argumentos (args) 'F', 'D' ou 'E' . Recebe também a proteina.
 @return 1 se dobrar a sequência. Retorna -1 (mensagem de erro)*/
int cmd_dobrar(char *args, proteina *p){
	char t[MAX_SIZE];
	t[0]='0';t[1]=' ';t[2]='0';t[3]='\0';
	if((*p).esta_colocada!='0'){
		if(args!=NULL){
			if((*p).size.AsBs!=1){
				if(F_ou_D_ou_E(args, p)){
					if((*p).size.dobras<(*p).size.AsBs)
						if((*p).size.dobras<((*p).size.AsBs-1)) return guarda_dobras_e_coordenadas(completa_Fs(args, p), p);
						else return guarda_dobras_e_coordenadas(args, p);
					else {
						mensagem_de_erro(E_ARGS);
						return -1;
					}
				} else {
					mensagem_de_erro(E_INVARGS);
					return -1;
				}
			} else {
				mensagem_de_erro(E_ARGS);
				return -1;
			}
		} else {
			(*p).size.dobras = 0;
			if((*p).size.AsBs==1){
				(*p).size.test=1;
				cmd_coords(t, p);
				return 1;
			} else return guarda_dobras_e_coordenadas(completa_Fs(args,p), p);
		}
	} else {
		mensagem_de_erro(E_NO_SEQ);
		return -1;
	}
}

/**Imprime SIM ou NAO.
@param Proteina.
@return 1 quando válida. Retorna -1 (mensagem de erro)*/
int cmd_validar(proteina *p){
	if((*p).esta_colocada == 'c'){
		if(coordenadas_ortogonais(p)){
			if(coordenadas_diferentes(p)){
				printf("SIM\n");
				return 1;
			} else {
				printf("NAO\n");
				return 1;
			}
		} else {
			printf("NAO\n");
			return 1;
		}
	} else {
		mensagem_de_erro(E_NAO_COLOC);
		return -1;
	}
}
/**Se anteriormente tiver sido introduzida uma proteina válida, compacta a sequência de 'A' e 'B' de forma a consumirem o menor número possível de caracteres.
@param Proteina.
@return 1 se compactar, -1 se houver algum erro. */
int cmd_compactar(proteina *p){
	if((*p).size.AsBs>0){
		compacta(p);
		imprime_compactado(p);
		return 1;
	} else {
		mensagem_de_erro(E_NO_SEQ);
		return -1;
	}
}

/**Grava ficheiro com sequência e coordenadas. 
@param recebe um argumento (nome do ficheiro) e a proteina.
@return 1 quando grava. Retorna -1 (mensagem de erro)**/

int cmd_gravar(char *nome_ficheiro, proteina *p) {
	int i = 0;
	FILE *f = NULL;
	if (nome_ficheiro==NULL){
		mensagem_de_erro(E_GRAVAR);
		return -1; 
	} else {
		if ((*p).size.AsBs==0) { 
			mensagem_de_erro(E_NO_SEQ);
			return -1;
		} else
			if ((*p).size.coords==0){
				mensagem_de_erro(E_NAO_COLOC);
				return -1;
			} else { 
				f = fopen(nome_ficheiro, "w");
				fprintf(f,"%s\n", (*p).AsBs);
				while(i < ((*p).size.coords-1)){
					fprintf(f,"(%d, %d) ",(*p).coordenadas[i].x,(*p).coordenadas[i].y);
					i++;
				}
				fprintf(f,"(%d, %d)\n",(*p).coordenadas[i].x,(*p).coordenadas[i].y);
			}
		fclose(f);
		return 1;
	}
}

/** Cria um ficheiro latex se tiver sequência e coordenadas válidas.  
 @param recebe um argumento (nome do ficheiro) e a proteina.
 @return 1 quando cria ficheiro. Retorna -1 (mensagem de erro)**/

int cmd_latex(char *nome_fich, proteina *p) {
	int i,minx,maxx,miny,maxy;
	FILE *f = NULL;
    if (nome_fich==NULL){
		mensagem_de_erro(E_GRAVAR);
		return -1; 
	} else
		if((*p).size.AsBs==0){ 
			mensagem_de_erro(E_NO_SEQ);
			return -1;
		} else
			if ((*p).size.coords==0){
				mensagem_de_erro(E_NAO_COLOC);
				return -1;
			} else {
				f = fopen(nome_fich, "w");
				minx= (*p).coordenadas[0].x;
				maxx= (*p).coordenadas[0].x;
				miny= (*p).coordenadas[0].y;
				maxy= (*p).coordenadas[0].y;
				for(i=1;i<(*p).size.AsBs;i++){
					if(((*p).coordenadas[i].x) < minx) minx= (*p).coordenadas[i].x;
					else 
						if(((*p).coordenadas[i].x)> maxx) maxx= (*p).coordenadas[i].x;
					if (((*p).coordenadas[i].y) < miny) miny= (*p).coordenadas[i].y;
					else 
						if (((*p).coordenadas[i].y) > maxy) maxy= (*p).coordenadas[i].y;
				}
				fprintf(f,"\\documentclass[a4paper]{article}\n");
				fprintf(f,"\\usepackage{tikz}\n");
				fprintf(f,"\\usetikzlibrary{arrows}\n");
				fprintf(f,"\\begin{document}\n");
				fprintf(f,"\\begin{center}\n");
				fprintf(f,"\\begin{tikzpicture}[axis/.style={very thick, ->, >=stealth'}]\n");
				fprintf(f,"\\draw[axis] (%d, %d) -- (%d, %d) node(xline)[right] {x};\n", minx - 1, miny - 1, maxx + 1, miny - 1);
				fprintf(f,"\\draw[axis] (%d, %d) -- (%d, %d) node(yline)[above] {y};\n", minx - 1, miny - 1, minx - 1, maxy + 1);
				fprintf(f,"\n");
				fprintf(f,"\\foreach \\x in {%d,...,%d} {\n\t",minx,maxx);
				fprintf(f,"\\draw[dashed] (\\x, %d) node[below]{\\x} -- (\\x, %d);\n}\n",miny - 1, maxy + 1);
				fprintf(f,"\n\\foreach \\y in {%d,...,%d} {\n\t",miny, maxy);
				fprintf(f,"\\draw[dashed] (%d, \\y) node[left]{\\y} -- (%d, \\y);\n}\n",minx - 1, maxx + 1);
				fprintf(f,"\n\\draw[very thick]\n");
				for (i=0;i< (*p).size.AsBs; i++)	{
					if (i>0) fprintf(f, " -- ");
						if ((*p).AsBs[i]== 'A') 
							fprintf(f,"(%d, %d) node[circle, draw, fill]{}",(*p).coordenadas[i].x,(*p).coordenadas[i].y);
						else 
							if ((*p).AsBs [i]== 'B')
								fprintf(f, "(%d, %d) node[circle, draw]{}",(*p).coordenadas[i].x,(*p).coordenadas[i].y);
				}
				fprintf(f,";\n\\end{tikzpicture}\n\\end{center}\n\\end{document}");
				fprintf(f,"\n");
				fclose(f);
				return 1;
			}
}

/**Calcula o valor da energia de uma dada sequência de 'A' e 'B', válida.
@param Nos argumentos (args) poderá ser invocada sem argumentos ou com 3 argumentos (nas devidas condições). Recebe também a proteina.
@return 1 caso calcule a energia e -1 caso ocorra algum erro. */
int cmd_energia(char *ag,proteina *p){
	char tail[MAX_SIZE];
	int e1,e2,e3,i,energia = 0;
	if((*p).size.AsBs>0){
		if((*p).size.coords>0){
			if(ag!=NULL){
				if(sscanf(ag,"%d %d %d %[^\n]",&e1,&e2,&e3,tail)==3){
					if(e1<0 && e2>=0 && e3>=0){
						for(i=3;i<(*p).size.coords;i++)
							energia += procura_vizinho(i, e1, e2, e3, p);
						printf("%d\n",energia);
						return 1;
					} else {
						mensagem_de_erro(E_INVARGS);
						return -1;
					}	
				} else {
					mensagem_de_erro(E_INVARGS);
					return -1;
				}
			} else {
				for(i=3;i<(*p).size.coords;i++)
					energia += procura_vizinho(i, -1, 0, 0, p);
				printf("%d\n",energia);
				return 1;
			}
		} else {
			mensagem_de_erro(E_NAO_COLOC);
			return -1;
		}
	} else {
		mensagem_de_erro(E_NO_SEQ);
		return -1;
	}
}
