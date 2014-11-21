#ifndef _HORDA_H_
#define _HORDA_H_

#include "Inimigo.h"
#include "Personagem.h"
#include "GameObject.h"
#include "Projetil.h"
#include "Drop.h"


class Horda {

	private:
		Lista<Inimigo*> listaInimigos;


	public:
		Horda(); //cria horda fazia
		Horda(int quantidade);
		Horda(int quantidade, int velocidade, int vida, int raio, int municao, int intervelo_tiro,
			int primeiro_tiro, Projetil projetil_base);
		~Horda();
		void Draw();
		void Atirar(Personagem p, go::GameObject base);
		void Mover(Personagem p, go::GameObject base);
		//retorna dano causado pelos projéteis dos inimigos em obj
		int VerificarColisaoProjInimObj(const go::GameObject obj);
		/*Faz colisão dos projéteis de persona com Inimigos, calcula dano
		e remove inimigos derrotados*/
		void VerificarColisaoProjPersInim(Personagem &persona, Lista<Drop*> &fila_cafe);
		//retorna se todos os inimigos e projéteis da Horda foram destruídos
		bool Destruida();

};

#endif