#include <stdlib.h>

class Evento {
 private:
 	int momentoQueExecuta;
 	Carro *carro;
 	Semaforo *semaforo;
 	// inteiro que determina o tipo de evento:
 	/* 
		0 = Novo carro entrou na pista;
		1 = Semáforo mudou de estado;
		2 = Carro chegou em um semáforo;
		3 = Carro trocou de pista.
 	*/
 	int tipoEvento;

 public:

 	Evento(int _momentoQueExecuta, int _tipoEvento, Carro *_carro, Semaforo *_semaforo) {
 		momentoQueExecuta = _momentoQueExecuta;
 		tipoEvento = _tipoEvento;
 		processaEvento();
 	}

 	void processaEvento() {	
 		switch (tipoEvento) {
 			case 0:

 			case 1:

 			case 2:

 			case 3: 
 		}
 	}

 	String getTipoEvento() {
 		return tipo;
 	}

 	int setTipoEvento(int _tipo) {
 		tipoEvento = _tipo;
 	}

 	int getMomentoQueExecuta() {
 		return momentoQueExecuta;
 	}

 	Carro getCarro() {
 		return carro;
 	}

}