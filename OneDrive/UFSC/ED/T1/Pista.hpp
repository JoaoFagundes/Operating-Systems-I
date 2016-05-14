#include <stdlib.h>
#include <time.h>

#include "Fila.hpp"
#include "Carro.hpp"
#include "Lista.hpp"

class Pista : private Fila<Carro> {
 private:
	Pista pistasAdjacentes [3]; 
	int velocidade, tamanho, maxCarros, tamanhoDisponivel;
	bool pistaCheia, fonte, sumidouro;
	int probabilidades[3];
 public:
 		// inicializa a pista com os atributos necessários.
 		// probabilidade[x] corresponde a probabilidade de ir pra pistaAdjacente[x]
 	Pista(int velocidade_, int tamanho_, int probabilidades[3]_, Pista[] pistas[3]) {
 		velocidade = velocidade_;
 		tamanho = tamanho_;
 		tamanhoDisponivel = tamanho_;
 		probabilidades = probabilidades_;
 		pistasAdjacentes = pistas;
 		maxCarros = (int) (tamanho_ / 5);
 	}

	Pista getProximaPista() {
		int randNum = (rand() % 100);
		switch (randNum) {
			case (randNum < probabilidades[0]) :
				return pistasAdjacentes[0]
				break;
			case (randNum >= probabilidades[0] && randNum < probabilidades[1]) :
				return pistasAdjacentes[1]
				break;
			case (randNum >= probabilidades[1] && randNum < probabilidades[2]) :
				return pistasAdjacentes[2]
		}
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
}