#ifndef _HORDA_H_
#define _HORDA_H_

#include "Inimigo.h"
#include "Player.h"
#include "GameObject.h"


class Horda {

	private:
		int quantInimigos;
		int id;
		Lista<Inimigo*> listaInimigos;


	public:
		Horda(int quantidade, int id);
		void LiberarInimigos();
		void Atirar(Personagem p);
		void Mover(Personagem p, int base_raio);
		int VerificarColisao(const go::GameObject obj);

};

#endif