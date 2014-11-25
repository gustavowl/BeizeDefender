#ifndef _FILA_DUPLA_H_
#define _FILA_DUPLA_H_
	#include <cstddef>

	/**
	* \class FilaDupl
	*
	* \brief Classe genérica de fila circula duplamente encadeada. Se comporta como uma mistura de fila e lista
	* pois sempre insere no final da fila, remove do começo, mas pode-se obter qualquer elemento da fila
	* pelo get.
	*
	* 
	*
	*/
	template <class type>
	class FilaDupl {
	private:
		int tam = 0; /**< Armazena o tamanho atual da fila*/

	public:
		struct node{
			type val; /**< Armazena o valor do nó atual*/
			node* next = NULL; /**< Armazena o endereço de memória para o próximo nó. Por padrão é NULO*/
			node* prev = NULL; /**< Armazena o endereço de memória para o nó anterior. Por padrão é NULO*/
		};
		node* first; /**< Armazena o endereço de memória do primeiro nó da fila*/
		node* lastget; /**< Armazena o endereço de memória do último nó retornado*/

		/**
		* Construtor padrão
		* Inicializa tamanho, e ponteiros next e prev de first
		*/
		FilaDupl();
		/**
		* Construtor de cópia
		* Faz cópia profunda da fila.
		*/
		FilaDupl(const FilaDupl &fila_dupl);
		/**
		* Destrutor
		* Desoloca memória reservada dinamicamente pelos nós da fila
		*/
		~FilaDupl();
		/**
		* Sobrecarga do operador =
		* Faz cópia profunda da fila.
		*/
		FilaDupl& operator=(const FilaDupl &fila_dupl);
		/**
		* Retorna o tamanho atual da lista
		*/
		int Size();
		/**
		* Retorna o primeiro elemento da fila por referência
		* \return Retorna se recebeu um valor válido por referência
		* @param &get recebe o primeiro valor da fila por referência
		*/
		bool GetFirstElem(type &get);
		/**
		* Retorna o próximo elemento da fila por referência
		* \return Retorna se recebeu um valor válido por referência
		* @param &get recebe o próximo valor da fila por referência
		*/
		bool GetNextElem(type &get);
		/**
		* Retorna o elemento anterior da fila por referência
		* \return Retorna se recebeu um valor válido por referência
		* @param &get recebe o valor anterior da fila por referência
		*/
		bool GetPrevElem(type &get);
		/**
		* Retorna o último elemento retornado por referência
		* \return Retorna se recebeu um valor válido por referência
		* @param &get recebe o valor do último elemento retornado por referência
		*/
		bool GetLastGetElem(type &get);
		/**
		* Insere elemento na última posição da fila.
		* \return Retorna se conseguiu inserir valor
		* @param val valor a ser inserido na fila ou pilha
		*/
		bool Insert(type val);
		/*
		* Remove primeiro valor da fila (primeiro inserido)
		* \return Retorna se removeu o elemento
		*/
		bool Remove();
		/*
		* Remove primeiro valor da fila (primeiro inserido) e retorna o valor removido por referência
		* \return Retorna se removeu o elemento
		* @param Recebe o valor removido por referência
		*/
		bool Remove(type &get);

		int Search(type val); //retorna posição da primeira instância de val
	};

	#include "FilaDupl.inl"
#endif