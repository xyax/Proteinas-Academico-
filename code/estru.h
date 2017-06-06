#ifndef ___ESTRUTURA___
#define ___ESTRUTURA___

#define MAX_SIZE 10000

typedef struct ponto {
	int x;
	int y;
} ponto;

typedef struct tamanho {
	unsigned short AsBs;
	unsigned short coords;
	unsigned short dobras;
	unsigned short test;
	unsigned short compact;
}tamanho;


typedef struct proteina {
	tamanho size;
	char esta_colocada;
	char AsBs[MAX_SIZE];
	ponto coordenadas[MAX_SIZE];
	char dobras[MAX_SIZE];
	char compact[MAX_SIZE];
	char volatil[MAX_SIZE];
} proteina;

#endif
