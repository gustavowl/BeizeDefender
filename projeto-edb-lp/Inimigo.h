#ifndef _INIMIGO_H_
#define _INIMIGO_H_

#include "GameObject.h"
#include "ListaEncadeada/lista.h"
#include "Projetil.h"
#include "Personagem.h"

class Inimigo : public Personagem{
	//definição do intervalo padrao abaixo levou em conta 30 fps
	#define INTERVALOTIROPADRAO 30

	private:
		int Tipo; // se sera normal, boss ou outra coisa //por enquanto armazena lixo
		int Municao; // quantidade de municao que ele vai atirar
		int Drop;
		bool CalcularProxDest;
		int InterveloTiro; //atira a cada intervalo, medido em frames
		int ProxTiro; //armazena frames restantes para próximo tiro
		//bool destruido; //tem vida
		//Lista<Projetil*> Projeteis; //tem em personagem
	public:
		//Inimigo();
		//Inimigo( unsigned int PositionX,  unsigned int PositionY);
		Inimigo(int velocidade, int vida); //gera posição inicial randômicamente (nas bordas)
		//gera posição inicial randômicamente (nas bordas)
		//primeiro_tiro: frames até dar o primeiro tiro
		Inimigo(int velocidade, int vida, int raio, int municao, int intervelo_tiro,
			int primeiro_tiro, Projetil projetil_base);
		void Distancia(Personagem p, go::GameObject base);
		int Dropar();
		void Draw();
		void operator=(const Personagem &persona);
		void AtualizarDestino(unsigned int DestinoX, unsigned int DestinoY);
		void Atirar(const Personagem &p, const go::GameObject &base);
};

#endif