#include "Player.h"
#include "ListaEncadeada/FilaDupl.h"
#include <math.h>

/*bool Player::LevarDano(unsigned int dano) { //retorna se morreu
	Vida -= dano;
	if (Vida <= 0)
		return true;
	return false;
}

int Player::VerificarColisao(const GameObject obj) { //retorna dano causado pelas balas ao obj, e destrói
//projéteis que causaram dano. Função exterior tem q tirar vida do obj
	Projetil *temp; int i = 0, dano_total = 0;
	//pega informações para calcular colisão de objeto
    while ( Projeteis.GetElem(i, temp) ) {
    	//verifica colisão de uma bala com obj e atualiza dano causado
		dano_total += temp->VerificarColisao(obj);
		i++;
    }
}

int Player::VerificarColisaoQuadrada(const GameObject obj) {
	Projetil *temp; int i = 0, dano_total = 0;
	//pega informações para calcular colisão de objeto
    while ( Projeteis.GetElem(i, temp) ) {
    	//verifica colisão de uma bala com obj e atualiza dano causado
		dano_total += temp->VerificarColisaoQuadrada(obj);
		i++;
    }	
}*/

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

/*void Player::Mover() { //sobrescreve operação de mover. Move tanto o player quanto suas balas
	GameObject::Mover(); //chama mover original
	//chama mover para os projéteis
	Projetil *temp; int i = 0;
	while ( Projeteis.GetElem( i, temp ) ) {
		temp->Mover();
		i++;
	}
}

Lista<Projetil*> Player::GetProjeteisToDraw() { //retorna uma lista com posição de todos os projéteis para desenhar
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
}*/

int Player::GetMunicaoAtual() {
	return MunicaoAtual;
}

void Player::Draw() {
	Personagem::Draw(0, 255, 0);
}

/*int Player::GetVida() {
	return Vida;
}*/

Player::Player(unsigned int posicao_x, unsigned int posicao_y) {
	*this = Personagem(posicao_x, posicao_y, 15, 100, 10, SMOOTH, Projetil(0, 0, 1, 1)); //cria projétil padrão
	MaxMunicao = 50;
	MunicaoAtual = 10;
	VidaTotal = Vida;
}

Player::Player(unsigned int posicao_x, unsigned int posicao_y, int max_municao, int municao_atual, 
	int velocidade, int vida, int raio, Projetil projetil_base, int REGEM) {
	
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

void Player::proxProjetil(){

}

void Player::antProjetil(){

}