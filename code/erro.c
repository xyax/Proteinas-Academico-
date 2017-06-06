#include <stdio.h>
#include "erro.h" 

/**
* Reporta o erro escrevendo uma mensagem no standard error
* @param erro_num O numero do erro que vem da tabela de erros. Usar SEMPRE o define e nao o valor numerico para maior legibilidade.
*/
int mensagem_de_erro(erro erro_num) {
	char* erro[] =
	{
  		"Comando nao existe",
  		"Erro de argumentos a mais ou a menos",
  		"Ainda nao ha sequencia",
  		"Sequencia invalida",
  		"Coordenadas erradas",
  		"Sequencia ainda nao foi colocada",
  		"Nao se consegue gravar o ficheiro",
  		"Argumentos invalidos",
  		"Erro de alocacao de memoria"
	};
	(void) fprintf(stderr, "%s\n", erro[erro_num]);
	return -1 - erro_num;
}

