// Copyright [2016] <João Victor Fagundes>

#ifndef LISTACIRC_HPP_
#define LISTACIRC_HPP_
#include "ListaEnc.hpp"

template<typename T>

//! Uma classe ListaCirc.
/*!
    Uma classe que possui os métodos necessários
    para a instanciação de uma lista circular, uma estrutura
    de dados, de maneira funcional.
*/
class ListaCirc : private ListaEnc<T> {
 public:
    //! Um construtor.
    /*!
        Um construtor que instancia uma Lista Circular. Dentro dele
        o tamanho é definido como '0', pois a lista está vazia, cria
        um elemento "sentinela" para definir sempre o início da lista.
        Também manda o ponteiro "head", declarado na classe pai, apontar
        para esse elemento "sentinela".
    */
	ListaCirc() : ListaEnc<T>() {
	    T info;
	    sentinela = new Elemento<T>(info, sentinela);
	    ListaEnc<T>::setHead(sentinela);
	    ListaEnc<T>::setSize(0);
	}

	//! Um destrutor.
    /*!
        Um destrutor que apaga da memória o ponteiro que aponta para o
        início da lista e o elemento "sentinela" que marca o início da lista.
    */
	~ListaCirc() {
	    ListaEnc<T>::setHead(NULL);
	    delete(sentinela);
	}

    //! Uma função que adiciona o dado passado como parâmetro
    //! e faz o ponteiro 'next' do sentinela apontar para o novo
    //! elemento adicionado.
    /*!
        \param dado o dado a ser inserido
        \sa adiciona(), adicionaNaPosicao() and adicionaEmOrdem()
    */
	void adicionaNoInicio(const T& dado) {
		Elemento<T> *novo;
		if (listaVazia()) {
			novo = new Elemento<T>(dado, sentinela);
			sentinela -> setProximo(novo);
		} else {
			novo = new Elemento<T>(dado, sentinela -> getProximo());
			sentinela -> setProximo(novo);
		}
		ListaEnc<T>::setSize(ListaEnc<T>::getSize() + 1);
	}

    //! Uma função que retorna o dado apontado pelo ponteiro "next"
    //! do sentinela e remove esse elemento da lista.
    /*!
        \return o dado apontado pelo ponteiro "next" do sentinela.
        \sa retira(), retiraDaPosicao() and retiraEspecifico()
    */
	T retiraDoInicio() {
		if (listaVazia())
			throw "ErroListaVazia";
		Elemento<T> *aux;
		T dadoRetorno;
		aux = sentinela -> getProximo();
		dadoRetorno = aux -> getInfo();
		sentinela -> setProximo(aux -> getProximo());
		ListaEnc<T>::setSize(ListaEnc<T>::getSize() - 1);
		delete(aux);
		return dadoRetorno;
	}

    //! Uma função que apaga da memória o dado apontado pelo 'next' do sentinela
    //! e faz o ponteiro apontar para o próximo elemento.
    /*!
        \sa retiraDoInicio(), retira(), retiraDaPosicao() and retiraEspecifico()
    */
	void eliminaDoInicio() {
		retiraDoInicio();
	}

    //! Uma função que adiciona o dado passado como parâmetro
    //! na posição informada pelo usuário no parâmetro.
    /*!
        \param dado o dado a ser inserido
        \param pos a posição que o dado deve ser inserido
        \sa adicionaNoInicio(), adiciona() and adicionaEmOrdem()
    */
	void adicionaNaPosicao(const T& dado, int pos) {
		if (pos > ListaEnc<T>::getSize() || pos < 0) {
			throw "ErroPosiçãoInválida";
		} else if (pos == 0) {
			adicionaNoInicio(dado);
		} else {
			Elemento<T> *novo, *anterior;
			anterior = sentinela -> getProximo();
			for (int i = 0; i < (pos - 1); i++)
				anterior = anterior -> getProximo();
			novo = new Elemento<T>(dado, anterior -> getProximo());
			anterior -> setProximo(novo);
			ListaEnc<T>::setSize(ListaEnc<T>::getSize() + 1);
		}
	}

