#ifndef _Personagem_H_
#define _Personagem_H_

#include <string>
#include "Projetil.h"
#include "Movimentacao.h"

class Personagem {

	private:
		int ouro;
		int vida;
		Projetil ataque;
		std::string imagem;
		Movimentacao move;

	public:
		void Atirar();
};

#endif