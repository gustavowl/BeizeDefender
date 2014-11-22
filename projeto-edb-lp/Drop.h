#ifndef _DROP_H_
#define _DROP_H_

#include "GameObject.h"
#include "Player.h"
#include "ListaEncadeada/lista.h"

class Drop : public go::GameObject{
	private:
		int energia;
		int tempo;
		int tempoEspera; // Tempo que o drop vai ficar na tela

	public:
		Drop();
		Drop(int energia, int XOrigem, int YOrigem);
		//~Drop();
		void operator=(const GameObject &GameObj);
		void Draw(Lista<Drop*> &fila_cafe); // Desenha a lista de drop
		void Pegar(Player &p, Lista<Drop*> &fila_cafe); 
		int VerificarColisao(Player &p, Drop &cafe); // Verifica a colisão do Player com o Drop
		int GetEnergia();
		int PassarTempo(); //decrementa o tempo de espera
};

#endif