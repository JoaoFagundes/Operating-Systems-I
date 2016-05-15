#include <stdlib.h>
#include <time.h>

#include "Fila.hpp"
#include "Carro.hpp"
#include "Lista.hpp"

class Pista : private FilaEnc<Carro> {
 private:
	Pista pistasAdjacentes[3]; 
	int velocidade, tamanho, maxCarros, espacoDisponivel;
	bool pistaCheia, fonte, sumidouro;
	int probabilidades[3];
 public:
 		// inicializa a pista com os atributos necessários.
 		// probabilidade[x] corresponde a probabilidade de ir pra pistaAdjacente[x]
 	Pista(int _velocidade, int _tamanho, int _probabilidades[3], Pista[] pistas[3], bool _fonte, bool _sumidouro) {
		velocidade = _velocidade;
		tamanho = _tamanho;
		espacoDisponivel = _tamanho;
		fonte = _fonte;
		sumidouro = _sumidouro;
		maxCarros = (int) (_tamanho / 5);
		pistasAdjacentes = pistas;
		probabilidades = _probabilidades;
 	}

	Pista getProximaPista() {
		int randNum = (rand() % 100);
		if (randNum < probabilidades[0]) 
			return pistasAdjacentes[0]
		else if (randNum < (probabilidades[0] + probabilidades[1]))
			return pistasAdjacentes[1]
		else 
			return pistasAdjacentes[2]
	}

	int getVelocidade() {
		return velocidade;
	}

	int getTamanho() {
		return tamanho;
	}

	int calculaTempoDaPista() {
		return (int) (tamanho / velocidade);
	}
	bool isFonte() {
 		return fonte;
 	}
 
 	bool isSumidouro() {
 		return sumidouro;
 	}
 
 	bool cabeCarroNaPista(Carro *carro) {
 		if (espacoDisponivel >= carro -> getTamanho())
 			return true;
 		else
 			return false;
 	}
 
  	int calculaTempoDaPista() {
 		return (int) (tamanho / velocidade);, 
 	}
 
 	void adicionaCarro(Carro *carro) {
 		espacoDisponivel -= carro.getTamanho();
 		FilaEnc<Carro>::inclui(*carro);
 	}
 
 	Carro retiraCarro() {
 		return FilaEnc<Carro>::retira();
  	}
}