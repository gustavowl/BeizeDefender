#include "Inimigo.h"
#include <math.h>
#include <cstdlib>

Inimigo::Inimigo(int velocidade, int vida) { //gera posição inicial randômicamente (nas bordas)
	*this = Personagem(velocidade, vida, LINEAR);
	Municao = 10;
	CalcularProxDest =  false;
	InterveloTiro = INTERVALOTIROPADRAO;
	ProxTiro = InterveloTiro;
}

 //gera posição inicial randômicamente (nas bordas)
Inimigo::Inimigo(int velocidade, int vida, int municao, int intervelo_tiro) {
	*this = Personagem(velocidade, vida, LINEAR);
	if (municao >= 0)
		Municao = municao;
	else
		Municao = 0;
	if (intervelo_tiro > 0)
		InterveloTiro = intervelo_tiro;
	else
		InterveloTiro = INTERVALOTIROPADRAO;
	ProxTiro = rand() % (InterveloTiro + 1);
	CalcularProxDest =  false;
}

int Inimigo::Dropar()
{
	return Municao;
}

void Inimigo::Distancia(Personagem p, go::GameObject base)
{
	int x_atual = GetXAtual(), y_atual = GetYAtual(); //evitar erros de subtração
	int px_atual = p.GetXAtual(), py_atual = p.GetYAtual(); //evitar erros de subtração
	int px_orig = p.GetXOrigem(), py_orig = p.GetYOrigem(); //evitar erros de subtração
	int base_x = base.GetXAtual(), base_y = base.GetYAtual(); //evitar erros de subtração
	int base_raio = base.GetRaio();

	float dist_jogador = sqrt( pow(x_atual - px_atual, 2) + pow(y_atual - py_atual, 2) );
	float dist_base = sqrt( pow(x_atual - base_x, 2) + pow(y_atual - base_y, 2) );

	//se o jogador estiver mais longe da base ou dentro dela, ataca a base
	if (dist_jogador >= dist_base || ( px_atual > base_x - base_raio && 
	px_atual < base_x + base_raio && py_atual > base_y - base_raio &&
	py_atual < base_y + base_raio) ) { 
		int novo_x, novo_y;
		if (x_atual < (MaxX / 2) - base_raio)
			novo_x = (MaxX/2) - base_raio;
		else if (x_atual > (MaxX/2) + base_raio)
			novo_x = (MaxX/2) + base_raio;
		else
			novo_x = x_atual;

		if (y_atual < (MaxY / 2) - base_raio)
			novo_y = (MaxY/2) - base_raio;
		else if (y_atual > (MaxY/2) + base_raio)
			novo_y = (MaxY/2) + base_raio;
		else
			novo_y = y_atual;

		this->AtualizarDestino( novo_x, novo_y );
		CalcularProxDest = true;
	}
	else {
		if ((px_orig == px_atual && py_orig == py_atual) || /*personagem mudou de rota, recalcula*/
		(x_atual == XDestino && y_atual == YDestino) || /*Inimigo atingiu destino, recalcula*/
		(px_atual == p.GetXDestino() && py_atual == p.GetYDestino()) /*Personagem atingiu destino, recalcula*/
		/*|| p.GetFrameAtual() <= 1*/) //saiu da inércia
			CalcularProxDest = true;

		if (CalcularProxDest) {
			if (px_orig != px_atual && px_atual != p.GetXDestino() &&
			py_atual != py_orig && py_atual != p.GetYDestino()) { //está se movimentando
				//vai para metade do caminho
				/*this->AtualizarDestino( (px_atual + p.GetXDestino()) / 2,
				(py_atual + p.GetYDestino()) / 2);*/
				this->AtualizarDestino( (px_orig + p.GetXDestino()) / 2,
				(py_orig + p.GetYDestino()) / 2);
				CalcularProxDest = false;
			}
			else { //está parado
				//vai para posição atual
				this->AtualizarDestino(px_atual, py_atual);
				CalcularProxDest = false;
			}
		}
			//vai para a metade do caminho
		/*if (px_orig != px_atual && px_atual != p.GetXDestino() &&
			py_atual != py_orig && py_atual != p.GetYDestino()) { //está se movimentando
			//vai para a metade do caminho
			if (CalcularProxDest) {
				this->AtualizarDestino( (px_atual + p.GetXDestino()) / 2,
					(py_atual + p.GetYDestino()) / 2);
			}
			else if (XAtual == XDestino && YAtual == YDestino) {
				//chegou no destino, calcula na próxima iteração
				CalcularProxDest = true;				
			}
		}
		else { //está parado
			if (CalcularProxDest) {
				this->AtualizarDestino(px_atual, py_atual);
				CalcularProxDest = false;
			}
			else if (XAtual == XDestino && YAtual == YDestino)
				//chegou no destino, calcula na próxima iteração
				CalcularProxDest = true;
		}*/
	}

	/*if(dist_jogador > dist_base) {//ataca base
		//atualiza destino se tiver mudado alvo ou seja ao ponto de destino
	//	if ( IsPlayerAlvo ) {
		if (XDestino != MaxX/2 - 100 && YDestino != MaxY/2 - 100) {
			this->AtualizarDestino((MaxX/2) - 100, (MaxY/2) - 100);
		}
		IsPlayerAlvo = false;
	//	}
	}
	else {//ataca jogador
		//atualiza destino se tiver mudado alvo ou seja ao ponto de destino
	//	if ( !IsPlayerAlvo ) {
		if (XDestino != px_orig && YDestino != py_orig &&
			p.GetXDestino() != px_atual && p.GetYDestino() != py_atual) { //está se movimentando e não parado
			this->AtualizarDestino(px_orig, py_orig); //atualiza 1x
			IsPlayerAlvo = false;
		}
		else if (p.GetXDestino() == px_atual && p.GetYDestino() == py_atual && !IsPlayerAlvo) { //parado
			this->AtualizarDestino(px_atual, py_atual);
			IsPlayerAlvo = true;
		}
		/*else if (px_orig == XDestino && py_orig == YDestino) {
			this->AtualizarDestino(0, 0);
		}* /


	//	}
	}*/
	//this->Mover(); //para não mover as balas
}

