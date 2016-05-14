#include <stdlib.h>
#include <time.h>

#include "Fila.hpp"
#include "Carro.hpp"
#include "Lista.hpp"

class Pista : Fila<Carro> {
 private:
	Pista pistasAdjacentes [10]; 
	int velocidade, tamanho, maxCarros, tamanhoDisponivel;
	bool pistaCheia, fonte, sumidouro;

 public:
 	Pista(int velocidade_, int tamanho_) {
 		velocidade = velocidade_;
 		tamanho = tamanho_;
 		tamanhoDisponivel = tamanho_;
 		maxCarros = (int) (tamanho_ / 5);
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
}