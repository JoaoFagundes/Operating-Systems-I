#include <stdlib.h>
#include <time.h>

class Clarro {
 private:
	int tamanho;
 
 public:

 	Carro() {
 		tamanho = calculaTamanho();
 	}

 	int calculaTamanho() {
 		srand(time(0));
 		return rand() % 5 + 1;
 	}
}