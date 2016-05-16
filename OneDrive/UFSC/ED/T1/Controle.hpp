#include "ListaCirc.hpp"
#include "ListaEnc.hpp"
#include "ListaEventos.hpp"
#include "Semaforo.hpp"
#include "Pista.hpp"
#include "Carro.hpp"
#include "ExcecaoSinalVermelho.hpp"
#include "Evento.hpp"
#include <stdlib.h>
#include <iostream>

class Controle {
 private: 
 	static int carrosQueEntraram;
 	static int carrosQueSairam;
 	ListaCirc(*Semaforo) *s1, *s2;
 	ListaEnc(*Pista) *listaDePistas;
 	ListaEventos *listaDeEventos;
 	int tempoDeSimulacao, tempoSemaforo, tempoAtualDoSistema;

 public:
 	Controle() {

 	}
 	Controle(int _tempoDeSimulacao, int _tempoSemaforo) {
 		tempoDeSimulacao = _tempoDeSimulacao;
 		tempoSemaforo = _tempoSemaforo;
 		tempoAtualDoSistema = 0;
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

 		// Define as probabilidades de inserção de carros das pistas que são fontes
 		n1Sul   -> setTempoDeFonte(20, 5);
 		n2Sul   -> setTempoDeFonte(20, 5);
 		s1Norte -> setTempoDeFonte(30, 7);
 		s2Norte -> setTempoDeFonte(30, 7);
 		o1Leste -> setTempoDeFonte(10, 2);
 		l1Oeste -> setTempoDeFonte(10, 2);

 		// Cria semáforos do primeiro cruzamento
 		Semaforo *s1_o1Leste = new Semaforo(true , o1Leste);
 		Semaforo *s1_n1Sul   = new Semaforo(false, n1Sul  );
 		Semaforo *s1_s1Norte = new Semaforo(false, s1Norte);
 		Semaforo *s1_c1Oeste = new Semaforo(false, c1Oeste);
 		s1 -> adiciona(s1_o1Leste);
 		s1 -> adiciona(s1_n1Sul  );
 		s1 -> adiciona(s1_s1Norte);
 		s1 -> adiciona(s1_c1Oeste);

 		// Cria semáforos do segundo cruzamento
 		Semaforo *s2_c1Leste = new Semaforo(true , c1Leste);
 		Semaforo *s2_n2Sul   = new Semaforo(false, n2Sul  );
 		Semaforo *s2_s2Norte = new Semaforo(false, s2Norte);
 		Semaforo *s2_l1Oeste = new Semaforo(false, l1Oeste);
 		s2 -> adiciona(s2_c1Leste);
 		s2 -> adiciona(s2_n2Sul  );
 		s2 -> adiciona(s2_s2Norte);
 		s2 -> adiciona(s2_l1Oeste);

 		// Inicializa as probabilidades dos semáforos
 		s1_o1Leste -> setProbabilidades({c1Leste, n1Norte, s1Sul}, {80, 10, 10});
 		s1_n1Sul -> setProbabilidades({c1Leste, o1Oeste, s1Sul}, {80, 10, 10});
 		s1_s1Norte -> setProbabilidades({c1Leste, n1Norte, o1Oeste}, {80, 10, 10});
 		s1_c1Oeste -> setProbabilidades({o1Oeste, n1Norte, s1Sul}, {40, 30, 30});
 		s2_c1Leste -> setProbabilidades({l1Leste, n2Norte, s2Sul}, {40, 30, 30});
 		s2_n2Sul -> setProbabilidades({l1Leste, c1Oeste, s2Sul}, {40, 30, 30});
 		s2_s2Norte -> setProbabilidades({l1Leste, s2Sul, c1Oeste}, {40, 30, 30});
 		s2_l1Oeste -> setProbabilidades({n2Norte, c1Leste, s2Sul}, {40, 30, 30});
 	}

 	void inicializaSimulacao() {
 		create_insereCarros();
 		create_semaforosMudamDeEstado();
 		create_carrosChegamEmSemaforo();
 		processaEvento();
 	}

