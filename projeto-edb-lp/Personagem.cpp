#include "Personagem.h"
#include <math.h>
#include <allegro5/allegro_primitives.h>

void Personagem::Draw(unsigned int red, unsigned int green, unsigned int blue) {
	//Desenha projéteis independentemente do inimigo ter sido destruído
	Projetil *temp; //ponteiro para pegar valores da lista
	int i = 0;
	while ( Projeteis.GetElem(i, temp) ) {
		//verifica se projétil em questão não foi destruído
		if ( temp->GetDesruido() ) {
			delete temp; //deleta projétil dinamicamente alocado
			Projeteis.Remove(i);//remove bala da lista
			//não incrementa o i pois agora o próximo elemento está na posução atual
		}
		else {
			temp->Draw();
			i++;
		}
	}
	//se não estiver destruído, o desenha
	if (Vida > 0) {
		al_draw_filled_circle(XAtual, YAtual, Raio, al_map_rgb(red % 256, green % 256, blue % 256));
	}
}

bool Personagem::LevarDano(unsigned int dano) { //retorna se morreu
	Vida -= dano; //prevejo erros vindo daqui
	if (Vida <= 0)
		return true;
	return false;
}

int Personagem::VerificarColisao(const GameObject obj) { //retorna dano causado pelas balas ao obj, e destrói
//projéteis que causaram dano. Função exterior tem q tirar vida do obj
	Projetil *temp; int i = 0, dano_total = 0;
	//pega informações para calcular colisão de objeto
    while ( Projeteis.GetElem(i, temp) ) {
    	//verifica colisão de uma bala com obj e atualiza dano causado
		dano_total += temp->VerificarColisao(obj);
		i++;
    }
    return dano_total;
}

int Personagem::VerificarColisaoQuadrada(const GameObject obj) {
	Projetil *temp; int i = 0, dano_total = 0;
	//pega informações para calcular colisão de objeto
    while ( Projeteis.GetElem(i, temp) ) {
    	//verifica colisão de uma bala com obj e atualiza dano causado
		dano_total += temp->VerificarColisaoQuadrada(obj);
		i++;
    }	
}

void Personagem::Atirar(unsigned int destino_x, unsigned int destino_y) { //atira projétil de tipo 1
	Projetil *novo_projetil = new Projetil( XAtual, YAtual, ProjetilBase.GetVelocidade(),
		destino_x, destino_y, ProjetilBase.GetRaio(), ProjetilBase.GetDano() );
	Projeteis.Insert( 0, novo_projetil ); //insere Projetil no começo da lista
}

void Personagem::Mover() { //sobrescreve operação de mover. Move tanto o player quanto suas balas
	if (Vida > 0) { //só move se ainda estiver vivo
		GameObject::Mover(); //chama mover original
	}
	//chama mover para os projéteis
	Projetil *temp; int i = 0;
	while ( Projeteis.GetElem( i, temp ) ) {
		temp->Mover();
		i++;
	}
}

void Personagem::Mover(Lista<Personagem*> &list_pers, Personagem* This) {
	if (Vida > 0) { //só move se ainda estiver vivo

		int prox_x, prox_y, px_atual, py_atual;
		float t = (float)(FrameAtual) / TotalFrames; //variável utilizada para calcular interpolação
			//atualiza posição atual, leva em conta posição de origem e destino

		prox_x = round( XDestino * t + XOrigem * (1 - t) );
		prox_y = round( YDestino * t + YOrigem * (1 - t) );


		//prox_x = XAtual; prox_y = YAtual;
		float dist;
		bool colindo = false;

		int i = 0;
		Personagem *temp;
		while(list_pers.GetElem(i, temp) && !colindo) {
			if (temp != This) {
				px_atual = temp->GetXAtual();
				py_atual = temp->GetYAtual();

				dist = sqrt( pow( prox_x - px_atual, 2) + pow (prox_y - py_atual, 2) );
				if (dist < ( This->GetRaio() + temp->GetRaio() ) ) {
					colindo = true;
				}
			}
			i++;
		}

		if (!colindo) {
			GameObject::Mover(); //chama mover original
		}
	}
	//chama mover para os projéteis
	Projetil *temp; int i = 0;
	while ( Projeteis.GetElem( i, temp ) ) {
		temp->Mover();
		i++;
	}
}

void Personagem::SetProjetilBase(const Projetil &novo_projetil) { //utilizado para mudar tipo do projétil
	ProjetilBase = novo_projetil;
}

