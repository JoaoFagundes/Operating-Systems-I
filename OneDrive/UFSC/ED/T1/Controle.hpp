#include "ListaCirc.hpp"
#include "ListaEnc.hpp"

class Controle {
 private: 
 	ListaCirc(*Semaforo) *s1, *s2;
 	ListaEnc(*Pista) *listaDePistas;
 	ListaEventos *listaEventos;
 	int tempoDeSimulacao, tempoSemaforo;

 public:
 	Controle(int tempoDeSimulacao_, int tempoSemaforo_) {
 		tempoDeSimulacao = tempoDeSimulacao_;
 		tempoSemaforo = tempoSemaforo_;
 		criaSistema();
 	}

 	void criaSistema() {
 		//Cria as 14 pistas e as adiciona na lista de pistas
 		Pista *n1Sul   = new Pista(60, 500 , true , false);
 		Pista *n1Norte = new Pista(60, 500 , false, true ); 		
 		Pista *n2Sul   = new Pista(40, 500 , true , false);
 		Pista *n2Norte = new Pista(40, 500 , false, true );
 		Pista *s1Sul   = new Pista(60, 500 , false, true );
 		Pista *s1Norte = new Pista(60, 500 , true , false);
 		Pista *s2Sul   = new Pista(40, 500 , false, true );
 		Pista *s2Norte = new Pista(40, 500 , true , false);
 		Pista *o1Oeste = new Pista(80, 2000, false, true );
 		Pista *o1Leste = new Pista(80, 2000, true , false);
 		Pista *c1Oeste = new Pista(60, 300 , false, false);
 		Pista *c1Leste = new Pista(60, 300 , false, false);
 		Pista *l1Oeste = new Pista(30, 400 , true , false);
 		Pista *l1Leste = new Pista(30, 400 , false, true );

 		listaDePistas -> adiciona(n1Sul  );
 		listaDePistas -> adiciona(n1Norte);
 		listaDePistas -> adiciona(n2Sul  );
 		listaDePistas -> adiciona(n2Norte);
 		listaDePistas -> adiciona(s1Sul  );
 		listaDePistas -> adiciona(s1Norte);
 		listaDePistas -> adiciona(s2Sul	 );
 		listaDePistas -> adiciona(s2Norte);
 		listaDePistas -> adiciona(o1Oeste);
 		listaDePistas -> adiciona(o1Leste);
 		listaDePistas -> adiciona(c1Oeste);
 		listaDePistas -> adiciona(c1Leste);
 		listaDePistas -> adiciona(l1Oeste);
 		listaDePistas -> adiciona(l1Leste);

 		// Cria do primeiro cruzamento
 		Semaforo *s1_o1Leste = new Semaforo(true);
 		Semaforo *s1_n1Sul = new Semaforo(false);
 		Semaforo *s1_s1Norte = new Semaforo(false);
 		Semaforo *s1_c1Oeste = new Semaforo(false);
 		s1 -> adiciona(s1_o1Leste);
 		s1 -> adiciona(s1_n1Sul);
 		s1 -> adiciona(s1_s1Norte);
 		s1 -> adiciona(s1_c1Oeste);
 	}

}	