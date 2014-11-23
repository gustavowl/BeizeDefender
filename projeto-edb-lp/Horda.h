#ifndef _HORDA_H_
#define _HORDA_H_

#include "Inimigo.h"
#include "Personagem.h"
#include "GameObject.h"
#include "Projetil.h"
#include "Drop.h"
#include "Player.h"


class Horda {

	private:
		int id;
		Lista<Inimigo*> listaInimigos;


	public:
		Horda(); //cria horda fazia
		Horda(int quantidade);
		Horda(int idHorda, int quantidade, int velocidade, int vida, int raio, int municao, int intervalo_tiro,
			int primeiro_tiro, Projetil projetil_base, int danoFisico);
		~Horda();
		void Draw();
		void Atirar(Personagem p, go::GameObject base);
		void Mover(Player &p, go::GameObject base);
		//retorna dano causado pelos projéteis dos inimigos em obj
		int VerificarColisaoProjInimObj(const go::GameObject obj);
		/*Faz colisão dos projéteis de persona com Inimigos, calcula dano
		e remove inimigos derrotados*/
		void VerificarColisaoProjPersInim(Personagem &persona, Lista<Drop*> &fila_cafe);
		//retorna se todos os inimigos e projéteis da Horda foram destruídos
		bool Destruida();
		int GetId();

};

#endif