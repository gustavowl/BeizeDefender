#ifndef _MOVIMENTACAO_H_
#define _MOVIMENTACAO_H_

class Movimentacao {

	private:
		int posicaoX;
		int posicaoY;
		int velocidade;
		int destinoX;
		int destinoY;
		int maxX;
		int maxY;

	public:
		void Mover();
};

#endif