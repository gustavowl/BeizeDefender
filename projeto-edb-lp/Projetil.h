#ifndef _PROJETIL_H_
#define _PROJETIL_H_

#include "GameObject.h"

class Projetil : public go::GameObject {
	//velocidade padrão da bala: 30
	//raio padrão da bala: 2
	//walktype: linear
	private:
		unsigned int Dano;
		bool Destruido;

		void CalcularCoordenadasFinais(unsigned int OrigemX, unsigned int OrigemY, unsigned int &DestinoX,
			unsigned int &DestinoY); //calcula coordenada de destino em que sairá da arena

	public:
	Projetil(unsigned int PositionX, unsigned int PositionY, unsigned int DestinoX, unsigned int DestinoY);

			/*GameObject(unsigned int PositionX, unsigned int PositionY, unsigned int Velocidade, 
			unsigned int DestinoX, unsigned int DestinoY, unsigned int Raio, WalkType TipoMov);*/
	Projetil(unsigned int PositionX, unsigned int PositionY, unsigned int Velocidade, unsigned int DestinoX,
		unsigned int DestinoY, unsigned int Raio, unsigned int Dano);
	
	void operator=(const GameObject &GameObj);
	void Mover();
	void Destruir();
	bool GetDesruido();
	unsigned int GetDano();
};

#endif