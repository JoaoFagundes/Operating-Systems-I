#include <stdlib.h>
#include <time.h>

class Carro {
 private:
	int tamanho;
	Pista pistaAtual;
 
 public:

 	Carro(Pista pistaAtual_) {
 		tamanho = calculaTamanho();
 		pistaAtual = pistaAtual_;
 	}

 	int calculaTamanho() {
 		srand(time(0));
 		return rand() % 5 + 1;
 	}

 	void setPistaAtual(pistaAtual_) {
 		pistaAtual = pistaAtual_;
 	}

 	Pista getPistaAtual() {
 		return pistaAtual;
 	}
}