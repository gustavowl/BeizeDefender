#ifndef _INIMIGO_H_
#define _INIMIGO_H_

#include "Personagem.h"

class Inimigo {

	private:
		int tipo;
		Personagem inimigo;

	public:
		int Dropar();
};

#endif