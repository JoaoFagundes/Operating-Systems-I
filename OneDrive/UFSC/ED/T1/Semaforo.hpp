#include "Pista.hpp"

class Semaforo {
 private:
	Lista<Pista> *pistasAferentes, *pistaEferentes;
 public:
 	Semaforo() {
 		
 	}

 	Pista proximaPista(Pista pistaAtual) {
 		srand(time(0));
 		int random = rand() % 10;
 		return pistaAtual.getProximaPista(random);
 	}
}