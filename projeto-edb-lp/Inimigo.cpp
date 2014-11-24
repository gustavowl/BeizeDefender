#include "Inimigo.h"
#include <cmath>
#include <cstdlib>

Inimigo::Inimigo(int velocidade, int vida) { //gera posição inicial randômicamente (nas bordas)
	SpManip::SpriteManip vazio;
	*this = Personagem(velocidade, vida, 10, LINEAR, Projetil(0, 0, 1, 1), vazio); //cria projétil padrão 
	Drop = 15;
	danoFisico = 4;
	CalcularProxDest =  false;
	IntervaloTiro = INTERVALOTIROPADRAO;
	ProxTiro = IntervaloTiro;
}

 //gera posição inicial randômicamente (nas bordas)
Inimigo::Inimigo(int velocidade, int vida, int raio, int intervaloTiro,
	int primeiro_tiro, Projetil projetil_base, int danoFisico, SpManip::SpriteManip sp_inim) 
{
	Drop = 15;
	this->danoFisico = danoFisico;
	*this = Personagem(velocidade, vida, raio, LINEAR, projetil_base, sp_inim);
	
	if (intervaloTiro > 0)
		IntervaloTiro = intervaloTiro;
	else
		IntervaloTiro = INTERVALOTIROPADRAO;
	if (primeiro_tiro >= 0)
		ProxTiro = primeiro_tiro;
	else
		ProxTiro = rand() % (IntervaloTiro + 1);
	CalcularProxDest =  false;
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

	//se o jogador estiver mais longe da base ou player dentro dela, ataca a base
	if (dist_jogador >= dist_base || ( px_atual > base_x - base_raio && 
	px_atual < base_x + base_raio && py_atual > base_y - base_raio &&
	py_atual < base_y + base_raio) ) { 
		int novo_x, novo_y;
		if (x_atual < base_x - base_raio)
			novo_x = base_x - base_raio * 1.25;
		else if (x_atual > base_x + base_raio)
			novo_x = base_x + base_raio * 1.25;
		else
			novo_x = x_atual;

		if (y_atual < base_y - base_raio)
			novo_y = base_y - base_raio * 1.25;
		else if (y_atual > base_y + base_raio)
			novo_y = base_y + base_raio * 1.25;
		else
			novo_y = y_atual;

		this->AtualizarDestino( novo_x, novo_y );
		CalcularProxDest = true;
	}
	else {
		if ((px_orig == px_atual && py_orig == py_atual) || /*personagem mudou de rota, recalcula*/
		(x_atual == XDestino && y_atual == YDestino) || /*Inimigo atingiu destino, recalcula*/
		(px_atual == p.GetXDestino() && py_atual == p.GetYDestino()) ) /*Personagem atingiu destino, recalcula*/
			CalcularProxDest = true;

		if (CalcularProxDest) {
			if (px_orig != px_atual && px_atual != p.GetXDestino() &&
			py_atual != py_orig && py_atual != p.GetYDestino()) { //está se movimentando
				//vai para metade do caminho

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
	}
}

void Inimigo::Draw()
{
	//próxima iteração ele vai voltar a andar
	if ( Sprites.GetTempoProxSprite() == 0 && atirando )
		atirando = false;
	//Sprites.AvancarSprite(XAtual, YAtual);
	Personagem::Draw(255, 0, 0);
	GameObject::Draw();
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

void Inimigo::AtualizarDestino(unsigned int DestinoX, unsigned int DestinoY)
{
	GameObject::AtualizarDestino(DestinoX, DestinoY);
}

void Inimigo::Atirar(const Personagem &p, const go::GameObject &base) 
{
	if ( ProxTiro == 0 && Vida > 0) {
		int x_atual = GetXAtual(), y_atual = GetYAtual(); //evitar erros de subtração
		int px_atual = p.GetXAtual(), py_atual = p.GetYAtual(); //evitar erros de subtração
		int px_orig = p.GetXOrigem(), py_orig = p.GetYOrigem(); //evitar erros de subtração
		int base_x = base.GetXAtual(), base_y = base.GetYAtual(); //evitar erros de subtração
		float dist_jogador = sqrt( pow(x_atual - px_atual, 2) + pow(y_atual - py_atual, 2) );
		float dist_base = sqrt( pow(x_atual - base_x, 2) + pow(y_atual - base_y, 2) );
		

		Projetil *novo_projetil;
		if (dist_jogador > dist_base) {
			novo_projetil = new Projetil(XAtual, YAtual, ProjetilBase.GetVelocidade(), base_x, base_y,
				ProjetilBase.GetRaio(), ProjetilBase.GetDano(), ProjetilBase.GetSprites() );
			Sprites.MudarAlvo(XAtual, YAtual, base_x, base_y);
		}
		else {
			novo_projetil = new Projetil(XAtual, YAtual, ProjetilBase.GetVelocidade(), px_atual, py_atual,
				ProjetilBase.GetRaio(), ProjetilBase.GetDano(), ProjetilBase.GetSprites() );
			Sprites.MudarAlvo(XAtual, YAtual, px_atual, py_atual);
		}

		atirando = true;
		Sprites.MudarAcaoAtual(ATIRAR);
		Sprites.SetTempoProxSprite(INTERVALO_ENTRE_SPRITES * 3);

		Projeteis.Insert( 0, novo_projetil ); //insere Projetil no começo da lista
		//zera a contagem dos intervalos
		//+1 evita que ProxTiro = 0, o que faria que o inimigo parasse de atirar
		ProxTiro = ( rand() % IntervaloTiro ) + 1;
	}
	ProxTiro--; //subtrai a cada frame
}



void Inimigo::Mover() 
{
	Personagem::Mover(); //chama mover original
}

void Inimigo::Mover(Lista<Personagem*> &list_pers, Personagem* This)
{
	Personagem::Mover(list_pers, This);
}

void Inimigo::Mover(Player &p, Inimigo &ini)
{
	if (Vida > 0) { //só move se ainda estiver vivo
		if(VerificarColisaoInimigo(p, ini)){
			std::cout<<"colidiu"<<std::endl;
		}
		GameObject::Mover(); //chama mover original
	}
}


int Inimigo::VerificarColisaoInimigo(Player &p, Inimigo &ini)
{

	int x_atual = ini.GetXAtual(), y_atual = ini.GetYAtual(); //evita erro de subtração
	//coordenadas de obj
	int objx = p.GetXAtual(), objy = p.GetYAtual();
	float dist = sqrt( pow( objx - x_atual, 2 ) + pow( objy - y_atual, 2 ) );
	//primeiramente calcula se não está colidindo diretamente
	if ( dist <= Raio + p.GetRaio() ) {
		
		return 1;
	}
	else if (FrameAtual > 0) { //cálculo de "leap" ("bug noturno")
		//calcula t da equação vetorial das retas para a variação das coordenadas
		float ta = (float)(FrameAtual - 1) / TotalFrames;
		float tb = (float) FrameAtual / TotalFrames;
		//acha o t de objeto na reta tal que X do objeto pertença à reta
		int x_origem = XOrigem, x_destino = XDestino; //evitar erro na subtração
		int y_origem = YOrigem, y_destino = YDestino; //evitar erro na subtração
		//calcula coeficiente angular da reta do projétil
		float coef_ang_proj = (float)(y_destino - y_origem) / (x_destino - x_origem);
		//calcula coeficiente linear da reta do projétil
		float coef_lin_proj = y_destino - coef_ang_proj * x_destino;
		//calcula coeficiente angular da reta perpendicular à do projétil que passa pela origem do círculo
		float coef_ang_perp = - (1 / coef_ang_proj);
		//calcula coeficiente linear da reta perpendicular à do projétil que passa pela origem do círculo
		float coef_lin_perp = objy - coef_ang_perp * objx;
		//acha ponto x da intersecção entre as duas retas
		float inters_x = (coef_lin_perp - coef_lin_proj) / (coef_ang_proj - coef_ang_perp);
		//acha o t da intersecção na equação vetorial da reta do projétil
		float ti = (inters_x - x_origem) / (x_destino - x_origem);
		//verifica se o t da intersecção está entre o segmento de reta formato por ta e tb
		if ( ti >= ta && ti <= tb ) {
			//acha ponto y da intersecção entre as duas retas
			float inters_y = coef_ang_proj * inters_x + coef_lin_proj;
			//calcula distância entre intersecção e origem do objeto
			dist = sqrt( pow( inters_x - objx, 2 ) + pow( inters_y - objy, 2 ) );
			//verifica se distância é menor do que a soma dos raios (colisão)
			//se for == tangencia, não colide
			if ( dist < Raio + p.GetRaio() ) {
				return 1;
			}
		}
	}
	return 0;
}


int Inimigo::Dropar()
{
	return Drop;
}