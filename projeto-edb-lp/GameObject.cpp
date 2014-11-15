#include "GameObject.h"
#include <cstdlib>

GameObject::GameObject() { //cria "objeto vazio"
	XOrigem = YOrigem = XAtual = YAtual = Velocidade = XDestino = YDestino = 0;
	Raio = 1;
}

GameObject::GameObject(unsigned int MaximoX, unsigned int MaximoY) { //inicializa tamanho da arena
	if (MaxX == 0 && MaxY == 0 && MaximoX > 0 && MaximoY > 0) { //verifica se adiciona e valores de entrada válidos
		MaxX = MaximoX;
		MaxY = MaximoY;

		XOrigem = YOrigem = XAtual = YAtual = Velocidade = XDestino = YDestino = 0;
		Raio = 1;
	}
}

GameObject::GameObject(unsigned int Velocidade, unsigned int Raio, WalkType TipoMov) { //pode gerar posição inicial randômica
	if (MaxX > 0 && MaxY > 0 && Raio > 0) {
		//0: borda sup | 1: borda dir | 2: borda inf | 3: borda esq
		int r = rand() % 4;
		switch (r) {
			case 0:  //posição aleatória na borda superior
				YOrigem = 0;
				XOrigem = rand() % (MaxX + 1);
				break;
			case 1: //posição aleatória na borda da direita
				XOrigem = MaxX;
				YOrigem = rand() % (MaxY + 1);
				break;
			case 2: //posição aleatória na borda inferior
				XOrigem = rand() % (MaxX + 1);
				YOrigem = MaxY;
				break;
			case 3: //posição aleatória na borda da esquerda
				XOrigem = 0;
				YOrigem = rand() % (MaxY + 1);
				break;
		}
		//atualiza restante dos dados
		this->Velocidade = Velocidade;
		XDestino = XOrigem;
		YDestino = YOrigem;
		XAtual = XOrigem;
		YAtual = YOrigem;
		this->Raio = Raio;
		TipoMovimento = TipoMov;
	}
}

GameObject::GameObject(unsigned int PositionX, unsigned int PositionY, unsigned int Velocidade,
	unsigned int Raio, WalkType TipoMov) {
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
		TipoMovimento = TipoMov;
	}
}
GameObject::GameObject(unsigned int PositionX, unsigned int PositionY, unsigned int Velocidade, 
	unsigned int DestinoX, unsigned int DestinoY, unsigned int Raio, WalkType TipoMov) {

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
		TipoMovimento = TipoMov;
	}
}
	
GameObject::~GameObject() {
	//what goes inside?
}

void GameObject::Mover() {
	//PUT THE DEFINITION HERE
}

unsigned int GameObject::GetMaxX() {
	return MaxX;
}
unsigned int GameObject::GetMaxY() {
	return MaxY;
}