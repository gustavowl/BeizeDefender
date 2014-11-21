#ifndef _DROP_H_
#define _DROP_H_

#include "GameObject.h"
#include "Player.h"
#include "ListaEncadeada/lista.h"

class Drop : public go::GameObject{
	private:
		int energia;
		int tempo;

	public:
		Drop();
		Drop(int energia, int XOrigem, int YOrigem);
		//~Drop();
		void operator=(const GameObject &GameObj);
		void Draw(Lista<Drop*> &fila_cafe);
		void Pegar(Player &p, Lista<Drop*> &fila_cafe);
		int VerificarColisao(Player &p, Drop &cafe);
		int GetEnergia();
};

#endif