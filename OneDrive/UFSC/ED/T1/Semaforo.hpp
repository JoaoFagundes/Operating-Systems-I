#include "Pista.hpp"

class Semaforo {
 private:
	Lista<Pista> *pistasAferentes, *pistaEferentes;
	bool aberto;
 public:
 	Semaforo(bool aberto_) {
 		aberto = aberto_;
 	}

 	bool isAberto() {
 		return aberto;
 	}

 	void mudaEstado() {
 		aberto = !aberto;
 	}
 
 	Pista proximaPista(Pista pistaAtual) {
 		srand(time(0));
 		int random = rand() % 10;
 		return pistaAtual -> getProximaPista(random);
 	}
}