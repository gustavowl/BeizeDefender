template <class type>
FilaDupl<type>::FilaDupl() {
	first = NULL;
	tam = 0;
	lastget = NULL;
}

template <class type>
FilaDupl<type>::FilaDupl(const FilaDupl &fila_dupl) { //construtor de cópia (profunda)
	*this = fila_dupl; //chamada operator=
}
//destructor
template <class type>
FilaDupl<type>::~FilaDupl() {
	while (Remove());
	delete first;
}

//operator =
template <class type>
FilaDupl<type>& FilaDupl<type>::operator=(const FilaDupl &fila_dupl) {
	//garante remoção de todos os valores reservados na lista, caso haja algum
	while ( Remove() );

	tam = fila_dupl.tam;
	if ( tam == 0 ) {
		lastget = NULL;
		first = NULL;
	}
	else {
		node* copy;
		//percorrerá fila_dupl
		node* fila_dupl_runner = fila_dupl.first;
		node* ant; //armazena node anteriormente copiado

		for (int i = 0; i <= tam; i++) {
			if ( i < tam )
				copy = new node;
			else
				copy = first;


			copy->val = fila_dupl_runner->val;

			if ( i == 0) {
				first = copy;
			}
			else {
				ant->prev = copy; //elemento ant vem primeiro na fila
				copy->next = ant; //elemento copy está "atrás" de ant
			}
			ant = copy;
			fila_dupl_runner = fila_dupl_runner->prev;
		}
		lastget = first;
	}
}

//todos os métodos de com "int pos" funcionam como vetor (elementos de 0 até tamanho - 1)
template <class type>
int FilaDupl<type>::Size() {return tam;};

template <class type>
bool  FilaDupl<type>::GetFirstElem(type &get) {
	if (tam > 0) {
		lastget = first;
		get = first->val;
		return true;
	}
	return false;
}

template <class type>
bool FilaDupl<type>::GetNextElem(type &get) { //retorna se lista ou pilha possui elemento top. &get armazenará valor
	if (tam > 0) {
		lastget = lastget->next;
		get = lastget->val;
		return true;
	}
	return false;
}

template <class type>
bool FilaDupl<type>::GetPrevElem(type &get) {
	if (tam > 0) {
		lastget = lastget->prev;
		get = lastget->val;
		return true;
	}
	return false;
}

template <class type>
bool FilaDupl<type>::Insert(type val) { //retorna se inserção OK. Insere val em filas e pilhas

	if (tam > 0) {
		node *novo = new node;
		novo->val = val;
		novo->prev = first;
		novo->next = first->next; //próximo do novo será o último
		first->next = novo; //último agora será o novo
		novo->next->prev = novo; //último agora será o penúltimo
		tam++;
		return true;
	}
	else if (tam == 0) {
		first = new node;
		first->val = val;
		first->prev = first;
		first->next = first;
		lastget = first;
		tam++;
		return true;
	}
	return false;
}

template <class type>
bool FilaDupl<type>::Remove() {
	if (tam > 0) {
		//remove o primeiro da fila
		if (tam > 1) {
			node *temp = first;
			first->prev->next = first->next; //próximo do segundo = último
			first->next->prev = first->prev; //anterior do último = segundo
			//atualiza lastget para segundo se for igual ao primeiro, já que será deletado
			if ( lastget == first )
				lastget = first->prev;

			first = first->prev; //agora primeiro = segundo
			delete temp; //deleta o antigo primeiro, que foi alocado dinamicamente
		}
		else {
			delete first; //deleta alocação dinâmica
			first = NULL; //aponta para nulo
			lastget = NULL;
		}
		tam--;
		return true;
	}
	return false;
}

template <class type>
bool FilaDupl<type>::Remove(type &get) { //se usar referência e type = int vai dar conflito com Remove(int pos)
//salvar imediatamente conteúdo de get em outra variável caso seja ponteiro
	get = first->val;
	return Remove();
}