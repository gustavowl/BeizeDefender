#include "Inimigo.h"
#include <iostream>
#include <math.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>

Inimigo::Inimigo( int PositionX,  int PositionY)
{
	//if (MaxX > 0 && MaxY > 0 && PositionX <= MaxX && PositionY <= MaxY) { //verifica se valor é válido
		int velocidade = 1;
		int raio = 10;
		//chama o construtor da classe pai
		GameObject temp = GameObject(PositionX, PositionY, velocidade, raio, LINEAR);
		*this =  temp; //copia os valores de pai para filho (tava dando erro ao fazer direto)
		destruido = false;
		ouro = 10; // valor temp
	//}
}

int Inimigo::Dropar(){
	return ouro;
}

void Inimigo::Distancia(GameObject b){
	float distJogador = sqrt( pow(this->GetXAtual() - b.GetXAtual(), 2) + pow(this->GetYAtual() - this->GetYAtual(), 2) );

	float distbase = sqrt( pow(this->GetXAtual() - (640/2), 2) + pow(this->GetYAtual() - (480/2), 2) );

	if(distJogador >= distbase){
		this->AtualizarDestino(b.GetXAtual(), b.GetYAtual());
		std::cout<<"entrei"<<std::endl;
		this->Mover();
		//return a;
	}
	else{
		this->AtualizarDestino((640/2), (480/2));
		std::cout<<"entrei 2"<<std::endl;
		this->Mover();
		//return a;
	}
}

void Inimigo::Mover(){
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

void Inimigo::Draw()
{
  int i = 0;
  unsigned int x, y;
  this->GetPosicaoAtual(x, y);
  //std::cout << x << ' ' << y << std::endl;
  al_draw_filled_circle(x, y, 10, al_map_rgb(100, 100, 100));
}

void Inimigo::operator=(const GameObject &GameObj) {
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

void Inimigo::Atirar(){

}

void Inimigo::AtualizarDestino(unsigned int DestinoX, unsigned int DestinoY){
	GameObject::AtualizarDestino( DestinoX, DestinoY);
}