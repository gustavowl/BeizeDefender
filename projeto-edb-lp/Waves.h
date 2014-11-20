#ifndef _WAVES_H_
#define _WAVES_H_

#include "Horda.h"
#include "ListaEncadeada/lista.h"
#include "GameObject.h"
#include "Personagem.h"

class Waves {

	private:
		//aponta pra horda que está no campo de batalha
		Horda* hordaAtual;
		//necessário que o comportamento seja fila, requerido no construtor
		//é ponteiro para alterar valor da lista do local onde foi chamado,
		//fazendo mudança nos dois locais
		Lista<Horda*> *filaHorda;
		//tempo de espera é medido em frames. Espera por = tempoEspera + 1 frames
		//tempo de espera para próxima horda. Se 0, horda está na arena
		int tempoEspera;
		//armazena tempo de espera para aparecimento das próximas hordas (contidas na fila)
		//tempo de espera é medido em frames
		//é ponteiro para alterar valor da lista do local onde foi chamado,
		//fazendo mudança nos dois locais
		Lista<int> *filaTempoEspera; //necessário que o comportamento seja fila também

	public:
		//exige fila de horda e de tempo de espera com o mesmo tamanho
		Waves( Lista<Horda*> &fila_horda, Lista<int> &fila_tempo_espera );
		~Waves();
		//reduz tempo de espera, se tempo = 0 adiciona horda no campo de batalha
		//retorna true caso esteja esperando e false caso horda esteja no campo de batalha
		bool EsperandoProximaHorda();
		bool Destruida(); //retorna se a wave foi destruída
		//faz com que inimigos da horda atual se movam
		void Mover(Personagem p, go::GameObject base);
		//Faz com que inimigos da horda atual atirem
		void Atirar(Personagem p, go::GameObject base);
		//retorna dano causado pelos projéteis dos inimigos em obj
		int VerificarColisaoProjInimObj(const go::GameObject obj);
		/*Faz colisão dos projéteis de persona com Inimigos, calcula dano
		e remove inimigos derrotados*/
		void VerificarColisaoProjPersInim(Personagem &persona);

};

#endif