#include <stdlib.h>
#ifndef SEMAFORO_HPP_
#define SEMAFORO_HPP_
#include "Pista.hpp"
#include "ExcecaoSinalFechado.hpp"

class Semaforo {
 private:
	Pista *pistaAtual;
	Pista *pistasDestino;
	int *probabilidades;
	bool aberto;
 public:
 	Semaforo(bool _aberto, Pista *_pistaAtual) {
 		pistaAtual = _pistaAtual;
 		aberto = _aberto;
 	}

 	void setProbabilidades(Pista pistas[3], int _probabilidades[3]) {
 		probabilidades = _probabilidades;
 		pistasDestino = pistas;
 	}

 	Pista* getProximaPista() {
 		srand(time(0));
		int randNum = (rand() % 100);
		if (randNum < probabilidades[0])
			return &pistasDestino[0];
		else if (randNum < (probabilidades[0] + probabilidades[1]))
			return &pistasDestino[1];
		else
			return &pistasDestino[2];
	}

	void trocaCarroDePista(Pista *proximaPista, Carro *carro) {
		if (!aberto)
			throw ExcecaoSinalFechado();
		carro -> getPistaAtual() -> retiraCarro();
		proximaPista -> adicionaCarro(carro);
	}

 	bool isAberto() {
 		return aberto;
 	}

 	Pista* getPistaAtual() {
 		return pistaAtual;
 	}

 	void mudaEstado() {
 		aberto = !aberto;
 	}

 	int calculaTrocaDeEstado(int _tempoAtual, int _tempoDeSemaforo) {
 		return _tempoAtual + _tempoDeSemaforo;
 	}
};

#endif