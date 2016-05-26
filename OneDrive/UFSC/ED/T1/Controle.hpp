#ifndef CONTROLE_HPP_
#define CONTROLE_HPP_
#include "ListaCirc.hpp"
#include "ListaEnc.hpp"
#include "ListaEventos.hpp"
#include "Semaforo.hpp"
#include "Pista.h"
#include "Carro.h"
#include "ExcecaoSinalFechado.hpp"
#include "Evento.hpp"
#include <stdlib.h>
#include <stdio.h>
#include <iostream>

class Controle {
 private:
 	int totalCarrosQueEntraram;
 	int totalCarrosQueSairam;
 	ListaCirc<Semaforo*> *s1, *s2;
 	ListaEnc<Pista*> *listaDePistas;
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

 		// Define as probabilidades de inserÃ§Ã£o de carros das pistas que sÃ£o fontes
 		n1Sul   -> setTempoDeFonte(20, 5);
 		n2Sul   -> setTempoDeFonte(20, 5);
 		s1Norte -> setTempoDeFonte(30, 7);
 		s2Norte -> setTempoDeFonte(30, 7);
 		o1Leste -> setTempoDeFonte(10, 2);
 		l1Oeste -> setTempoDeFonte(10, 2);

 		// Cria semÃ¡foros do primeiro cruzamento
 		Semaforo *s1_o1Leste = new Semaforo(true , o1Leste);
 		Semaforo *s1_n1Sul   = new Semaforo(false, n1Sul  );
 		Semaforo *s1_s1Norte = new Semaforo(false, s1Norte);
 		Semaforo *s1_c1Oeste = new Semaforo(false, c1Oeste);
 		s1 -> adiciona(s1_o1Leste);
 		s1 -> adiciona(s1_n1Sul  );
 		s1 -> adiciona(s1_s1Norte);
 		s1 -> adiciona(s1_c1Oeste);

 		// Cria semÃ¡foros do segundo cruzamento
 		Semaforo *s2_c1Leste = new Semaforo(true , c1Leste);
 		Semaforo *s2_n2Sul   = new Semaforo(false, n2Sul  );
 		Semaforo *s2_s2Norte = new Semaforo(false, s2Norte);
 		Semaforo *s2_l1Oeste = new Semaforo(false, l1Oeste);
 		s2 -> adiciona(s2_c1Leste);
 		s2 -> adiciona(s2_n2Sul  );
 		s2 -> adiciona(s2_s2Norte);
 		s2 -> adiciona(s2_l1Oeste);

 		// Inicializa as probabilidades dos semÃ¡foros
		/*
			Como as probabilidades sÃ£o distribuÃ­das em 2 tipos ({80, 10, 10} e {40, 30, 30},
			faremos apenas 2 arranjos para elas e vÃ¡rios para as pistas.
		*/
		int probabilidades1[3] = { 80, 10, 10 };
		int probabilidades2[3] = { 40, 30, 30 };

		Pista *pistas1[3] = { c1Leste, n1Norte, s1Sul };
		s1_o1Leste->setProbabilidades(*pistas1, probabilidades1);

		Pista *pistas2[3] = { c1Leste, o1Oeste, s1Sul };
 		s1_n1Sul -> setProbabilidades(*pistas2, probabilidades1);

		Pista *pistas3[3] = { c1Leste, n1Norte, o1Oeste };
 		s1_s1Norte -> setProbabilidades(*pistas3, probabilidades1);

		Pista *pistas4[3] = { o1Oeste, n1Norte, s1Sul };
 		s1_c1Oeste -> setProbabilidades(*pistas4, probabilidades2);

		Pista *pistas5[3] = { l1Leste, n2Norte, s2Sul };
 		s2_c1Leste -> setProbabilidades(*pistas5, probabilidades2);

		Pista *pistas6[3] = { l1Leste, c1Oeste, s2Sul };
 		s2_n2Sul -> setProbabilidades(*pistas6, probabilidades2);

		Pista *pistas7[3] = { l1Leste, s2Sul, c1Oeste };
 		s2_s2Norte -> setProbabilidades(*pistas7, probabilidades2);