 	// MÉTODOS DE CRIAÇÃO:
 	// Métodos que possuem "create_" no início indicam que estão explicitamente
 	// criando eventos.
 	void create_insereCarros() {
 		int tempoAtualDoMetodo, tempoEvento;
 		int i;
 		// POSSÍVEL ERRO AQUI NO 0.
 		for (i = 0; i < listaDePistas -> getSize(); i++) {
 			if (listaDePistas -> mostra(i) -> isFonte()) {
 				Pista *pista = listaDePistas -> mostra(i);
 				tempoAtualDoMetodo = tempoAtualDoSistema;
 				// Enquanto o contador de tempo do método for menor
 				// que o tempo determinado para simulação, o laço
 				// deve continuar criando eventos de inserção de carros.
 				while (tempoAtualDoMetodo < tempoDeSimulacao) {
 					tempoEvento = pista -> calculaTempoDeInserirCarro(tempoAtualDoMetodo);
 					if (tempoEvento <= tempoDeSimulacao) {
 						Evento *evento = new Evento(tempoEvento, 0, new Carro(pista), NULL);
 						listaDeEventos -> adicionaEvento(evento);
 						tempoAtualDoMetodo = tempoEvento;
 					}
 				}
 			}
 		}
 	}

 	void create_semaforosMudamDeEstado() {
 		int tempoAtualDoMetodo, tempoEvento;
 		int i;
 		// POSSÍVEL ERRO AQUI NO 0.
 		for (i = 0; i < s1 -> getSize(); i++) {
 			tempoAtualDoMetodo = tempoAtualDoSistema;
 			while (tempoAtualDoMetodo < tempoAtualDoSistema) {
 				Semaforo *semaforoAtual1 = s1 -> mostra(i);
 				Semaforo *semaforoAtual2 = s2 -> mostra(i);
 				tempoEvento = semaforoAtual1 -> calculaTrocaDeEstado(tempoAtualDoMetodo, tempoSemaforo);
 				if (tempoEvento <= tempoDeSimulacao) {
 					Evento *atual1Muda = new Evento(tempoEvento, 1, NULL, semaforoAtual1);
 					Evento *atual2Muda = new Evento(tempoEvento, 1, NULL, semaforoAtual2);
 					Evento *proximo1Muda = new Evento(tempoEvento + 1, 1, NULL, s1 -> mostra(i + 1));
 					Evento *proximo2Muda = new Evento(tempoEvento + 1, 1, NULL, s2 -> mostra(i + 1));
 					listaDeEventos -> adicionaEvento(atual1Muda);
 					listaDeEventos -> adicionaEvento(atual2Muda);
 					listaDeEventos -> adicionaEvento(proximo1Muda);
 					listaDeEventos -> adicionaEvento(proximo2Muda);
 				}
 				tempoAtualDoMetodo = tempoEvento;
 			}
 		}
 	}

 	void create_carrosChegamEmSemaforo() {
 		int i, tempoQueChegou;
 		// POSSÍVEL ERRO NO 0.
 		for (i = 0; i < listaDeEventos -> getSize(); i++) {
 			if (listaDeEventos -> mostra(i) -> getTipoEvento() == 0) {
 				Evento e = listaDeEventos -> mostra(i);
 				tempoQueChegou = (e -> getCarro() -> getPistaAtual() -> calculaTempoDaPista()) + e -> getMomentoQueExecuta();
 				if (tempoQueChegou <= tempoDeSimulacao) {
 					Carro *carro = e -> getCarro();
 					Evento *evento = new Evento(tempoQueChegou, 2, carro, achaSemaforo(carro -> getPistaAtual()));
 					listaDeEventos -> adicionaEvento(evento);
 				}
 			}
 		}
 	}

 	// MÉTODOS DE EXECUÇÃO:
 	// Esses métodos executam os eventos e implicitamente criam novos eventos.

