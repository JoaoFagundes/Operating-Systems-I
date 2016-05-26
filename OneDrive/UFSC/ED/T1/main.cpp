#include <stdlib.h>
#include <iostream>

#include "Controle.hpp"

int main() {
	int tempoDeSimulacao = 150;
	int tempoSemaforo = 10;
	Controle *controle = new Controle(tempoDeSimulacao, tempoSemaforo);
	return 0;
}