void Inimigo::Draw()
{
	Personagem::Draw(255, 0, 0);
}

void Inimigo::operator=(const Personagem &persona) {
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

void Inimigo::Atirar(const Personagem &p) 
{
	if ( ProxTiro == 0 && Vida > 0) {
		int x_atual = GetXAtual(), y_atual = GetYAtual(); //evitar erros de subtração
		int px_atual = p.GetXAtual(), py_atual = p.GetYAtual(); //evitar erros de subtração
		int px_orig = p.GetXOrigem(), py_orig = p.GetYOrigem(); //evitar erros de subtração
		int max_x = MaxX, max_y = MaxY; //evitar erros de subtração
		float dist_jogador = sqrt( pow(x_atual - px_atual, 2) + pow(y_atual - py_atual, 2) );
		float dist_base = sqrt( pow(x_atual - max_x / 2, 2) + pow(y_atual - max_y / 2, 2) );
		
		Projetil *novo_projetil;
		if (dist_jogador > dist_base)
			novo_projetil = new Projetil(this->XAtual, this->YAtual, max_x / 2, max_y / 2);
		else
			novo_projetil = new Projetil(this->XAtual, this->YAtual, px_atual, py_atual);
		Projeteis.Insert( 0, novo_projetil ); //insere Projetil no começo da lista
		//zera a contagem dos intervalos
		//+1 evita que ProxTiro = 0, o que faria que o inimigo parasse de atirar
		ProxTiro = ( rand() % InterveloTiro ) + 1;
	}
	ProxTiro--; //subtrai a cada frame
}

void Inimigo::AtualizarDestino(unsigned int DestinoX, unsigned int DestinoY)
{
	GameObject::AtualizarDestino(DestinoX, DestinoY);
}
/*
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

*/