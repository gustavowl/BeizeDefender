#ifndef _PROJETIL_H_
#define _PROJETIL_H_

#include "GameObject.h"

class Projetil : public go::GameObject {
	//velocidade padrão da bala: 30
	//raio padrão da bala: 2
	//walktype: linear
	private:
		unsigned int dano = 2;

	public:
	Projetil(unsigned int PositionX, unsigned int PositionY, unsigned int DestinoX, unsigned int DestinoY);

			/*GameObject(unsigned int PositionX, unsigned int PositionY, unsigned int Velocidade, 
			unsigned int DestinoX, unsigned int DestinoY, unsigned int Raio, WalkType TipoMov);*/
	Projetil(unsigned int PositionX, unsigned int PositionY, unsigned int Velocidade, unsigned int DestinoX,
		unsigned int DestinoY, unsigned int Raio, unsigned int Dano);
	
	void operator=(const GameObject &GameObj);
	void Mover();
};

#endif