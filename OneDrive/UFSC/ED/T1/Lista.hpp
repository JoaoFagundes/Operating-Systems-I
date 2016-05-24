// Copyright [2016] <João Victor Fagundes>

#ifndef LISTA_HPP_
#define LISTA_HPP_
template <typename T>
//! Uma classe Lista.
/*!
    Uma classe que possui os métodos necessários
    para a instanciação de uma lista, uma estrutura
    de dados, de maneira funcional.
*/
class Lista {
 private:
    //! Uma váriavel do tipo 'T'.
    /*!
        Essa variável posteriormente se tornará o vetor que
        irá armazenar os dados da lista.
    */
    T* m_dados_;

    //! Um inteiro "ultimo_".
    /*!
        Esse inteiro guarda a posição no vetor do último
        dado inserido na lista.
    */
    int ultimo_;

    //! Um inteiro "maxlista".
    /*!
        Esse inteiro guarda o número de elementos que a
        a lista pode armazenar.
    */
    int maxlista;

 public:
    //! Um construtor.
    /*!
        Um construtor padrão, sem parâmetros que serve
        apenas para instanciação da classe.
    */
	Lista();

    //! Outro construtor.
    /*!
        Esse construtor recebe um inteiro como parâmetro e 
        cria um vetor cujo tamanho será o inteiro fornecido.
        Também inicializa o "ultimo_" como -1 para sinalizar que
        a lista está vazia.
    */
	explicit Lista(int tam) {
	    ultimo_ = -1;
	    maxlista = tam;
	    m_dados_ = new T[maxlista];
	}

    //! Uma função que adiciona o dado passado como parâmetro
    //! na posição logo após o último dado inserido.
    /*!
        \param dado o dado a ser inserido
        \sa adicionaNoInicio(), adicionaNaPosicao() and adicionaEmOrdem()
    */
	void adiciona(T dado) {
	    if (listaCheia())
	        throw "ErroListaCheia";
	    adicionaNaPosicao(dado, (ultimo_ + 1));
	}

    //! Uma função que adiciona o dado passado como parâmetro
    //! na posição '0' do vetor, jogando os outros dados uma posição acima cada.
    /*!
        \param dado o dado a ser inserido
        \sa adiciona(), adicionaNaPosicao() and adicionaEmOrdem()
    */
	void adicionaNoInicio(T dado) {
        if (listaCheia())
            throw "ErroListaCheia";
        adicionaNaPosicao(dado, 0);
	}

    //! Uma função que adiciona o dado passado como parâmetro
    //! na posição informada pelo usuário no parâmetro.
    /*!
        \param dado o dado a ser inserido
        \param posicao a posição que o dado deve ser inserido
        \sa adicionaNoInicio(), adiciona() and adicionaEmOrdem()
    */
	void adicionaNaPosicao(T dado, int posicao) {
	    if (listaCheia()) {
	        throw "ErroListaCheia";
	    } else if (posicao < 0 || posicao > (ultimo_ + 1)) {
	        throw "ErroPosicaoIncorreta";
	    } else {
	        for (int i = ultimo_; i >= posicao; i--)
	            m_dados_[i + 1] = m_dados_[i];
	        m_dados_[posicao] = dado;
	        ultimo_ += 1;
	    }
	}

    //! Uma função que adiciona à lista o dado passado como parâmetro
    //! em ordem crescente.
    /*!
        \param dado o dado a ser inserido
        \sa adicionaNoInicio(), adicionaNaPosicao() and adiciona()
    */
	void adicionaEmOrdem(T dado) {
	    if (listaCheia()) {
	        throw "ErroListaCheia";
	    } else if (listaVazia()) {
	        adicionaNoInicio(dado);
	    } else {
	        for (int i = 0; i <= ultimo_; i++) {
	            if (maior(m_dados_[i], dado)) {
	                adicionaNaPosicao(dado, i);
	                break;
	            } else if (i == ultimo_ && maior(dado, m_dados_[i])) {
	                adiciona(dado);
	                break;
	            }
	        }
	    }
	}

    //! Uma função que retorna o último dado inserido e o remove da lista.
    /*!
        \return o dado adicionado por último na lista.
        \sa retiraDoInicio(), retiraDaPosicao() and retiraEspecifico()
    */
	T retira() {
	    T dado;
	    if (listaVazia())
	        throw "ErroListaVazia";
	    dado = retiraDaPosicao(ultimo_);
	    return dado;
	}

    //! Uma função que retorna o dado da posição '0' e o remove da lista.
    /*!
        \return o dado da posição '0' da lista.
        \sa retira(), retiraDaPosicao() and retiraEspecifico()
    */
	T retiraDoInicio() {
	    T dado;
	    if (listaVazia())
	        throw "ErroListaVazia";
	    dado = retiraDaPosicao(0);
	    return dado;
	}

