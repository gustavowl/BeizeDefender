#include "Projetil.h"
#include <iostream>
#include <math.h>

Projetil::Projetil(unsigned int PositionX, unsigned int PositionY, unsigned int DestinoX,
unsigned int DestinoY) {
	if (MaxX > 0 && MaxY > 0 && PositionX <= MaxX && PositionY <= MaxY &&
	DestinoX <= MaxX && DestinoY <= MaxY) { //verifica se valor é válido
		//calcula coordenada de destino em que sairá da arena
		CalcularCoordenadasFinais(PositionX, PositionY, DestinoX, DestinoY);
		//chama o construtor da classe pai
		GameObject temp = GameObject(PositionX, PositionY, 30, DestinoX, DestinoY, 2, LINEAR);
		*this =  temp; //copia os valores de pai para filho (tava dando erro ao fazer direto)
		Dano = 2;
		Destruido = false;
	}
}

Projetil::Projetil(unsigned int PositionX, unsigned int PositionY, unsigned int Velocidade, 
unsigned int DestinoX, unsigned int DestinoY, unsigned int Raio, unsigned int Dano) {
	if (MaxX > 0 && MaxY > 0 && PositionX <= MaxX && PositionY <= MaxY &&
	DestinoX <= MaxX && DestinoY <= MaxY && Raio > 0 && Dano > 0) { //verifica se valor é válido
		//calcula coordenada de destino em que sairá da arena
		CalcularCoordenadasFinais(PositionX, PositionY, DestinoX, DestinoY);
		//chama o construtor da classe pai
		GameObject temp = GameObject(PositionX, PositionY, 30, DestinoX, DestinoX, 2, LINEAR);
		*this =  temp; //copia os valores de pai para filho (tava dando erro ao fazer direto)
		this->Dano = Dano; //atualiza dano com valor de entrada
		Destruido = false;
	}
}

void Projetil::operator=(const GameObject &GameObj) {
	FrameAtual = GameObj.GetFrameAtual();
	TotalFrames = GameObj.GetTotalFrames();
	XOrigem = GameObj.GetXOrigem();
	YOrigem = GameObj.GetYOrigem();
	XAtual = GameObj.GetXAtual();
	YAtual = GameObj.GetYAtual();
	XDestino = GameObj.GetXDestino();
	YDestino = GameObj.GetYDestino();
	Raio = GameObj.GetRaio();
	Velocidade = GameObj.GetVelocidade();
	TipoMovimento = LINEAR;
}

void Projetil::Mover() {
	GameObject::Mover();
	if ( FrameAtual >= TotalFrames )
		Destruir();
}

//destroi se chegar no destino
void Projetil::Destruir() {
	Destruido = true;
}

void Projetil::CalcularCoordenadasFinais(unsigned int OrigemX, unsigned int OrigemY,
	unsigned int &DestinoX,	unsigned int &DestinoY) {
	//basea-se na equação da reta para saber a direção do movimento
	int dx = DestinoX, ox = OrigemX, dy = DestinoY, oy = OrigemY; //evitar erro na subtração

	float tx = 0, ty = 0; //tx: t a serem aplicados na equação vetorial da reta

	//encontrando os valores de t
	if (dx - ox < 0)  //vai para a esquerda
		tx = (float)( -ox ) / ( dx - ox ); //aplica fórmula tentando achar o x mínimo (0)
	else if (dx - ox > 0) //vai para a direita
		tx = (float)( GetMaxX() - ox ) / (dx - ox); //aplica fórmula tentando achar o x máximo (dimensão horizontal da arena)
	//senão, não se move no eixo x

	if (dy - oy < 0) //vai para cima
		ty = (float)( -oy ) / ( dy - oy ); //aplica fórmula tentando achar o y mínimo (0)
	else if (dy - oy > 0) //vai para baixo
		ty = (float)( GetMaxY() -oy ) / ( dy - oy ); //aplica fórmula tentando achar o y máximo (dimensão vertical da arena)
	//senão, não se move no eixo y

	//verifica qual o menor valor de t, encontrando com qual borda colidirá primeiro
	if (tx != 0 && ty != 0) //compara qual dos 2 eh menor
		if ( fabs(tx) <= fabs(ty) ) { //encontra coordenadas de destino aplicando tx na fórmula
			DestinoX = ox + tx * (dx - ox);
			DestinoY = oy + tx * (dy - oy);
		}
		else { //encontra coordenadas de destino aplicando ty na fórmula
			DestinoX = ox + ty * (dx - ox);
			DestinoY = oy + ty * (dy - oy);
		}
	else if (tx != 0) { //encontra coordenadas de destino aplicando tx na fórmula
		DestinoX = ox + tx * (dx - ox);
		DestinoY = oy + tx * (dy - oy);
	}
	else if (ty != 0) { //encontra coordenadas de destino aplicando ty na fórmula
		DestinoX = ox + ty * (dx - ox);
		DestinoY = oy + ty * (dy - oy);
	}
	//senão, valor inválido
}