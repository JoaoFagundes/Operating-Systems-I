#include <stdlib.h>
#include <time.h>

#include "Fila.hpp"
#include "Carro.hpp"
#include "Lista.hpp"

class Pista : private FilaEnc<Carro> {
 private:
	Pista pistasAdjacentes [10]; 
	int velocidade, tamanho, maxCarros, espacoDisponivel;
	bool pistaCheia, fonte, sumidouro;

 public:
 	Pista(int _velocidade, int _tamanho, bool fonte_, bool sumidouro_) {
 		velocidade = _velocidade;
 		tamanho = _tamanho;
 		espacoDisponivel = _tamanho;
 		fonte = fonte_;
 		sumidouro = sumidouro_;
 		maxCarros = (int) (_tamanho / 5);
 	}

 	void setPistasAdjacentes(int[] probabilidade, Pista[] pistas) {
 		int i = 0;

 		for (i; i < 10; i++) {
 			if (i < probabilidade[0])
 				pistasAdjacentes[i] = pistas[0];
 			else if (i < probabilidade[0] + probabilidade[1])
 				pistasAdjacentes[i] = pistas[1];
 			else
 				pistasAdjacentes[i] = pistas[2];
 		}
	}

	Pista getProximaPista(int randomProximaPista) {
		return pistasAdjacentes[randomProximaPista];
	}

	int getVelocidade() {
		return velocidade;
	}

	int getTamanho() {
		return tamanho;
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