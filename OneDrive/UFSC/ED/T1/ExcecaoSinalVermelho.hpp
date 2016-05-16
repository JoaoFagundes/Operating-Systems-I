#include <exception>

class ExcecaoSinalFechado : public std::exception {
 public:
 	String mensagemErro() throw() {
 		return "Semáforo fechado.";
 	}
}