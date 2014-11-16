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
		municao = 10; // valor temp
	//}
}

int Inimigo::Dropar()
{
	return municao;
}

void Inimigo::Distancia(Player b)
{
	float distJogador = sqrt( pow(this->GetXAtual() - b.GetXAtual(), 2) + pow(this->GetYAtual() - b.GetYAtual(), 2) );
	float distbase = sqrt( pow(this->GetXAtual() - (MaxX/2), 2) + pow(this->GetYAtual() - (MaxY/2), 2) );

	if(distJogador >= distbase){
		this->AtualizarDestino(b.GetXAtual(), b.GetYAtual());
	} else{
		this->AtualizarDestino((MaxX/2), (MaxY/2));
	}

	this->Mover();
}

void Inimigo::Mover()
{
	GameObject::Mover(); //chama mover original

	Projetil *temp; int i = 0;
	while ( Projeteis.GetElem( i, temp ) ) {
		temp->Mover();
		i++;
	}

}

void Inimigo::Draw()
{
  int i = 0;
  unsigned int x, y;
  this->GetPosicaoAtual(x, y);
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

void Inimigo::Atirar() 
{
	Projetil *novo_projetil = new Projetil(this->XAtual, this->YAtual, this->XDestino, this->YDestino);
	Projeteis.Insert( 0, novo_projetil ); //insere Projetil no começo da lista
}

void Inimigo::AtualizarDestino(unsigned int DestinoX, unsigned int DestinoY)
{
	GameObject::AtualizarDestino(DestinoX, DestinoY);
}

Lista<Projetil*> Inimigo::GetProjeteisToDraw() 
{ 	//retorna uma lista com posição de todos os projéteis para desenhar
	Lista<Projetil*> to_return; //lista para retornar
	Projetil *temp; //ponteiro para pegar valores da lista
	int i = 0;
	while ( Projeteis.GetElem(i, temp) ) {
		//verifica se projétil em questão não foi destruído
		if ( temp->GetDesruido() )
			Projeteis.Remove(i);//remove bala da lista
			//não incrementa o i pois agora o próximo elemento está na posução atual
		else {
			to_return.Insert( 0, temp );//adiciona ao retorno
			i++;
		}
	}
	return to_return;
}