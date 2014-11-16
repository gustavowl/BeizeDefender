#ifndef _INIMIGO_H_
#define _INIMIGO_H_

#include "GameObject.h"
#include "ListaEncadeada/lista.h"
#include "Projetil.h"
#include "Player.h"

class Inimigo : public go::GameObject{
	//velocidade padrão da bala: 1
	//raio padrão do inimigo: 10
	//walktype: linear

	private:
		int tipo; // se sera normal, boss ou outra coisa
		int municao; // quantidade de municao que ele vai dropar
		bool destruido;
		Lista<Projetil*> Projeteis;
	public:
		//Inimigo();
		Inimigo( int PositionX,  int PositionY);
		void Distancia(Player b);
		int Dropar();
		void Mover();
		void Draw();
		void operator=(const GameObject &GameObj);
		void AtualizarDestino(unsigned int DestinoX, unsigned int DestinoY);
		void Atirar();
		Lista<Projetil*> GetProjeteisToDraw();
};

#endif