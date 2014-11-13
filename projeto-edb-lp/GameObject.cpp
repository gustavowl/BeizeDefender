#include "GameObject.h"

virtual void GameObject::Mover() {
	//PUT THE DEFINITION HERE
}

unsigned int GetMaxX() {
	return MaxX;
}
unsigned int GetMaxY() {
	return MaxY;
}

GameObject::GameObject() { //cria "objeto vazio"
	PositionX = PositionY = Velocidade = DestinoX = DestinoY = 0;
	Raio = 1;
}

GameObject::GameObject(unsigned int MaximoX, unsigned int MaximoY) { //gera posição inicial randômica
//só permite alterar o tamanho da arena uma vez e ao criar um objeto tipo GameObject (não herdados)
	if (MaxX == 0 && MaxY == 0 && MaximoX > 0 && MaximoY) { //só permite alterar os valores umas vez
		MaxX = MaximoX;
		MaxY = MaximoY;

		PositionX = PositionY = Velocidade = DestinoX = DestinoY = 0;
		Raio = 1;
	}
}

GameObject(unsigned int Velocidade, unsigned int Raio) { //gera posição inicial randômica
	if (MaxX > 0 && MaxY > 0 && Raio > 0) {
		//0: borda sup | 1: borda dir | 2: borda inf | 3: borda esq
		int r = rand() % 4;
		switch (r) {
			case 0:  //posição aleatória na borda superior
				PosicaoY = 0;
				PosicaoX = rand() % (MaxX + 1);
				break;
			case 1: //posição aleatória na borda da direita
				PositionX = MaxX;
				PositionY = rand() % (MaxY + 1);
				break;
			case 2: //posição aleatória na borda inferior
				PosicaoX = rand() % (MaxX + 1);
				PosicaoY = MaxY;
				break;
			case 3: //posição aleatória na borda da esquerda
				PosicaoX = 0;
				PositionY = rand() % (MaxY + 1);
				break;
		}

		this->Velocidade = Velocidade;
		DestinoX = PosicaoX;
		DestinoY = PosicaoY;
		this->Raio = Raio;

	}
}

GameObject(unsigned int PositionX, unsigned int PositionY, unsigned int Velocidade, unsigned int Raio) {
	//verifica se valores de entrada são válidos
	if (MaxX > 0 && MaxY > 0 && PositionX <= MaxX && PositionY <= MaxY && Raio > 0) {
		PosicaoX = PositionX;
		PosicaoY = PositionY;
		this->Velocidade = Velocidade;
		DestinoX = PosicaoX;
		DestinoY = PosicaoY;
		this->Raio = Raio;
	}
}
GameObject(unsigned int PositionX, unsigned int PositionY, unsigned int Velocidade, 
	unsigned int DestinoX, unsigned int DestinoY, unsigned int Raio) {

	//verifica se valores de entrada são válidos
	if (MaxX > 0 && MaxY > 0 && PositionX <= MaxX && PositionY <= MaxY &&
		DestinoX <= MaxX && DestinoY <= MaxY && Raio > 0) {
		PosicaoX = PositionX;
		PosicaoY = PositionY;
		this->Velocidade = Velocidade;
		this->DestinoX = DestinoX;
		this->DestinoY = DestinoY;
		this->Raio = Raio;
	}
}

~GameObject() {
	//what goes inside?
}