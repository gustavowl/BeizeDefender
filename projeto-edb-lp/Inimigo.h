#ifndef _INIMIGO_H_
#define _INIMIGO_H_

#include "ListaEncadeada/lista.h"
#include "Projetil.h"
#include "Personagem.h"

class Inimigo : public Personagem{
	//velocidade padrão da bala: 1
	//raio padrão do inimigo: 10
	//walktype: linear

	private:
		int Tipo; // se sera normal, boss ou outra coisa //por enquanto armazena lixo
		int Municao; // quantidade de municao que ele vai dropar
		bool CalcularProxDest;
		//bool destruido; //tem vida
		//Lista<Projetil*> Projeteis; //tem em personagem
	public:
		//Inimigo();
		//Inimigo( unsigned int PositionX,  unsigned int PositionY);
		Inimigo(int velocidade, int vida); //gera posição inicial randômicamente (nas bordas)
		Inimigo(int velocidade, int vida, int municao); //gera posição inicial randômicamente (nas bordas)
		void Distancia(Personagem p, int base_raio);
		int Dropar();
		void Draw();
		void operator=(const Personagem &persona);
		void AtualizarDestino(unsigned int DestinoX, unsigned int DestinoY);
		void Atirar(const Personagem &p);
		Lista<Projetil*> GetProjeteisToDraw();
};

#endif