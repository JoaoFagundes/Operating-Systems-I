#ifndef CARRO_H_
#define CARRO_H_
#include "Pista.h"

class Pista;

class Carro {
	int tamanho;
	Pista *pistaAtual;
 
 public:

 	Carro(Pista *_pistaAtual);

 	~Carro();

 	int calculaTamanho();

 	int getTamanho();

 	void setPistaAtual(Pista *_pistaAtual);

 	Pista* getPistaAtual();
};

#endif
