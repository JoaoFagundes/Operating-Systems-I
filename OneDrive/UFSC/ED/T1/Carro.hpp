#ifndef CARRO_HPP_
#define CARRO_HPP_
#include <stdlib.h>
#include <time.h>

class Carro {
 private:
	int tamanho;
	Pista *pistaAtual;
 
 public:

 	Carro(Pista *_pistaAtual) {
 		tamanho = calculaTamanho();
 		pistaAtual = _pistaAtual;
 	}

 	~Carro() {
 		delete pistaAtual;
 	}

 	int calculaTamanho() {
 		//Inicia o seed de rand() com uma timestamp
   		srand(time(0));
		// Acha um número randômico entre 0 e 4, soma 2 para
 		// chegar no intervalo desejado (de 2 a 6) e soma 3
 		// para representar a distância entre um carro e outro.
 		return (rand() % 5 + 2) + 3;
 	}
 	int getTamanho() {
 			return tamanho;
   	}
 	void setPistaAtual(Pista *_pistaAtual) {
 		pistaAtual = _pistaAtual;
 	}

 	Pista* getPistaAtual() {
 		return pistaAtual;
 	}
};

#endif
