#include <stdlib.h>
#include <time.h>

#include "Fila.hpp"
#include "Carro.hpp"
#include "Lista.hpp"

class Pista : private FilaEnc<Carro> {
 private:
	Pista pistasAdjacentes[3]; 
	int velocidade, tamanho, maxCarros, espacoDisponivel;
	int fonte_tempoFixo, fonte_intervalo, fonte_tempoVariante;
	bool pistaCheia, fonte, sumidouro;
	int probabilidades[3];
 public:
 	Pista(int _velocidade, int _tamanho, bool _fonte, bool _sumidouro) {
		velocidade = _velocidade;
		tamanho = _tamanho;
		espacoDisponivel = _tamanho;
		fonte = _fonte;
		sumidouro = _sumidouro;
		maxCarros = (int) (_tamanho / 5);
		pistasAdjacentes = pistas;
		probabilidades = _probabilidades;
 	}

	int getVelocidade() {
		return velocidade;
	}

	int getTamanho() {
		return tamanho;
	}

	int calculaTempoDaPista() {
		return (int) (tamanho / (velocidade / 3,6));
	}
	bool isFonte() {
 		return fonte;
 	}
 
 	bool isSumidouro() {
 		return sumidouro;
 	}

 	// Diz o de quanto em quanto tempo uma pista fonte tem que 
 	// criar um novo carro, com a variável "_tempoVariante"
 	// informando o intervalo.
 	void setTempoDeFonte(int _tempoFixo, int _tempoVariante) {
 		fonte_tempoFixo = _tempoFixo;
 		fonte_tempoVariante = _tempoVariante;
 		fonte_intervalo =  (2 * _tempoVariante) + 1;
 	}
 
 	bool cabeCarroNaPista(Carro *carro) {
 		if (espacoDisponivel >= carro -> getTamanho())
 			return true;
 		else
 			return false;
 	}

 	// Calcula o tempo que a pista fonte deve inserir um novo carr
 	// baseado nas suas variáveis fonte_tempoVariante, fonte_tempoFixo
 	// e fonte_intervalo.
 	int calculaTempoDeInserirCarro(int tempoAtual) {
 		srand(time(0));
 		// Acha um número randômico dentro do intervalo proposto e soma
 		// ao menor valor do intervalo.
 		int tempoDeExecucao = ( (rand() % fonte_intervalo) + (fonte_tempoFixo - fonte_tempoVariante));

 		// Soma o resultado da expressão anterior com o tempo atual do sistema
 		// para descobrir o real tempo de execução desse evento e o retorna.
 		return tempoDeExecucao + tempoAtual;
 	}
 
 	void adicionaCarro(Carro *carro) {
 		espacoDisponivel -= carro.getTamanho();
 		FilaEnc<Carro>::inclui(*carro);
 		Controle::adicionaCarrosQueEntraram();
 	}
 
 	Carro retiraCarro() {
 		Controle::adicionaCarrosQueSairam();
 		return FilaEnc<Carro>::retira();
  	}
}