    //! Uma função que retorna um dado inserido e o remove da lista. A posição
    //! do dado é fornecida através do parâmetro "posicao".
    /*!
        \param posicao a posição que se encontra o dado desejado
        \return o dado da posição passada no parâmetro da função.
        \sa retiraDoInicio(), retira() and retiraEspecifico()
    */
	T retiraDaPosicao(int posicao) {
	    T dado;
	    if (listaVazia()) {
	        throw "ErroListaVazia";
	    } else if (posicao < 0 || posicao > ultimo_) {
	        throw "ErroPosicaoIncorreta";
	    } else {
	        dado = m_dados_[posicao];
	        for (int i = posicao; i < ultimo_; i++)
	            m_dados_[posicao] = m_dados_[posicao + 1];
	        ultimo_--;
	    }
	    return dado;
	}

    //! Uma função que retorna e remove o dado igual ao dado passado como
    //! parâmetro
    /*!
        \param dado o dado que deseja remover da lista.
        \return o dado que foi removido da lista.
        \sa retiraDoInicio(), retira() and retiraDaPosicao()
    */
	T retiraEspecifico(T dado) {
	    if (listaVazia()) {
	        throw "ErroListaVazia";
	    } else if (!contem(dado)) {
	        throw "ErroDadoNãoExiste";
	    } else {
	        int posicaoDado = posicao(dado);
	        T novoDado = retiraDaPosicao(posicaoDado);
            return novoDado;
        }
    }

    //! Uma função que retorna a posição no vetor de determinado dado
    //! passado como parâmetro.
    /*!
        \param dado o dado que deseja-se descobrir a posição no vetor.
        \return a posição desse dado no vetor
        \sa retiraDaPosicao(), igual(), contem() and listaVazia().
    */
	int posicao(T dado) {
	    if (listaVazia())
	        throw "ErroListaVazia";
	    else if (!contem(dado))
	        throw "ErroDadoNaoExiste";
	    for (int i = 0; i <= ultimo_; i++) {
	        if (igual(m_dados_[i], dado))
	            return i;
	    }
	    throw "ErroDadoNaoExiste";
	}

    //! Uma função que informa se tal dado existe na lista ou não.
    /*!
        \param dado o dado que deseja verificar se está na lista.
        \return um bool informando se tal dado está ou não na lista.
        \sa listaVazia()
    */
	bool contem(T dado) {
	    if (listaVazia())
	        return false;
	    for (int i = 0; i <= ultimo_; i++) {
	        if (m_dados_[i] == dado)
	            return true;
	    }

	    return false;
	}

    //! Uma função que informa se dois dados são iguais.
    /*!
        \param dado1 o primeiro dado a ser comparado.
        \param dado2 o segundo dado a ser comparado.
        \return um bool informando se os dados são iguais.
        \sa contem(), maior() and menor().
    */
	bool igual(T dado1, T dado2) {
	    return dado1 == dado2;
	}

    //! Uma função que informa se um dado é maior que outro.
    /*!
        \param dado1 o primeiro dado a ser comparado.
        \param dado2 o segundo dado a ser comparado.
        \return um bool informando se o dado1 é maior que o dado2.
        \sa adicionaEmOrdem(), menor() and igual().
    */
	bool maior(T dado1, T dado2) {
	    return dado1 > dado2;
	}

    //! Uma função que informa se um dado é menor que outro.
    /*!
        \param dado1 o primeiro dado a ser comparado.
        \param dado2 o segundo dado a ser comparado.
        \return um bool informando se o dado1 é menor que o dado2.
        \sa adicionaEmOrdem(), maior() and igual().
    */
	bool menor(T dado1, T dado2) {
	    return dado1 < dado2;
	}

    //! Uma função que informa se a lista está cheia.
    /*!
        \return um bool informando se a lista está cheia ou não.
        \sa adiciona(), adicionaEmOrdem(), adicionaNaPosicao() and adicionaNoInicio().
    */
	bool listaCheia() {
	    if (ultimo_ == (maxlista - 1))
	        return true;
	    return false;
	}

    //! Uma função que informa se a lista está cheia.
    /*!
        \return um bool informando se a lista está vazia ou não.
        \sa retira(), retiraDoInicio(), retiraDaPosicao() and retiraEspecífico().
    */
	bool listaVazia() {
	    if (ultimo_ == -1)
	        return true;
	    return false;
	}

    //! Uma apaga todos os dados da lista.
    /*!
        \sa retira(), retiraDoInicio(), retiraDaPosicao() and retiraEspecífico().
    */
	void destroiLista() {
	    ultimo_ = -1;
	}
};

#endif