    //! Uma função que retorna a posição do elemento passado como parâmetro
    //! na lista.
    //! Esse método é implementado chamando o método de mesmo nome da classe pai
    /*!
        \param dado o dado que deseja-se descobrir a posição no vetor.
        \return a posição desse dado no vetor
        \sa retiraDaPosicao(), igual(), contem() and listaVazia().
    */
	int posicao(const T& dado) {
		ListaEnc<T>::setHead(sentinela -> getProximo());
		return ListaEnc<T>::posicao(dado);
		ListaEnc<T>::setHead(sentinela);
	}

    //! Uma função que retorna a posição na memória do elemento passado
    //! como parâmetro na lista. Semelhante ao método anterior.
    //! Esse método é implementado chamando o método de mesmo nome da classe pai
    /*!
        \param dado o dado que deseja-se descobrir a posição no vetor.
        \return a posição desse dado no vetor
        \sa posicao(), retiraDaPosicao(), igual(), contem() and listaVazia().
    */
	T* posicaoMem(const T& dado) {
		ListaEnc<T>::setHead(sentinela -> getProximo());
		return ListaEnc<T>::posicaoMem(dado);
		ListaEnc<T>::setHead(sentinela);
	}

    //! Uma função que informa se tal dado existe na lista ou não.
    //! Esse método é implementado chamando o método de mesmo nome da classe pai
    /*!
        \param dado o dado que deseja verificar se está na lista.
        \return um bool informando se tal dado está ou não na lista.
        \sa listaVazia()
    */
	bool contem(const T& dado) {
		ListaEnc<T>::setHead(sentinela -> getProximo());
		return ListaEnc<T>::contem(dado);
		ListaEnc<T>::setHead(sentinela);
	}

    //! Uma função que retorna um dado inserido e o remove da lista. A posição
    //! do dado é fornecida através do parâmetro "posicao".
    /*!
        \param pos a posição que se encontra o dado desejado
        \return o dado da posição passada no parâmetro da função.
        \sa retiraDoInicio(), retira() and retiraEspecifico()
    */
	T retiraDaPosicao(int pos) {
		T dadoRetorno;
		if (pos > ListaEnc<T>::getSize() || pos < 0) {
			throw "ErroPosiçãoInválida";
		} else if (pos == 0) {
			return retiraDoInicio();
		} else {
			Elemento<T> *anterior, *eliminar;
			anterior = sentinela -> getProximo();
			for (int i = 0; i < (pos - 1); i++)
				anterior = anterior -> getProximo();
			eliminar = anterior -> getProximo();
			dadoRetorno = eliminar -> getInfo();
			anterior -> setProximo(eliminar -> getProximo());
			ListaEnc<T>::setSize(ListaEnc<T>::getSize() - 1);
			delete(eliminar);
		}
		return dadoRetorno;
	}

    //! Uma função que adiciona o dado passado como parâmetro
    //! na posição logo após o último dado inserido.
    /*!
        \param dado o dado a ser inserido
        \sa adicionaNoInicio(), adicionaNaPosicao() and adicionaEmOrdem()
    */
	void adiciona(const T& dado) {
		adicionaNaPosicao(dado, ListaEnc<T>::getSize());
	}

    //! Uma função que retorna o último dado inserido e o remove da lista.
    /*!
        \return o dado adicionado por último na lista.
        \sa retiraDoInicio(), retiraDaPosicao() and retiraEspecifico()
    */
	T retira() {
		return retiraDaPosicao(ListaEnc<T>::getSize() - 1);
	}

    //! Uma função que retorna e remove o dado igual ao dado passado como
    //! parâmetro
    /*!
        \param dado o dado que deseja remover da lista.
        \return o dado que foi removido da lista.
        \sa retiraDoInicio(), retira() and retiraDaPosicao()
    */
	T retiraEspecifico(const T& dado) {
		int pos = posicao(dado);
		return retiraDaPosicao(pos);
	}

    //! Uma função que retorna, sem removê-lo da lista, o dado
    //! igual ao dado passado como parâmetro.
    /*!
        \param pos a posição do dado que deseja ver.
        \return o dado da posição passada como parâmetro.
        \sa posicao(), adicionaNaPosicao() and retiraDaPosicao()
    */
	T mostra(int pos) {
		T dadoRetorno = retiraDaPosicao(pos);
		adicionaNaPosicao(dadoRetorno, pos);
		return dadoRetorno;
	}

