#include "Carro.h"
#include <stdio.h>
#include <time.h>
#include <cstdlib>

Carro::Carro(Pista *_pistaAtual) {
	tamanho = calculaTamanho();
	pistaAtual = _pistaAtual;
}

Carro::~Carro() {
	delete pistaAtual;
}

int Carro::calculaTamanho() {
	//Inicia o seed de rand() com uma timestamp
	srand(time(0));
	// Acha um número randômico entre 0 e 4, soma 2 para
	// chegar no intervalo desejado (de 2 a 6) e soma 3
	// para representar a distância entre um carro e outro.
	return (rand() % 5 + 2) + 3;
}
int Carro::getTamanho() {
	return tamanho;
}
void Carro::setPistaAtual(Pista *_pistaAtual) {
	pistaAtual = _pistaAtual;
}

Pista* Carro::getPistaAtual() {
	return pistaAtual;
}