		Pista *pistas8[3] = { n2Norte, c1Leste, s2Sul };
 		s2_l1Oeste -> setProbabilidades(*pistas8, probabilidades2);
 	}

 	void inicializaSimulacao() {
 		create_insereCarros();
 		create_semaforosMudamDeEstado();
 		create_carrosChegamEmSemaforo();
 		processaEvento();
 	}

 	// MÃ‰TODOS DE CRIAÃ‡ÃƒO:
 	// MÃ©todos que possuem "create_" no inÃ­cio indicam que estÃ£o explicitamente
 	// criando eventos.
 	void create_insereCarros() {
 		int tempoAtualDoMetodo, tempoEvento;
 		int i;
 		// POSSÃ�VEL ERRO AQUI NO 0.
 		for (i = 0; i < listaDePistas -> getSize(); i++) {
 			if (listaDePistas -> mostra(i) -> isFonte()) {
 				Pista *pista = listaDePistas -> mostra(i);
 				tempoAtualDoMetodo = tempoAtualDoSistema;
 				// Enquanto o contador de tempo do mÃ©todo for menor
 				// que o tempo determinado para simulaÃ§Ã£o, o laÃ§o
 				// deve continuar criando eventos de inserÃ§Ã£o de carros.
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
		// VerUltimo(): mostra o tamanho da lista.
 		// POSSÃ�VEL ERRO AQUI NO 0.
 		for (i = 0; i < s1 -> verUltimo(); i++) {
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
 		// POSSÃ�VEL ERRO NO 0.
 		for (i = 0; i < listaDeEventos -> getSize(); i++) {
 			if (listaDeEventos -> mostra(i) -> getTipoEvento() == 0) {
 				Evento *e = listaDeEventos -> mostra(i);
 				int tempoDaPista = e -> getCarro() -> getPistaAtual() -> calculaTempoDaPista();
 				tempoQueChegou = (e -> getCarro() -> getPistaAtual() -> calculaTempoDaPista()) + e -> getMomentoQueExecuta();
 				if (tempoQueChegou <= tempoDeSimulacao) {
 					Carro *carro = e -> getCarro();
 					Evento *evento = new Evento(tempoQueChegou, 2, carro, achaSemaforo(carro -> getPistaAtual()));
 					listaDeEventos -> adicionaEvento(evento);
 				}
 			}
 		}
 	}

 	// MÃ‰TODOS DE EXECUÃ‡ÃƒO:
 	// Esses mÃ©todos executam os eventos e implicitamente criam novos eventos.

 	void processaEvento() {
 		int i, tempoAtualDoMetodo;
 		Semaforo *semaforo;
 		Carro *carro;
 		Pista *pista;
 		for (i = 0; i < listaDeEventos -> getSize(); i++) {
 			Evento *evento = listaDeEventos -> mostra(i);
 			switch (evento -> getTipoEvento()) {
 				case 0: {
 					carro = evento -> getCarro();
 					pista = carro -> getPistaAtual();
 					if (pista -> cabeCarroNaPista(carro))
 						pista -> adicionaCarro(carro);
 					tempoAtualDoMetodo = evento -> getMomentoQueExecuta();
 					break;
 				} case 1: {
 					semaforo = evento -> getSemaforo();
 					semaforo -> mudaEstado();
 					tempoAtualDoMetodo = evento -> getMomentoQueExecuta();
 					break;
 				} case 2: {
 					carroChegouEmSemaforo(evento);
 					tempoAtualDoMetodo = evento -> getMomentoQueExecuta();
 					break;
 				} case 3: {
 					carro = evento -> getCarro();
 					pista = carro -> getPistaAtual();
 					pista -> retiraCarro();
 					tempoAtualDoMetodo = evento -> getMomentoQueExecuta();
 					break;
 				}
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
 		} catch (std::exception& e) {
 			tempoQueOSemaforoAbre = achaAberturaDeSemaforo(tempoDoEvento, semaforo);
 			novoEvento = new Evento(tempoQueOSemaforoAbre + 1, 2, evento -> getCarro(), semaforo);
 		}

 		listaDeEventos -> adicionaEvento(novoEvento);
 	}

 	void carroEntrouEmNovaPista(Carro *carro, int tempoAtual) {
 		Evento *novoEvento;
 		Pista *pistaAtual = carro -> getPistaAtual();
		int tempoDePista = pistaAtual -> calculaTempoDaPista();
 		if (pistaAtual -> isSumidouro())
 			novoEvento = new Evento(tempoAtual + tempoDePista, 3, carro, NULL);
 		else
 			novoEvento = new Evento(tempoAtual + tempoDePista, 2, carro, achaSemaforo(pistaAtual));

 		listaDeEventos -> adicionaEvento(novoEvento);
 	}



 	void imprimeResultadoDaSimulacao() {
 		calculaNumeroDeCarros();
 		printf("NÃºmero de carros que entraram no sistema: %d.\n", totalCarrosQueEntraram);
 		printf("NÃºmero de carros que saÃ­ram do sistema: %d.\n", totalCarrosQueSairam);
 	}

 	Semaforo* achaSemaforo(Pista *pista) {
 		int i;
		// VerUltimo(): mostra o tamanho da lista.
 		for (i = 0; i < s1 -> verUltimo(); i++) {
 			Semaforo *semaforo1 = s1 -> mostra(i);
 			Semaforo *semaforo2 = s2 -> mostra(i);
 			if (semaforo1 -> getPistaAtual() == pista)
 				return semaforo1;
 			else if (semaforo2 -> getPistaAtual() == pista)
 				return semaforo2;
 		}

 		throw "SemáforoNãoEncontrado";
 	}

 	int achaAberturaDeSemaforo(int tempoAtual, Semaforo *semaforo) {
 		int i;
 		for (i = 0; i < listaDeEventos -> getSize(); i++) {
 			Evento *evento = listaDeEventos -> mostra(i);
 			if (evento -> getTipoEvento() == 1
 				&& evento -> getMomentoQueExecuta() >= tempoAtual
 				&& semaforo == evento -> getSemaforo()) {
 				return evento -> getMomentoQueExecuta();
 			}
 		}

 		return tempoAtual + 2;
 	}

 	void calculaNumeroDeCarros() {
 		int i;
 		for (i = 0; i < listaDePistas -> getSize(); i++) {
 			Pista *pista = listaDePistas -> mostra(i);
 			if (pista -> isFonte())
 				totalCarrosQueEntraram += pista -> getCarrosQueEntraram();
 			else if (pista -> isSumidouro())
 				totalCarrosQueSairam += pista -> getCarrosQueSairam();
 		}
 	}
};

#endif
