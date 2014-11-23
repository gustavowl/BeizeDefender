#include "Player.h"
#include "ListaEncadeada/FilaDupl.h"
#include <math.h>

Player::Player(){}

Player::Player(unsigned int posicao_x, unsigned int posicao_y) {
	*this = Personagem(posicao_x, posicao_y, 15, 100, 10, SMOOTH, Projetil(0, 0, 1, 1)); //cria projétil padrão
	MaxMunicao = 50;
	MunicaoAtual = 10;
	danoFisico = 10;
	VidaTotal = Vida;
}

Player::Player(unsigned int posicao_x, unsigned int posicao_y, int max_municao, int municao_atual, 
	int velocidade, int vida, int raio, int REGEM, Projetil projetil_base) {
	SalvarAtaques();
	Projetil *proj;
	ataques.GetFirstElem(proj);
	ProjetilBase = *proj; // projetil tipo 1
	
	if (max_municao > 0 && municao_atual > 0 && vida > 0) {
		*this = Personagem(posicao_x, posicao_y, velocidade, vida, raio, SMOOTH, projetil_base);
		MaxMunicao = max_municao;
		if (municao_atual > max_municao)
			MunicaoAtual = max_municao;
		else
			MunicaoAtual = municao_atual;
	}
	VidaTotal = Vida;
	regem = REGEM;
	danoFisico = 10;

}

void Player::AdicionarMunicao(unsigned int qtd) { //adiciona munição ao Projétil de tipo 1
	MunicaoAtual += qtd;
	if (MunicaoAtual > MaxMunicao)
		MunicaoAtual = MaxMunicao;
}

void Player::Atirar(unsigned int destino_x, unsigned int destino_y) { //atira projétil de tipo 1
	if ( MunicaoAtual > 0 ) { //verifica se tem munição
		Projetil *novo_projetil = new Projetil(XAtual, YAtual, ProjetilBase.GetVelocidade(),
			destino_x, destino_y, ProjetilBase.GetRaio(), ProjetilBase.GetDano() );
		/*
		(unsigned int PositionX, unsigned int PositionY, unsigned int Velocidade, unsigned int DestinoX,
			unsigned int DestinoY, unsigned int Raio, unsigned int Dano)
		*/
		Projeteis.Insert( 0, novo_projetil ); //insere Projetil no começo da lista
		MunicaoAtual--; //decrementa da munição
	}
}


int Player::GetMunicaoAtual() {
	return MunicaoAtual;
}

void Player::Draw() {
	Personagem::Draw(0, 255, 0);
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

void Player::Regenerar(){
	Vida += regem;
	if(Vida > VidaTotal){
		Vida = VidaTotal;
	}
}


// avança para o proximo ataque
void Player::ProxProjetil(){
	Projetil *proj;
	ataques.GetNextElem(proj);
	ProjetilBase = *proj;
}

// volta para o ataque anterior
void Player::AntProjetil(){
	Projetil *proj;
	ataques.GetPrevElem(proj);
	ProjetilBase = *proj;
}

// cria a lista com os ataques, é chamado no construtor de player
void Player::SalvarAtaques(){
	// x, y, velocidade, x, y, raio, dano
	Projetil *proj_player1 = new Projetil(0, 0, 20, 1, 1, 2, 5, 1); // velocidade 20, raio 2, dano 1
	Projetil *proj_player2 = new Projetil(0, 0, 10, 1, 1, 5, 5, 3); // velocidade 10, raio 15, dano 3
	Projetil *proj_player3 = new Projetil(0, 0, 5, 1, 1, 10, 5, 5); // velocidade 5, raio 20, dano 5
	ataques.Insert(proj_player1);
	ataques.Insert(proj_player2);
	ataques.Insert(proj_player3);
}
