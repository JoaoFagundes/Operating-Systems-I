// Copyright [2016] <João Victor Fagundes>

#include "Elemento.hpp"

template<typename T>

//! Uma classe ListaEnc.
/*!
    Uma classe que possui os métodos necessários
    para a instanciação de uma lista encadeada, uma estrutura
    de dados, de maneira funcional.
*/
class ListaEnc {
 public:
    //! Um construtor.
    /*!
        Um construtor que instancia uma Lista Encadeada. Dentro dele
        o tamanho é definido como '0', pois a lista está vazia, e 
        seu ponteiro aponta para NULL.
    */
	ListaEnc() {
	    size = 0;
	    head = NULL;
	}

	//! Um destrutor.
    /*!
        Um destrutor que apaga da memória o ponteiro que aponta para o
        início da lista.
    */
	~ListaEnc() {
        delete(head);
	}

	// inicio

    //! Uma função que adiciona o dado passado como parâmetro
    //! e faz o ponteiro 'head' apontar para o novo elemento adicionado.
    //! O elemento que antes era apontado por 'head' agora é apontado por
    //! 'next_' do novo elemento.
    /*!
        \param dado o dado a ser inserido
        \sa adiciona(), adicionaNaPosicao() and adicionaEmOrdem()
    */
	void adicionaNoInicio(const T& dado) {
	    Elemento<T> *novo = new Elemento<T>(dado, head);
	    if (novo == NULL)
	        throw "ErroFaltaDeMemória";
	    head = novo;
	    size++;
	}

    //! Uma função que retorna o dado apontado por 'head' e o remove da lista.
    /*!
        \return o dado apontado por 'head'.
        \sa retira(), retiraDaPosicao() and retiraEspecifico()
    */
	T retiraDoInicio() {
	    if (listaVazia())
	        throw "ErroListaVazia";
	    Elemento<T> *aux;
	    T dadoRetorno;
	    aux = head;
	    dadoRetorno = aux -> getInfo();
	    head = aux -> getProximo();
	    size--;
	    delete(aux);
	    return dadoRetorno;
    }

    //! Uma função que apaga da memória o dado apontado por 'head',
    //! e faz o ponteiro apontar para o próximo elemento.
    /*!
        \sa retiraDoInicio(), retira(), retiraDaPosicao() and retiraEspecifico()
    */
	void eliminaDoInicio() {
	    if (listaVazia())
	        throw "ErroListaVazia";
	    Elemento<T> *aux;
	    aux = head;
	    head = aux -> getProximo();
	    size--;
	    delete(aux -> getInfo());
	    delete(aux);
	}

	// posicao

	//! Uma função que adiciona o dado passado como parâmetro
    //! na posição informada pelo usuário no parâmetro.
    /*!
        \param dado o dado a ser inserido
        \param pos a posição que o dado deve ser inserido
        \sa adicionaNoInicio(), adiciona() and adicionaEmOrdem()
    */
	void adicionaNaPosicao(const T& dado, int pos) {
	    Elemento<T> *novo, *anterior;
	    if (pos > size || pos < 0) {
	        throw "ErroPosiçãoInválida";
	    } else if (pos == 0) {
	        adicionaNoInicio(dado);
	    } else {
	        anterior = head;
	        for (int i = 0; i < (pos - 1); i++)
	            anterior = anterior -> getProximo();
	        novo = new Elemento<T>(dado, anterior -> getProximo());
	        anterior -> setProximo(novo);
	        size++;
	    }
	}

    //! Uma função que retorna a posição do elemento passado como parâmetro
    //! na lista.
    /*!
        \param dado o dado que deseja-se descobrir a posição no vetor.
        \return a posição desse dado no vetor
        \sa retiraDaPosicao(), igual(), contem() and listaVazia().
    */
	int posicao(const T& dado) const {
	    if (!contem(dado)) {
	        throw "ErroDadoNãoExiste";
        }
        Elemento<T> *aux;
        aux = head;
        if (igual(aux -> getInfo(), dado))
            return 0;
        for (int i = 1; i <= size; i++) {
            aux = aux -> getProximo();
            if (igual(aux -> getInfo(), dado))
                return (i);
        }
        throw "ErroDadoNãoExiste";
    }

    //! Uma função que retorna a posição na memória do elemento passado
    //! como parâmetro na lista. Semelhante ao método anterior.
    /*!
        \param dado o dado que deseja-se descobrir a posição no vetor.
        \return a posição desse dado no vetor
        \sa posicao(), retiraDaPosicao(), igual(), contem() and listaVazia().
    */
	T* posicaoMem(const T& dado) const {
	    if (!contem(dado)) {
	        throw "ErroElementoNãoExiste";
	    } else {
	        Elemento<T> *aux;
	        int *ptr;
	        aux = head;
	        if (igual(head -> getInfo(), dado))
	            return &(head -> getInfo());
	        for (int i = 1; i < size; i++) {
	            aux = aux -> getProximo();
	            if (igual(aux -> getInfo(), dado))
	                return &(aux -> getInfo());
	        }
	    }
	    throw "ErroDadoNãoExiste";
	}

    //! Uma função que informa se tal dado existe na lista ou não.
    /*!
        \param dado o dado que deseja verificar se está na lista.
        \return um bool informando se tal dado está ou não na lista.
        \sa listaVazia()
    */
	bool contem(const T& dado) const {
	    if (listaVazia())
	        return false;
	    Elemento<T> *aux;
	    aux = head;
	    if (igual(aux -> getInfo(), dado))
	        return true;
	    for (int i = 1; i < size; i++) {
	        aux = aux -> getProximo();
	        if (igual(aux -> getInfo(), dado))
	            return true;
	    }
	    return false;
	}

