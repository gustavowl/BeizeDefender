#ifndef _HORDA_H_
#define _HORDA_H_

#include "Inimigo.h"
#include "Player.h"


class Horda {

	private:
		int quantInimigos;
		int id;
		Lista<Inimigo*> listaInimigos;

	public:
		Horda(int quantidade, int id);
		void LiberarInimigos();
		void Atirar();
		void Mover(Player p, int base_raio);

};

#endif