Lista<Projetil*> Personagem::GetProjeteis() const { //retorna uma lista com posição de todos os projéteis para desenhar
	Lista<Projetil*> to_return; //lista para retornar
	Projetil *temp; //ponteiro para pegar valores da lista
	int i = 0;
	while ( Projeteis.GetElem(i, temp) ) {
			to_return.Insert( i, temp );//adiciona ao retorno
			i++;
	}
	return to_return;
}

int Personagem::GetVida() const {
	return Vida;
}

bool Personagem::PersonagemEProjeteisDestruidos() {
	return ( Vida <= 0 && Projeteis.Size() == 0 );
}

Projetil Personagem::GetProjetilBase() const {
	return ProjetilBase;
}

int Personagem::GetDanoFisico(){
	return danoFisico;
}

Personagem::Personagem() {
	*this = GameObject(0, 0, 5, 10, LINEAR);
	Vida = 10;
}

Personagem::Personagem(unsigned int posicao_x, unsigned int posicao_y, WalkType walk_type) {
	*this = GameObject(posicao_x, posicao_y, 5, 10, walk_type);
	Vida = 10;
	ProjetilBase = Projetil(0, 0, 1, 1);
}

 //gera posição inicial randômicamente (nas bordas)
Personagem::Personagem(int velocidade, int vida, int raio, WalkType walk_type, Projetil projetil_base) {
	if (vida > 0 && velocidade > 0 && raio > 0) {
		*this = GameObject(velocidade, raio, walk_type);
		Vida = vida;
		ProjetilBase = projetil_base;
	}	
}

Personagem::Personagem(unsigned int posicao_x, unsigned int posicao_y, int velocidade, int vida,
	int raio, WalkType walk_type, Projetil projetil_base) {

	if (vida > 0 && velocidade > 0 && raio > 0) {
		*this = GameObject(posicao_x, posicao_y, velocidade, raio, walk_type);
		Vida = vida;
		ProjetilBase = projetil_base;
	}
}

Personagem::Personagem(const Personagem &persona) { //construtor de cópia
	*this = persona;
}

void Personagem::operator=(const GameObject &game_obj) {
	FrameAtual = game_obj.GetFrameAtual();
	TotalFrames = game_obj.GetTotalFrames();
	XOrigem = game_obj.GetXOrigem();
	YOrigem = game_obj.GetYOrigem();
	XAtual = game_obj.GetXAtual();
	YAtual = game_obj.GetYAtual();
	XDestino = game_obj.GetXDestino();
	YDestino = game_obj.GetYDestino();
	Raio = game_obj.GetRaio();
	Velocidade = game_obj.GetVelocidade();
	TipoMovimento = game_obj.GetTipoMovimento();
}

void Personagem::operator=(const Personagem &persona) {//faz cópia profunda
	this->FrameAtual = persona.FrameAtual;
	this->TotalFrames = persona.TotalFrames;
	this->XOrigem = persona.XOrigem;
	this->YOrigem = persona.YOrigem;
	this->XAtual = persona.XAtual;
	this->YAtual = persona.YAtual;
	this->XDestino = persona.XDestino;
	this->YDestino = persona.YDestino;
	this->Raio = persona.Raio;
	this->Velocidade = persona.Velocidade;
	this->TipoMovimento = persona.GetTipoMovimento();
	this->Vida = persona.Vida;
	this->ProjetilBase = persona.ProjetilBase;

	Projetil *temp; int i = 0;
	while ( Projeteis.GetElem(0, temp) ) { //deleta todos os projéteis dinamicamente alocados
		delete temp; //deleta projétil dinamicamente alocado
		Projeteis.Remove(0);//remove bala da lista
	}

	while ( persona.Projeteis.GetElem( i, temp ) ) {
		Projetil* to_add = new Projetil();
		*to_add = *temp;
		this->Projeteis.Insert(i, to_add);//insere na última posição para preservar a ordem (apesar de não alterar nada)
		i++;
	}
}

Personagem::~Personagem() { //deleta lista de projéteis dinamicamente alocados
	Projetil *temp; //ponteiro para pegar valores da lista
	while ( Projeteis.GetElem(0, temp) ) { //deleta todos os projéteis dinamicamente alocados
		delete temp; //deleta projétil dinamicamente alocado
		Projeteis.Remove(0);//remove bala da lista
	}
}