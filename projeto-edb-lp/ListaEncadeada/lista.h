#ifndef _LISTA_H_
#define _LISTA_H_
	#include <iostream>
	#include <cstddef>

	enum BEHAVIOR {LISTASIMPLES, PILHA, FILA}; //0, 1, 2

	template <class type>
	class Lista {
	private:
		int tam = 0;
		BEHAVIOR bhvr;

	public:
		struct node{
			type val;
			node* next = NULL;
		};
		node* head = new node; //evita erro de apontar para 0x0 ou 0x1

		Lista();
		Lista(BEHAVIOR b);
		Lista(const Lista &l);
		~Lista();
		Lista& operator=(const Lista &l);
		int Size();
		bool GetElem(int pos, type &get) const;
		bool GetElem(type &get) const;
		int Search(type val);
		bool Insert(int pos, type val);
		bool Insert(type val);
		bool Remove(unsigned int pos);
		bool Remove();
		bool Remove(int pos, type &get);
		bool Remove(type &get);
		void Print(char separator = ' ');
	//MÉTODOS
		//construtores
/*		Lista() {
			bhvr = LISTASIMPLES;
			//head = new node;
			head->next = NULL;
		}

		Lista(BEHAVIOR b) {
			bhvr = b;
			//head = new node;
			head->next = NULL;
		}

		Lista(const Lista &l) { //construtor de cópia (profunda)
			bhvr = l.bhvr;
			tam = l.tam;
			node* temp = l.head->next;
			node* copy = head;
			while (temp != NULL) {
				copy->next = new node;
				copy = copy->next;
				copy->val = temp->val;
				temp = temp->next;
			}
		}
		//destructor
		~Lista() {
			if (bhvr == LISTASIMPLES)
				while (Remove(0));
			else
				while (Remove());
			//delete head;
		}

		//operator =
		Lista& operator=(const Lista &l) {
			bhvr = l.bhvr;
			tam = l.tam;
			node* temp = l.head->next;
			node* copy = head;
			while (temp != NULL) {
				copy->next = new node;
				copy = copy->next;
				copy->val = temp->val;
				temp = temp->next;
			}
		}

		//todos os métodos de com "int pos" funcionam como vetor (elementos de 0 até tamanho - 1)
		int Size() {return tam;};

		bool GetElem(int pos, type &get) { //retorna se posição é válida. &get armazenará valor
			if (bhvr == LISTASIMPLES && pos >= 0 && pos < tam) {
				node *temp = head;
				for (int i = 0; i <= pos; i++) {
					temp = temp->next;
				}
				get = temp->val;
				return true;
			}
			return false;
		};

		bool GetElem(type &get) { //retorna se lista ou pilha possui elemento top. &get armazenará valor
			if (tam > 0) {
				if (bhvr == PILHA) {
					get = head->next->val;
					return true;
				}
				else if (bhvr == FILA) {
					node* temp = head->next;
					while (temp->next != NULL) {
						temp = temp->next;
					}
					get = temp->val;
					return true;

				}
				return false;
			}
			return false;
		}

		int Search(type val) { //retorna posição da primeira instância de val
			//-1: não existe elemento
			if (tam > 0) {
				node *temp = head->next;
				int i = 0;
				do {
					if (temp->val == val)
						return i;
					i++;
					temp = temp->next;
				} while (temp->next != NULL);
				return -1;
			}
			return -1;
		};
		
		bool Insert(int pos, type val) { //retorna se inserção OK. Insere val em lista simples
			if (pos >= 0 && pos <= tam && bhvr == LISTASIMPLES) {
				node *temp = head;
				for (int i = 0; i < pos; i++) {
					temp = temp->next;
				}
				node *novo = new node;
				novo->val = val;
				novo->next = temp->next;
				temp->next = novo;
				tam++;
				return true;
			}
			return false;
		}

		bool Insert(type val) { //retorna se inserção OK. Insere val em filas e pilhas
			if (tam >= 0 && (bhvr == PILHA || bhvr == FILA)) {
				node *novo = new node;
				while (novo == head) { //I HAVE NO IDEA OF WHY THIS HAPPENS
					novo = new node;
				}
				novo->val = val;
				novo->next = head->next;
				head->next = novo;
				tam++;
				return true;
			}
			return false;
		}

		bool Remove(unsigned int pos) { //retorna se remoção OK. Não retorna valor. Funciona para listas
			if (pos >= 0 && pos < tam && bhvr == LISTASIMPLES) {
				node* ant = head;
				node* temp = head->next;
				for (int i = 0; i < pos; i++) {
					temp = temp->next;
					ant = ant->next;
				}
				ant->next = temp->next;
				delete temp;
				tam--;
				return true;
			}
			return false;
		};

		bool Remove() {
			if (tam > 0 && head->next != NULL) {
				if (bhvr == PILHA) {
					node *temp = head->next;
					head->next = temp->next;
					delete temp;
					tam--;
					return true;
				}
				else if (bhvr == FILA) {
					node *bef = head; //before
					node *fow = head->next; //foward
					while (fow->next != NULL) {
						fow = fow->next;
						bef = bef->next;
					}
					delete fow;
					bef->next = NULL;
					tam--;
					return true;
				}
				return false;
			}
			return false;
		}

		bool Remove(int pos, type &get) { //retorna se remoção OK. &get armazenará valor da posição
			if (pos >= 0 && pos < tam && bhvr == LISTASIMPLES) {
				node* ant = head;
				node* temp = head->next;
				for (int i = 0; i < pos; i++) {
					temp = temp->next;
					ant = ant->next;
				}
				ant->next = temp->next;
				get = temp->val;
				delete temp;
				tam--;
				return true;
			}
			return false;
		};

		bool Remove(type &get) { //se usar referência e type = int vai dar conflito com Remove(int pos)
		//salvar imediatamente conteúdo de get em outra variável caso seja ponteiro
			if (tam > 0) {
				if (bhvr == PILHA) {
					node *temp = head->next;
					head->next = temp->next;
					get = temp->val;
					delete temp;
					tam--;
					return true;
				}
				else if (bhvr == FILA) {
					node *bef = head; //before
					node *fow = head->next; //foward
					while (fow->next != NULL) {
						fow = fow->next;
						bef = bef->next;
					}
					get = fow->val;
					delete fow;
					bef->next = NULL;
					tam--;
					return true;
				}
				return false;
			}
			return false;
		}

		void Print(char separator = ' ') {
			node *temp = head->next;
			std::cout << std::endl;
			while (temp != NULL) {
				std::cout << temp->val << separator;
				temp = temp->next;
			}
			std::cout << std::endl;
		}*/
	};

	#include "lista.inl"
#endif