 	void processaEvento() {
 		int i, tempoAtualDoMetodo;
 		for (i = 0; i < listaDeEventos -> getSize(); i++) {
 			Evento evento = listaDeEventos -> mostra(i);
 			switch (evento -> getTipoEvento()) {
 				case 0:
 					Carro *carro = evento -> getCarro();
 					Pista *pista = carro -> getPistaAtual();
 					if (pista -> cabeCarroNaPista(carro))
 						pista -> adicionaCarro(carro);
 					tempoAtualDoMetodo = evento -> getMomentoQueExecuta();
 					break;
 				case 1:
 					Semaforo *semaforo = evento -> getSemaforo();
 					semaforo -> mudaEstado();
 					tempoAtualDoMetodo = evento -> getMomentoQueExecuta();
 					break;
 				case 2:
 					carroChegouEmSemaforo(evento);
 					tempoAtualDoMetodo = evento -> getMomentoQueExecuta();
 					break;
 				case 3:
 					Carro *carro = evento -> getCarro();
 					Pista *pistaAtual = carro -> getPistaAtual();
 					pistaAtual -> retiraCarro();
 					tempoAtualDoMetodo = evento -> getMomentoQueExecuta();
 					break;
 			}
 			listaDeEventos -> retiraEspecifico(evento);
 		}

 		imprimeResultadoDaSimulacao();

 	}

 	void carroChegouEmSemaforo(Evento *evento) {
 		int tempoQueOSemaforoAbre;
 		int tempoDoEvento = evento -> getMomentoQueExecuta();
 		Semaforo *semaforo = evento -> getSemaforo();
 		Pista *proximaPista = semaforo -> getProximaPista();
 		Evento *novoEvento;
 		try {
 			if (proximaPista -> cabeCarroNaPista(evento -> getCarro())) {
 				semaforo -> trocaCarroDePista(proximaPista, evento -> getCarro());
 				carroEntrouEmNovaPista(evento -> getCarro(), tempoDoEvento);
 			} else { 
 				novoEvento = new Evento(tempoDoEvento + 2, 2, evento -> getCarro(), semaforo);	
 			}
 		} catch (exception& e) {
 			tempoQueOSemaforoAbre = achaAberturaDeSemaforo(tempoDoEvento, semaforo);
 			novoEvento = new Evento(tempoQueOSemaforoAbre + 1, 2, evento -> getCarro(), semaforo);
 		}

 		listaDeEventos -> adicionaEvento(novoEvento);
 	}

 	void carroEntrouEmNovaPista(Carro *carro, int tempoAtual) {
 		Evento *novoEvento;
 		Pista *pistaAtual = carro -> getPistaAtual();
 		int tempoDePista = pistaAtual -> calculaTempoDaPista()
 		if (pistaAtual -> isSumidouro())
 			novoEvento = new Evento(tempoAtual + tempoDePista, 3, carro, NULL);
 		else
 			novoEvento = new Evento(tempoAtual + tempoDePista, 2, carro, achaSemaforo(pistaAtual));
 		
 		listaDeEventos -> adicionaEvento(novoEvento);
 	}

 	void imprimeResultadoDaSimulacao() {
 		printf("Número de carros que entraram no sistema: %d.\n", carrosQueEntraram);
 		printf("Número de carros que saíram do sistema: %d.\n", carrosQueSairam);
 	}

 	Semaforo achaSemaforo(Pista *pista) {
 		int i;
 		for (i = 0; i < s1 -> getSize(); i++) {
 			Semaforo *semaforo1 = s1 -> mostra(i);
 			Semaforo *semaforo2 = s2 -> mostra(i);
 			if (semaforo1 -> getPistaAtual() == pista)
 				return semaforo1;
 			else if (semaforo2 -> getPistaAtual() == pista)
 				return semaforo2;
 		}
 	}

 	int achaAberturaDeSemaforo(int tempoAtual, Semaforo *semaforo) {
 		int i;
 		for (i = 0; i < listaDeEventos -> getSize(); i++) {
 			Evento *evento = listaDeEventos -> mostra(i);
 			if (evento -> getTipoEvento() == 1 && evento -> getMomentoQueExecuta >= tempoAtual
 				&& semaforo == evento -> getSemaforo()) {
 				return evento -> getMomentoQueExecuta();
 			}
 		}
 	}

 	void adicionaCarrosQueEntraram() {
 		carrosQueEntraram++;
 	}

 	int getCarrosQueEntraram() {
 		return carrosQueEntraram;
 	}

 	void adicionaCarrosQueSairam() {
 		carrosQueSairam++;
 	}

 	int getCarrosQueSairam() {
 		return carrosQueSairam;
 	}

}	