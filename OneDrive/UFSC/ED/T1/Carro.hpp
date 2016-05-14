#include <stdlib.h>
#include <time.h>

class Clarro {
 private:
	int tamanho;
	Pista pistaAtual;
 
 public:

 	Carro(Pista pistaAtual_) {
 		tamanho = calculaTamanho();
 		pistaAtual = pistaAtual_;
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

 	void setPistaAtual(pistaAtual_) {
 		pistaAtual = pistaAtual_;
 	}

 	Pista getPistaAtual() {
 		return pistaAtual;
 	}
}