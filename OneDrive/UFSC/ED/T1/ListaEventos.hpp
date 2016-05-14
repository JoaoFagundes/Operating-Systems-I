#include "ListaEnc.hpp"

class ListaEventos : private ListaEnc<Evento> {
 private:
 	void adicionaEvento(Evento e) {
 		ListaEnc<Evento>::adicionaEmOrdem(e);
 	}

 	void processaEvento() {
 		Evento evento = ListaEnc<Evento>::retiraDoInicio();
 		
 	}

}