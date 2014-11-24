#include "Player.h"
#include <allegro5/allegro_image.h>
#include <cmath>

Player::Player(){}

Player::Player(unsigned int posicao_x, unsigned int posicao_y, int max_energia, int energia_atual, 
	int velocidade, int vida, int raio, int regem, Projetil projetil_base, SpriteManip sp_player) {

	SalvarAtaques();
	Projetil *proj;
	ataques.GetFirstElem(proj);
	ProjetilBase = *proj;
	
	if (max_energia > 0 && energia_atual > 0 && vida > 0) {
		*this = Personagem(posicao_x, posicao_y, velocidade, vida, raio, SMOOTH, projetil_base, sp_player);
		MaxEnergia = max_energia;
		if (energia_atual > max_energia)
			EnergiaAtual = max_energia;
		else
			EnergiaAtual = energia_atual;
	}

	VidaTotal = Vida;
	Regem = regem;
	danoFisico = 10;

}

void Player::operator=(const Personagem &persona){
	this->FrameAtual = persona.GetFrameAtual();
	this->TotalFrames = persona.GetTotalFrames();
	this->XOrigem = persona.GetXOrigem();
	this->YOrigem = persona.GetYOrigem();
	this->XAtual = persona.GetXAtual();
	this->YAtual = persona.GetYAtual();
	this->XDestino = persona.GetXDestino();
	this->YDestino = persona.GetYDestino();
	this->Raio = persona.GetRaio();
	this->Velocidade = persona.GetVelocidade();
	this->TipoMovimento = persona.GetTipoMovimento();
	this->Vida = persona.GetVida();
	this->ProjetilBase = persona.GetProjetilBase();
	this->spPlayer = persona.GetSpriteManip();

	Lista<Projetil*> proj_persona = persona.GetProjeteis();
	Projetil *temp; int i = 0;

	while ( this->Projeteis.GetElem(0, temp) ) { //deleta todos os projéteis dinamicamente alocados
		delete temp; //deleta projétil dinamicamente alocado
		this->Projeteis.Remove(0);//remove bala da lista
	}

	while ( proj_persona.GetElem( i, temp ) ) {
		Projetil* to_add = new Projetil();
		*to_add = *temp;
		this->Projeteis.Insert(i, to_add);//insere na última posição para preservar a ordem (apesar de não alterar nada)
		i++;
	}
}

void Player::AdicionarEnergia(unsigned int qtd) { 
	EnergiaAtual += qtd;
	if (EnergiaAtual > MaxEnergia)
		EnergiaAtual = MaxEnergia;
}

void Player::Atirar(unsigned int destino_x, unsigned int destino_y) {
	if ( EnergiaAtual > 0 ) { //verifica se tem munição
		Projetil *novo_projetil = new Projetil(XAtual, YAtual, ProjetilBase.GetVelocidade(),
			destino_x, destino_y, ProjetilBase.GetRaio(), ProjetilBase.GetDano(), ProjetilBase.GetSpriteManip() );
		Projeteis.Insert( 0, novo_projetil ); //insere Projetil no começo da lista
		spPlayer.MudarAlvo(XAtual, YAtual, destino_x, destino_y);
		spPlayer.MudarAcaoAtual(ATIRAR);
		EnergiaAtual--; //decrementa da munição
	}
}

void Player::Draw() {
	spPlayer.AvancarSprite(XAtual, YAtual);
	Personagem::Draw(0, 255, 0);
}

void Player::Regenerar(){
	Vida += Regem;
	if(Vida > VidaTotal){
		Vida = VidaTotal;
	}
}

void Player::ProxProjetil(){
	Projetil *proj;
	ataques.GetNextElem(proj);
	ProjetilBase = *proj;
}


void Player::AntProjetil(){
	Projetil *proj;
	ataques.GetPrevElem(proj);
	ProjetilBase = *proj;
}

void Player::SalvarAtaques(){
	// x, y, velocidade, x, y, raio, dano
	// velocidade 20, raio 2, dano 1
	Projetil *proj_player1 = new Projetil(0, 0, 20, 1, 1, 2, 1, ProjetilBase.GetSpriteManip() );
	// velocidade 10, raio 5, dano 3
	Projetil *proj_player2 = new Projetil(0, 0, 10, 1, 1, 5, 3, ProjetilBase.GetSpriteManip() );
	 // velocidade 5, raio 10, dano 5
	Projetil *proj_player3 = new Projetil(0, 0, 5, 1, 1, 10, 5, ProjetilBase.GetSpriteManip() );
	ataques.Insert(proj_player1);
	ataques.Insert(proj_player2);
	ataques.Insert(proj_player3);
}

int Player::GetEnergiaAtual() {
	return EnergiaAtual;
}
