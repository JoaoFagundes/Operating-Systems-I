#include <stdlib.h>
#include "ListaEnc.hpp"

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
		3 = Carro chegou no fim de pista sumidouro
 	*/
 	int tipoEvento;

 public:

 	Evento(int _momentoQueExecuta, int _tipoEvento, Carro *_carro, Semaforo *_semaforo) {
 		momentoQueExecuta = _momentoQueExecuta;
 		tipoEvento = _tipoEvento;
 		processaEvento();
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

 	Semaforo getSemaforo() {
 		return semaforo;
 	}

}