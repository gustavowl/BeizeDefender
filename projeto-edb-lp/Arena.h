#ifndef _ARENA_H_
#define _ARENA_H_

#include "Jogador.h"
#include "Base.h"

class Arena {

	private:
		//int altura;
		//int largura;
		Base tower; // achei melhor do que chamar de base
		int dificuldade;

		void ProximaWave();
		void RegenerarTodos();

	public:
		void LoopPrincipal();
};

#endif