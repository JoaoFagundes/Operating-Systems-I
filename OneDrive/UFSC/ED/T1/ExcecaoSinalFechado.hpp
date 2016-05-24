#ifndef EXCECAOSINALFECHADO_HPP_
#define EXCECAOSINALFECHADO_HPP_
#include <exception>

class ExcecaoSinalFechado : public std::exception {
 public:
 	char* mensagemErro() throw() {
 		return "Semáforo fechado.";
 	}
};

#endif