    //! Uma função que retorna um dado inserido e o remove da lista. A posição
    //! do dado é fornecida através do parâmetro "posicao".
    /*!
        \param pos a posição que se encontra o dado desejado
        \return o dado da posição passada no parâmetro da função.
        \sa retiraDoInicio(), retira() and retiraEspecifico()
    */
	T retiraDaPosicao(int pos) {
	    if (listaVazia())
	        throw "ErroListaVazia";
	    Elemento<T> *anterior, *eliminar;
	    T dadoRetorno;
	    if (pos >= size || pos < 0) {
	        throw "ErroPosiçãoInválida";
	    } else if (pos == 0) {
	        dadoRetorno = retiraDoInicio();
	        return dadoRetorno;
	    } else {
	        anterior = head;
	        for (int i = 0; i < (pos - 1); i++)
	            anterior = anterior -> getProximo();
	        eliminar = anterior -> getProximo();
	        dadoRetorno = eliminar -> getInfo();
	        anterior -> setProximo(eliminar -> getProximo());
	        size--;
	        delete(eliminar);
	    }
	    return dadoRetorno;
	}

	// fim

    //! Uma função que adiciona o dado passado como parâmetro
    //! na posição logo após o último dado inserido.
    /*!
        \param dado o dado a ser inserido
        \sa adicionaNoInicio(), adicionaNaPosicao() and adicionaEmOrdem()
    */
	void adiciona(const T& dado) {
	    adicionaNaPosicao(dado, (size));
	}

    //! Uma função que retorna o último dado inserido e o remove da lista.
    /*!
        \return o dado adicionado por último na lista.
        \sa retiraDoInicio(), retiraDaPosicao() and retiraEspecifico()
    */
	T retira() {
	    if (listaVazia())
	        throw "ErroListaVazia";
	    return retiraDaPosicao(size - 1);
	}

	// especifico

	//! Uma função que retorna e remove o dado igual ao dado passado como
    //! parâmetro
    /*!
        \param dado o dado que deseja remover da lista.
        \return o dado que foi removido da lista.
        \sa retiraDoInicio(), retira() and retiraDaPosicao()
    */
	T retiraEspecifico(const T& dado) {
	    if (listaVazia())
	        throw "ErroListaVazia";
	    else if (!contem(dado))
	        throw "ErroElementoNãoExiste";
	    int aux = posicao(dado);
	    return retiraDaPosicao(aux);
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
	    Elemento<T> *atual = head;
	    int posicao = 0;
	    while (!(atual -> getProximo(), NULL) &&
	        maior(data, atual -> getInfo())) {
	            atual = atual -> getProximo();
	            posicao++;
	        }
	    if (maior(data, atual -> getInfo()))
	        adicionaNaPosicao(data, (posicao + 1));
	    else
	        adicionaNaPosicao(data, posicao);
	}

    //! Uma função que informa se a lista está cheia.
    /*!
        \return um bool informando se a lista está vazia ou não.
        \sa retira(), retiraDoInicio(), retiraDaPosicao() and retiraEspecífico().
    */
	bool listaVazia() const {
	    if (size == 0)
	        return true;
	    return false;
	}

    //! Uma função que informa se dois dados são iguais.
    /*!
        \param dado1 o primeiro dado a ser comparado.
        \param dado2 o segundo dado a ser comparado.
        \return um bool informando se os dados são iguais.
        \sa contem(), maior() and menor().
    */
	bool igual(T dado1, T dado2) const {
	    if (dado1 == dado2)
	        return true;
	    return false;
	}

    //! Uma função que informa se um dado é maior que outro.
    /*!
        \param dado1 o primeiro dado a ser comparado.
        \param dado2 o segundo dado a ser comparado.
        \return um bool informando se o dado1 é maior que o dado2.
        \sa adicionaEmOrdem(), menor() and igual().
    */
	bool maior(T dado1, T dado2) const {
	    if (dado1 > dado2)
	        return true;
	    return false;
	}

    //! Uma função que informa se um dado é menor que outro.
    /*!
        \param dado1 o primeiro dado a ser comparado.
        \param dado2 o segundo dado a ser comparado.
        \return um bool informando se o dado1 é menor que o dado2.
        \sa adicionaEmOrdem(), maior() and igual().
    */
	bool menor(T dado1, T dado2) const {
	    if (dado1 < dado2)
	        return true;
	    return false;
	}

    //! Uma função que apaga todos os dados da lista, um por um
    //! cuidando para não deixar defuntos em memória.
    /*!
        \sa retira(), retiraDoInicio(), retiraDaPosicao() and retiraEspecífico().
    */
	void destroiLista() {
	    Elemento<T> *atual;
	    atual = head;
	    while (atual -> getProximo() != NULL) {
	        Elemento<T> *anterior;
	        anterior = atual;
	        atual = atual -> getProximo();
	        delete(anterior);
	    }
	    head = NULL;
	    size = 0;
	}

 private:
    //! Uma váriavel do tipo 'Elemento<T>'.
    /*!
        Essa variável guarda um apontador para o primeiro elemento
        da lista encadeada.
    */
	Elemento<T>* head;
	//! Uma váriavel do tipo int.
    /*!
        Essa variável guarda o número de elementos que a lista possui.
    */
	int size;
};
