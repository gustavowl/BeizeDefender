#ifndef _INIMIGO_H_
#define _INIMIGO_H_

#include "GameObject.h"

class Inimigo : public go::GameObject{
	//velocidade padrão da bala: 1
	//raio padrão do inimigo: 10
	//walktype: linear

	private:
		int tipo; // se sera normal, boss ou outra coisa
		int ouro; // quantidade de ouro que ele vai dropar
		bool destruido;

	public:
		//Inimigo();
		Inimigo( int PositionX,  int PositionY);
		void Distancia(GameObject b);
		int Dropar();
		void Mover();
		void Draw();
		void operator=(const GameObject &GameObj);
		void Atirar();
		void AtualizarDestino(unsigned int DestinoX, unsigned int DestinoY);
};

#endif