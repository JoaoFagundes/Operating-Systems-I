#include <stdlib.h>

class Evento {
 private:
 	int momentoQueExecuta;

 	// inteiro que determina o tipo de evento:
 	/* 
		0 = Novo carro entrou na pista;
		1 = Semáforo mudou de estado;
		2 = Carro chegou em um semáforo;
		3 = Carrou trocou de pista.
 	*/
 	int tipoEvento;

 public:

 	Evento(int momentoQueExecuta_, int tipoEvento_) {
 		momentoQueExecuta = momentoQueExecuta_;
 		tipoEvento = tipoEvento;
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

 	int setTipoEvento(int tipo_) {
 		tipoEvento = tipo_;
 	}

 	int getMomentoQueExecuta() {
 		return momentoQueExecuta;
 	}


}