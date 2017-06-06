#ifndef ___ERROS_H___
#define ___ERROS_H___

typedef enum {E_COMMAND, E_ARGS, E_NO_SEQ, E_SEQ_INV, E_COORDS, E_NAO_COLOC, E_GRAVAR, E_INVARGS, E_MEM} erro;
int mensagem_de_erro(erro erro_num);

#endif
