#ifndef _LISTA_H_
#define _LISTA_H_
	#include <iostream>
	#include <cstddef>

	//fila duplamente encadeada
	//na realidade vai funcionar como uma mistura de fila e lista encadeada
	//sempre insere no final da fila, remove do começo, mas o Get percorre um passo da lista
	template <class type>
	class FilaDupl {
	private:
		int tam = 0;

	public:
		struct node{
			type val;
			node* next = NULL;
			node* prev = NULL;
		};
		node* first; //evita erro de apontar para 0x0 ou 0x1
		//aponta originalmente pro último elemento.
		//primeiro getnext retornará first. Primeiro getprev retornará o antepenúltimo
		node* lastget; //último nó retornado pelo get

		FilaDupl();
		FilaDupl(const FilaDupl &fila_dupl);
		~FilaDupl();
		FilaDupl& operator=(const FilaDupl &fila_dupl);
		int Size();
		//bool GetElem(int pos, type &get) const;
		bool GetFirstElem(type &get);
		bool GetNextElem(type &get);
		bool GetPrevElem(type &get);
		bool GetLastGetElem(type &get);
		//int Search(type val);
		//bool Insert(int pos, type val);
		bool Insert(type val);
		//bool Remove(unsigned int pos);
		bool Remove();
		//bool Remove(int pos, type &get);
		bool Remove(type &get);
	};

	#include "FilaDupl.inl"
#endif