    //! Uma função que adiciona à lista o dado passado como parâmetro
    //! em ordem crescente.
    /*!
        \param dado o dado a ser inserido
        \sa adicionaNoInicio(), adicionaNaPosicao() and adiciona()
    */
	void adicionaEmOrdem(const T& data) {
		if (listaVazia())
	        adicionaNoInicio(data);
	    Elemento<T> *atual = sentinela -> getProximo();
	    int posicao = 0;
	    while (!(atual -> getProximo(), sentinela) &&
	        maior(data, atual -> getInfo())) {
	            atual = atual -> getProximo();
	            posicao++;
	        }
	    if (maior(data, atual -> getInfo()))
	        adicionaNaPosicao(data, (posicao + 1));
	    else
	        adicionaNaPosicao(data, posicao);
	}

    //! Uma função que retorna o inteiro da variável "size" da classe pai,
    //! que informa o tamanho da lista
    /*!
        \return o tamanho da lista.
        \sa listaVazia(), retira() and adiciona()
    */
	int verUltimo() {
		return ListaEnc<T>::getSize();
	}

    //! Uma função que informa se a lista está cheia.
    /*!
        \return um bool informando se a lista está vazia ou não.
        \sa retira(), retiraDoInicio(), retiraDaPosicao() and retiraEspecífico().
    */
	bool listaVazia() const {
		return ListaEnc<T>::listaVazia();
	}

    //! Uma função que informa se dois dados são iguais.
    //! Esse método é implementado chamando o método de mesmo nome da classe pai
    /*!
        \param dado1 o primeiro dado a ser comparado.
        \param dado2 o segundo dado a ser comparado.
        \return um bool informando se os dados são iguais.
        \sa contem(), maior() and menor().
    */
	bool igual(T dado1, T dado2) {
		ListaEnc<T>::setHead(sentinela -> getProximo());
		return ListaEnc<T>::igual(dado1, dado2);
		ListaEnc<T>::setHead(sentinela);
	}

    //! Uma função que informa se um dado é maior que outro.
    //! Esse método é implementado chamando o método de mesmo nome da classe pai
    /*!
        \param dado1 o primeiro dado a ser comparado.
        \param dado2 o segundo dado a ser comparado.
        \return um bool informando se o dado1 é maior que o dado2.
        \sa adicionaEmOrdem(), menor() and igual().
    */
	bool maior(T dado1, T dado2) {
		ListaEnc<T>::setHead(sentinela -> getProximo());
		return ListaEnc<T>::maior(dado1, dado2);
		ListaEnc<T>::setHead(sentinela);
	}

    //! Uma função que informa se um dado é menor que outro.
    //! Esse método é implementado chamando o método de mesmo nome da classe pai
    /*!
        \param dado1 o primeiro dado a ser comparado.
        \param dado2 o segundo dado a ser comparado.
        \return um bool informando se o dado1 é menor que o dado2.
        \sa adicionaEmOrdem(), maior() and igual().
    */
	bool menor(T dado1, T dado2) {
		ListaEnc<T>::setHead(sentinela -> getProximo());
		return ListaEnc<T>::menor(dado1, dado2);
		ListaEnc<T>::setHead(sentinela);
	}

    //! Uma função que apaga todos os dados da lista, um por um
    //! cuidando para não deixar defuntos em memória.
    /*!
        \sa retira(), retiraDoInicio(), retiraDaPosicao() and retiraEspecífico()
    */
	void destroiLista() {
		Elemento<T> *atual;
	    atual = sentinela -> getProximo();
	    while (atual -> getProximo() != sentinela) {
	        Elemento<T> *anterior;
	        anterior = atual;
	        atual = atual -> getProximo();
	        delete(anterior);
	    }
	    ListaEnc<T>::setSize(0);
	}

 private:
    //! Uma váriavel do tipo 'Elemento<T>'.
    /*!
        Essa variável guarda um apontador para o primeiro elemento
        "sentinela", que é o primeiro elemento da lista.
    */
    Elemento<T> *sentinela;
};

#endif