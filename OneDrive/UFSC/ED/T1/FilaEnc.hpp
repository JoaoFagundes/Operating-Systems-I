// Copyright [2016] <João Victor Fagundes>

#include "ListaEnc.hpp"

template <typename T>

//! Uma classe Fila.
/*!
    Uma classe que possui os métodos necessários
    para a instanciação de uma fila, uma estrutura
    de dados, de maneira funcional.
*/
class FilaEnc : private ListaEnc<T> {
 public:
    //! Um construtor.
    /*!
        Esse construtor inicializa a fila baseado no
        construtor da classe pai "ListaEnc".
    */
	FilaEnc<T>() {}

    //! Um destrutor.
    /*!
        Um destrutor sem instruções para que apenas chame o destrutor
        da classe pai.
    */
	~FilaEnc() {}

    //! Uma função que adiciona à fila o dado passado como parâmetro
    /*!
        \param dado o dado a ser inserido
        \sa retira() and ultimo()
    */
	void inclui(const T& dado) {
	    ListaEnc<T>::adiciona(dado);
	}

    //! Uma função que remove o primeiro dado da fila.
    /*!
        \return o primeiro dado inserido na fila.
    	\sa filaVazia(), primeiro() and limparFila()
   	*/
	T retira() {
	    return ListaEnc<T>::retiraDoInicio();
	}

    //! Uma função que apenas retorna o último dado da fila.
    /*!
        \return o dado inserido por último na fila
    	\sa inclui() and filaVazia()
   	*/
	T ultimo() {
	    T dadoRetorno = ListaEnc<T>::retira();
	    inclui(dadoRetorno);
	    return dadoRetorno;
	}

    //! Uma função que apenas retorna o primeiro dado da fila.
    /*!
        \return o primeiro dado da fila
    	\sa retira() and filaVazia()
   	*/
	T primeiro() {
	    T dadoRetorno = ListaEnc<T>::retiraDoInicio();
	    ListaEnc<T>::adicionaNoInicio(dadoRetorno);
	    return dadoRetorno;
	}

    //! Uma função que informa se a fila está vazia.
    /*!
        \return um bool verdadeiro caso a fila esteja vazia, ou um falso caso haja elementos.
        \sa limparFila(), retira() and inclui()
    */
	bool filaVazia() {
	    return ListaEnc<T>::listaVazia();
	}

    //! Uma função que limpa a lista.
    /*!
        Chama função da classe pai que limpa todo o conteúdo da fila.
        \sa filaVazia() and retira()
    */
	void limparFila() {
	    ListaEnc<T>::destroiLista();
	}
};

