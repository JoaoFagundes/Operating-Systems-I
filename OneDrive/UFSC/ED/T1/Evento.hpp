#include <stdlib.h>

class Evento {
 private:
 	int segundoDeExecucao;
 	String tipo;

 public:

 	void processaEvento(Evento e) {	
 	}

 	void novoCarro(Carro carro) {
 		carro.getPistaAtual().getVelocidade();
 	}

 	void semaforoMudou() {

 	}

 	void carroChegouNoSemaforo(Pista proximaPista) {
 		if (proximaPista.isCheia())
 			fail
 		else

 	}

 	void carroTrocouDePista(Pista pistaAtual, Carro carro) {

 	}

 	String getTipo() {
 		return tipo;
 	}

 	String setTipo(String tipo_) {
 		tipo = tipo_;
 	}
}