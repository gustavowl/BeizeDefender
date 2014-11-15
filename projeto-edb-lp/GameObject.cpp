#include "GameObject.h"
#include <cstdlib>
#include <math.h>

GameObject::GameObject() { //cria "objeto vazio"
	XOrigem = YOrigem = XAtual = YAtual = Velocidade = XDestino = YDestino = 0;
	Raio = 1;
	TipoMovimento = STATIC;
	FrameAtual = TotalFrames = 0;
}

GameObject::GameObject(unsigned int MaximoX, unsigned int MaximoY) { //inicializa tamanho da arena
	if (MaxX == 0 && MaxY == 0 && MaximoX > 0 && MaximoY > 0) { //verifica se adiciona e valores de entrada válidos
		MaxX = MaximoX;
		MaxY = MaximoY;
		TipoMovimento = STATIC;

		XOrigem = YOrigem = XAtual = YAtual = Velocidade = XDestino = YDestino = 0;
		FrameAtual = TotalFrames = 0;
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
		FrameAtual = TotalFrames = 0;
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
		FrameAtual = TotalFrames = 0;
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
		//calculando quantidade de frames para mover
		//calcula a distância por pitágoras
		float dist = sqrt( pow(XOrigem - XDestino, 2) + pow(YOrigem - YDestino, 2) );
		//usa a distância e a velocidade para saber a quantidade de frames
		if (Velocidade > 0)
			TotalFrames = (unsigned int)(dist / Velocidade);
		else
			TotalFrames = 0;
		//zera frame atual
		FrameAtual = 0;
	}
}
	
GameObject::~GameObject() {
	//what goes inside?
}

void GameObject::Mover() {
	if ( TipoMovimento != STATIC ) {
		if ( FrameAtual <= TotalFrames && TotalFrames > 0 ) {
			float t = (float)FrameAtual / TotalFrames; //variável utilizada para calcular interpolação
			if ( TipoMovimento == SMOOTH )
				t = pow(t, 2) * ( 3 - 2 * t ); //faz com que passo seja smooth
			//atualiza posição atual, leva em conta posição de origem e destino
			XAtual = round( XDestino * t + XOrigem * (1 - t) );
			YAtual = round( YDestino * t + YOrigem * (1 - t) );
		}
	}
}

void GameObject::AtualizarDestino(unsigned int DestinoX, unsigned int DestinoY) {
	XOrigem = XAtual;
	YOrigem = YAtual;
	XDestino = DestinoX;
	YDestino = DestinoY;
	//calcula a distância por pitágoras
	float dist = sqrt( pow(XOrigem - XDestino, 2) + pow(YOrigem - YDestino, 2) );
	//usa a distância e a velocidade para saber a quantidade de frames
	if (Velocidade > 0)
		TotalFrames = (unsigned int)(dist / Velocidade);
	else
		TotalFrames = 0;
	//zera frame atual
	FrameAtual = 0;
}

unsigned int GameObject::GetMaxX() {
	return MaxX;
}
unsigned int GameObject::GetMaxY() {
	return MaxY;
}

void GameObject::GetPosicaoAtual(unsigned int &x, unsigned int &y) {
	x = XAtual;
	y = YAtual;
}

unsigned int GameObject::GetXAtual() {
	return XAtual;
}

unsigned int GameObject::GetYAtual() {
	return YAtual;
}