#ifndef _INIMIGO_H_
#define _INIMIGO_H_

#include "ListaEncadeada/lista.h"
#include "Projetil.h"
#include "Personagem.h"

class Inimigo : public Personagem{
	//definição do intervalo padrao abaixo levou em conta 30 fps
	#define INTERVALOTIROPADRAO 20

	private:
		int Tipo; // se sera normal, boss ou outra coisa //por enquanto armazena lixo
		int Municao; // quantidade de municao que ele vai dropar
		bool CalcularProxDest;
		int InterveloTiro; //atira a cada intervalo, medido em frames
		int ProxTiro; //armazena frames restantes para próximo tiro
		//bool destruido; //tem vida
		//Lista<Projetil*> Projeteis; //tem em personagem
	public:
		//Inimigo();
		//Inimigo( unsigned int PositionX,  unsigned int PositionY);
		Inimigo(int velocidade, int vida); //gera posição inicial randômicamente (nas bordas)
		Inimigo(int velocidade, int vida, int municao, int intervelo_tiro); //gera posição inicial randômicamente (nas bordas)
		void Distancia(Personagem p, int base_raio);
		int Dropar();
		void Draw();
		void operator=(const Personagem &persona);
		void AtualizarDestino(unsigned int DestinoX, unsigned int DestinoY);
		void Atirar(const Personagem &p);
};

#endif