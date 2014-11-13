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
	PositionX = PositionY = Velocidade = XDestino = YDestino = 0;
	Raio = 1;
}

GameObject::GameObject(unsigned int MaximoX, unsigned int MaximoY) { //gera posição inicial randômica
//só permite alterar o tamanho da arena uma vez e ao criar um objeto tipo GameObject (não herdados)
	if (MaxX == 0 && MaxY == 0 && MaximoX > 0 && MaximoY) { //só permite alterar os valores umas vez
		MaxX = MaximoX;
		MaxY = MaximoY;

		PositionX = PositionY = Velocidade = XDestino = YDestino = 0;
		Raio = 1;
	}
}

GameObject(unsigned int Velocidade, unsigned int Raio) { //gera posição inicial randômica
	if (MaxX > 0 && MaxY > 0 && Raio > 0) {
		//0: borda sup | 1: borda dir | 2: borda inf | 3: borda esq
		int r = rand() % 4;
		switch (r) {
			case 0:  //posição aleatória na borda superior
				YOrigem = 0;
				XOrigem = rand() % (MaxX + 1);
				break;
			case 1: //posição aleatória na borda da direita
				PositionX = MaxX;
				PositionY = rand() % (MaxY + 1);
				break;
			case 2: //posição aleatória na borda inferior
				XOrigem = rand() % (MaxX + 1);
				YOrigem = MaxY;
				break;
			case 3: //posição aleatória na borda da esquerda
				XOrigem = 0;
				PositionY = rand() % (MaxY + 1);
				break;
		}

		this->Velocidade = Velocidade;
		XDestino = XOrigem;
		YDestino = YOrigem;
		XAtual = XOrigem;
		YAtual = YOrigem;
		this->Raio = Raio;

	}
}

GameObject(unsigned int PositionX, unsigned int PositionY, unsigned int Velocidade, unsigned int Raio) {
	//verifica se valores de entrada são válidos
	if (MaxX > 0 && MaxY > 0 && PositionX <= MaxX && PositionY <= MaxY && Raio > 0) {
		XOrigem = PositionX;
		YOrigem = PositionY;
		this->Velocidade = Velocidade;
		XDestino = XOrigem;
		YDestino = YOrigem;
		XAtual = XOrigem;
		YAtual = YOrigem;
		this->Raio = Raio;
	}
}
GameObject(unsigned int PositionX, unsigned int PositionY, unsigned int Velocidade, 
	unsigned int DestinoX, unsigned int DestinoY, unsigned int Raio) {

	//verifica se valores de entrada são válidos
	if (MaxX > 0 && MaxY > 0 && PositionX <= MaxX && PositionY <= MaxY &&
		DestinoX <= MaxX && DestinoY <= MaxY && Raio > 0) {
		XOrigem = PositionX;
		YOrigem = PositionY;
		this->Velocidade = Velocidade;
		XAtual = XOrigem;
		YAtual = YOrigem;
		XDestino = DestinoX;
		YDestino = DestinoY;
		this->Raio = Raio;
	}
}

~GameObject() {
	//what goes inside?
}