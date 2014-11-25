#include "Player.h"
#include <allegro5/allegro_image.h>
#include <cmath>

Player::Player(){}

Player::Player(unsigned int posicao_x, unsigned int posicao_y, int max_energia, int energia_atual, 
	int velocidade, int vida, int raio, int regem, Projetil projetil_base, SpriteManip sp_player,
	SpriteManip sp_proj1, SpriteManip sp_proj2, SpriteManip sp_proj3) {

	SalvarAtaques(sp_proj1, sp_proj2, sp_proj3);
	Projetil *proj;
	ataques.GetFirstElem(proj);
	ProjetilBase = *proj;
	
	if (max_energia > 0 && energia_atual > 0 && vida > 0) {
		*this = Personagem(posicao_x, posicao_y, velocidade, vida, raio, LINEAR, ProjetilBase, sp_player);
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
	this->Sprites = persona.GetSprites();

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
			destino_x, destino_y, ProjetilBase.GetRaio(), ProjetilBase.GetDano(), ProjetilBase.GetSprites() );
		Projeteis.Insert( 0, novo_projetil ); //insere Projetil no começo da lista
		Sprites.MudarAlvo(XAtual, YAtual, destino_x, destino_y);
		Sprites.MudarAcaoAtual(ATIRAR);
		Sprites.SetTempoProxSprite(INTERVALO_ENTRE_SPRITES * 3);
		atirando = true;
		EnergiaAtual--; //decrementa da munição
	}
}

void Player::Draw() {
	//próxima iteração ele vai voltar a andar
	if ( Sprites.GetTempoProxSprite() == 0 && atirando )
		atirando = false;
	Personagem::Draw();
	//GameObject::Draw();
	//Sprites.AvancarSprite(XAtual, YAtual);
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

void Player::SalvarAtaques(SpriteManip sp_proj1, SpriteManip sp_proj2, SpriteManip sp_proj3){
	// x, y, velocidade, x, y, raio, dano
	// velocidade 20, raio 2, dano 1
	Projetil *proj_player1 = new Projetil(0, 0, 20, 1, 1, 2, 1, sp_proj1 );
	// velocidade 10, raio 5, dano 3
	Projetil *proj_player2 = new Projetil(0, 0, 10, 1, 1, 5, 3, sp_proj2 );
	 // velocidade 5, raio 10, dano 5
	Projetil *proj_player3 = new Projetil(0, 0, 5, 1, 1, 10, 5, sp_proj3 );
	ataques.Insert(proj_player1);
	ataques.Insert(proj_player2);
	ataques.Insert(proj_player3);
}

int Player::GetEnergiaAtual() {
	return EnergiaAtual;
}

Player::~Player() {
	Projetil *temp;
	while ( ataques.Remove(temp) ) {
		delete temp;
	}
}