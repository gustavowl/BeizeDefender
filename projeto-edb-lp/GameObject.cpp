#include "GameObject.h"
#include <cstdlib>
#include <cmath>
#include <ctime>

using namespace go;

unsigned int GameObject::MaxY = 0;
unsigned int GameObject::MaxX = 0;

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

//gera posição inicial randômica nas bordas
GameObject::GameObject(unsigned int Velocidade, unsigned int Raio, WalkType TipoMov, 
	SpManip::SpriteManip sprites) {

	if (MaxX > 0 && MaxY > 0 && Raio > 0) {
		//0: borda sup | 1: borda dir | 2: borda inf | 3: borda esq
		 
		srand(time(NULL) * rand());

		int r =  rand() % 4;
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
		Sprites = sprites;
	}
}

GameObject::GameObject(unsigned int PositionX, unsigned int PositionY, unsigned int Velocidade,
	unsigned int Raio, WalkType TipoMov, SpManip::SpriteManip sprites) {
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
		Sprites = sprites;
	}
}
GameObject::GameObject(unsigned int PositionX, unsigned int PositionY, unsigned int Velocidade, 
	unsigned int DestinoX, unsigned int DestinoY, unsigned int Raio, WalkType TipoMov,
	SpManip::SpriteManip sprites) {

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
		int xo, xd, yo, yd;
		xo = XOrigem; xd = XDestino; yo = YOrigem; yd = YDestino;
		//unsigned int a conta pode dar errada (130 - 150), por exemplo
		//variáveis int criadas pois com conversão direta não estava funcionando
		float dist = sqrt( pow(xo - xd, 2) + pow(yo - yd, 2) );
		//usa a distância e a velocidade para saber a quantidade de frames
		if (Velocidade > 0)
			TotalFrames = (unsigned int)(dist / Velocidade);
		else
			TotalFrames = 0;
		//zera frame atual
		FrameAtual = 0;
		Sprites = sprites;
	}
}
	
GameObject::~GameObject() {
	
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
			FrameAtual++;
		}
	}
}

void GameObject::AtualizarDestino(unsigned int DestinoX, unsigned int DestinoY) {
	if (DestinoX != XDestino || DestinoY != YDestino) {
		XOrigem = XAtual;
		YOrigem = YAtual;
		XDestino = DestinoX;
		YDestino = DestinoY;
		//calcula a distância por pitágoras
		int xo, xd, yo, yd;
		xo = XOrigem; xd = XDestino; yo = YOrigem; yd = YDestino;
		//unsigned int a conta pode dar errada (130 - 150), por exemplo
		//variáveis int criadas pois com conversão direta não estava funcionando
		float dist = sqrt( pow(xo - xd, 2) + pow(yo - yd, 2) );
		//usa a distância e a velocidade para saber a quantidade de frames
		if (Velocidade > 0)
			TotalFrames = (unsigned int)(dist / Velocidade);
		else
			TotalFrames = 0;
		//zera frame atual
		FrameAtual = 0;
	}
}

void GameObject::Draw() {
	//fazer para atualizar dimensões
	if ( Sprites.AvancarSprite(XAtual, YAtual, Largura, Altura) )
		//média do "raio" da largura e do "raio" da altura
		Raio = (Largura / 2 + Altura / 2) / 2;
}

unsigned int GameObject::GetMaxX() const {
	return MaxX;
}
unsigned int GameObject::GetMaxY() const {
	return MaxY;
}

void GameObject::GetPosicaoAtual(unsigned int &x, unsigned int &y) const {
	x = XAtual;
	y = YAtual;
}

unsigned int GameObject::GetXAtual() const {
	return XAtual;
}

unsigned int GameObject::GetYAtual() const {
	return YAtual;
}

unsigned int GameObject::GetFrameAtual() const {
	return FrameAtual;
}

unsigned int GameObject::GetTotalFrames() const {
	return TotalFrames;
}

unsigned int GameObject::GetXOrigem() const {
	return XOrigem;
}

unsigned int GameObject::GetYOrigem() const {
	return YOrigem;
}

unsigned int GameObject::GetXDestino() const {
	return XDestino;
}

unsigned int GameObject::GetYDestino() const {
	return YDestino;
}

unsigned int GameObject::GetRaio() const {
	return Raio;
}

unsigned int GameObject::GetLargura() const {
	return Largura;
}

unsigned int GameObject::GetAltura() const {
	return Altura;
}

unsigned int GameObject::GetVelocidade() const {
	return Velocidade;
}

WalkType GameObject::GetTipoMovimento() const {
	return TipoMovimento;
}

SpManip::SpriteManip GameObject::GetSprites() const {
	return Sprites;
}