#include "ListaEnc.hpp"

class ListaEventos : private ListaEnc<Evento> {

 public:
 	ListaEventos();

 	void adicionaEvento(Evento e) {
 		ListaEnc<Evento>::adicionaEmOrdem(e);
 	}

 	Evento processaEvento() {
 		Evento evento = ListaEnc<Evento>::retiraDoInicio();
 		tempoDoEventoAtual = evento -> getMomentoQueExecuta();
 		return evento;
 	}

 	bool maior(Evento *evento1, Evento *evento2) const {
 		return evento1 -> getMomentoQueExecuta() > evento2 -> getMomentoQueExecuta();
 	}

}