#include <stdlib.h>
#include <iostream>
#include "Sistema.hpp"

int main() {
	int tempoDeSimulacao = 50;
	int tempoSemaforo = 5;
	Controle *controle = new Controle(tempoDeSimulacao, tempoSemaforo);
	return 0;
}