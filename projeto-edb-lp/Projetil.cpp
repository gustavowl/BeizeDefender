#include "Projetil.h"
#include <iostream>
#include <math.h>

Projetil::Projetil(unsigned int PositionX, unsigned int PositionY, unsigned int DestinoX,
unsigned int DestinoY) {
	if (MaxX > 0 && MaxY > 0 && PositionX <= MaxX && PositionY <= MaxY &&
	DestinoX <= MaxX && DestinoY <= MaxY) {
		GameObject temp = GameObject(PositionX, PositionY, 30, DestinoX, DestinoY, 2, LINEAR);
		*this =  temp;
	}
}

Projetil::Projetil(unsigned int PositionX, unsigned int PositionY, unsigned int Velocidade, 
unsigned int DestinoX, unsigned int DestinoY, unsigned int Raio, unsigned int Dano) {
	if (MaxX > 0 && MaxY > 0 && PositionX <= MaxX && PositionY <= MaxY &&
	DestinoX <= MaxX && DestinoY <= MaxY && Raio > 0 && Dano > 0) {
		*this = GameObject(PositionX, PositionY, 30, DestinoX, DestinoX, 2, LINEAR);
		dano = Dano;
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
	if ( FrameAtual >= TotalFrames ) {
		Destruir();
	}
}

//destroi se chegar no destino
void Projetil::Destruir() {
	
		XAtual = 0;
		YAtual = 0;
		//destroy
}