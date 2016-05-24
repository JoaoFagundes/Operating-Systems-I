#ifndef LISTAEVENTOS_HPP_
#define LISTAEVENTOS_HPP_
#include "ListaEnc.hpp"
#include "Evento.hpp"

class ListaEventos : private ListaEnc<Evento*> {
 public:
 	ListaEventos();

 	void adicionaEvento(Evento *e) {
 		ListaEnc<Evento*>::adicionaEmOrdem(e);
 	}

 	bool maior(Evento *evento1, Evento *evento2) const {
 		return evento1 -> getMomentoQueExecuta() > evento2 -> getMomentoQueExecuta();
 	}

	int getSize() {
		return ListaEnc<Evento*>::getSize();
	}

	Evento* retiraEspecifico(Evento *evento) {
		return ListaEnc<Evento*>::retiraEspecifico(evento);
	}

	Evento* mostra(int pos) {
		return ListaEnc<Evento*>::mostra(pos);
	}

};

#endif