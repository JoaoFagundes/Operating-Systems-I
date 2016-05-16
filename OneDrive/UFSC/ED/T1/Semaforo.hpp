#include "Pista.hpp"

class Semaforo {
 private:
	Pista *pistaAtual;
	Pista *pistasDestino;
	int *probabilidades;
	bool aberto;
 public:
 	Semaforo(Pista *_pistaAtual, bool aberto_) {
 		pistaAtual = _pistaAtual;
 		aberto = aberto_;
 	}

 	void setProbabilidades(Pista[] pistas[3], int _probabilidades[3]) {
 		probabilidades = _probabilidades;
 		pistasDestino = pistas;
 	}

 	Pista getProximaPista() {
 		srand(time(0));
		int randNum = (rand() % 100);
		if (randNum < probabilidades[0]) 
			return pistasDestino[0]
		else if (randNum < (probabilidades[0] + probabilidades[1]))
			return pistasDestino[1]
		else 
			return pistasDestino[2]
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