#ifndef PISTA_H_
#define PISTA_H_
#include <stdlib.h>
#include <time.h>
#include "Carro.h"
#include "FilaEnc.hpp"

class Carro;

class Pista : private FilaEnc<Carro*> {
	Pista *pistasAdjacentes[3] = {};
	int velocidade, tamanho, maxCarros, espacoDisponivel;
	int fonte_tempoFixo, fonte_intervalo, fonte_tempoVariante;
	int carrosQueEntraram, carrosQueSairam;
	bool pistaCheia, fonte, sumidouro;
	int probabilidades[3];
 public:
 	Pista(int _velocidade, int _tamanho, bool _fonte, bool _sumidouro);

	int getVelocidade();

	int getCarrosQueEntraram();

	int getCarrosQueSairam();

	int getTamanho();

	Carro* retiraCarro();

	int calculaTempoDaPista();

	bool isFonte();
 
 	bool isSumidouro();

 	// Diz o de quanto em quanto tempo uma pista fonte tem que 
 	// criar um novo carro, com a variável "_tempoVariante"
 	// informando o intervalo.
 	void setTempoDeFonte(int _tempoFixo, int _tempoVariante);

 	bool cabeCarroNaPista(Carro *carro);

 	// Calcula o tempo que a pista fonte deve inserir um novo carr
 	// baseado nas suas variáveis fonte_tempoVariante, fonte_tempoFixo
 	// e fonte_intervalo.
 	int calculaTempoDeInserirCarro(int tempoAtual);
 
 	void adicionaCarro(Carro *carro);
};

#endif
