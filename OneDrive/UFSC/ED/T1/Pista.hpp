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
 	Pista(int velocidade_, int tamanho_, int probabilidades_[3], Pista[] pistas[3], bool fonte_, bool sumidouro_) {
		velocidade = _velocidade;
		tamanho = _tamanho;
		espacoDisponivel = _tamanho;
		fonte = fonte_;
		sumidouro = sumidouro_;
		maxCarros = (int) (_tamanho / 5);
		pistasAdjacentes = pistas;
		probabilidades = probabilidades_;
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
	bool isFonte() {
 		return fonte;
 	}
 
 	bool isSumidouro() {
 		return sumidouro;
 	}
 
 	bool cabeCarroNaPista(Carro *carro) {
 		if (espacoDisponivel >= carro.getTamanho())
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