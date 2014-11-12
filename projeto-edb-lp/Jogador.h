#ifndef _JOGADOR_H_
#define _JOGADOR_H_

#include <string>

class Jogador {

	private:
		std::string nome;
		int kills;
		int municao;


	public:
		void RecuperarVida();
		void PegarOuro();
};

#endif