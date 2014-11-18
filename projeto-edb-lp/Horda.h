#ifndef _HORDA_H_
#define _HORDA_H_

#include "Inimigo.h"
#include "Personagem.h"
#include "GameObject.h"


class Horda {

	private:
		int quantInimigos;
		int id;
		Lista<Inimigo*> listaInimigos;


	public:
		Horda(int quantidade, int id);
		~Horda();
		void Draw();
		void Atirar(Personagem p);
		void Mover(Personagem p, int base_raio);
		//retorna dano causado pelos projéteis dos inimigos em obj
		int VerificarColisaoProjInimObj(const go::GameObject obj);
		/*Faz colisão dos projéteis de persona com Inimigos, calcula dano
		e remove inimigos derrotados*/
		void VerificarColisaoProjPersInim(Personagem &persona);
		//retorna se todos os inimigos da Horda foram destruídos
		bool Destruida();

};

#endif