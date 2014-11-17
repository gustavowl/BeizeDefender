#include "Projetil.h"
#include <iostream>
#include <math.h>

Projetil::Projetil(unsigned int PositionX, unsigned int PositionY, unsigned int DestinoX,
unsigned int DestinoY) {
	if (MaxX > 0 && MaxY > 0 && PositionX <= MaxX && PositionY <= MaxY &&
	DestinoX <= MaxX && DestinoY <= MaxY) { //verifica se valor é válido
		//calcula coordenada de destino em que sairá da arena
		CalcularCoordenadasFinais(PositionX, PositionY, DestinoX, DestinoY);
		//chama o construtor da classe pai
		GameObject temp = GameObject(PositionX, PositionY, 30, DestinoX, DestinoY, 2, LINEAR);
		*this =  temp; //copia os valores de pai para filho (tava dando erro ao fazer direto)
		Dano = 2;
		Destruido = false;
	}
}

Projetil::Projetil(unsigned int PositionX, unsigned int PositionY, unsigned int Velocidade, 
unsigned int DestinoX, unsigned int DestinoY, unsigned int Raio, unsigned int Dano) {
	if (MaxX > 0 && MaxY > 0 && PositionX <= MaxX && PositionY <= MaxY &&
	DestinoX <= MaxX && DestinoY <= MaxY && Raio > 0 && Dano > 0) { //verifica se valor é válido
		//calcula coordenada de destino em que sairá da arena
		CalcularCoordenadasFinais(PositionX, PositionY, DestinoX, DestinoY);
		//chama o construtor da classe pai
		GameObject temp = GameObject(PositionX, PositionY, 30, DestinoX, DestinoX, 2, LINEAR);
		*this =  temp; //copia os valores de pai para filho (tava dando erro ao fazer direto)
		this->Dano = Dano; //atualiza dano com valor de entrada
		Destruido = false;
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
	if ( FrameAtual >= TotalFrames )
		Destruir();
}

//destroi se chegar no destino
void Projetil::Destruir() {
	Destruido = true;
}

bool Projetil::GetDesruido() {
	return Destruido;
}

unsigned int Projetil::GetDano() {
	return Dano;
}

int Projetil::VerificarColisao(const GameObject obj) { //retorna dano causado pela bala ao obj, e destrói
//projétil que causou dano. Função exterior tem q tirar vida do obj e remover projétil da memória
	
	int x_atual = XAtual, y_atual = YAtual; //evita erro de subtração
	//coordenadas de obj
	int objx = obj.GetXAtual(), objy = obj.GetYAtual();
	float dist = sqrt( pow( objx - x_atual, 2 ) + pow( objy - y_atual, 2 ) );
	//primeiramente calcula se não está colidindo diretamente
	if ( dist <= Raio + obj.GetRaio() ) {
		Destruir();
		return Dano;
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
			if ( dist < Raio + obj.GetRaio() ) {
				Destruir();
				return Dano;
			}
		}
	}
	return 0;
}

int Projetil::VerificarColisaoQuadrada(const GameObject obj) {//retorna dano causado pelas balas ao obj, e destrói (mas n remove)
//projéteis que causaram dano. Função exterior tem q tirar vida do obj
//verifica colisão com a base, considera raio como metade da largura
	int x_atual = XAtual, y_atual = YAtual; //evita erro de subtração
	//coordenadas de obj
	int objx = obj.GetXAtual(), objy = obj.GetYAtual(), obj_raio = obj.GetRaio();
	//primeiramente calcula se não está colidindo diretamente
	if ( x_atual + Raio > objx - obj_raio && x_atual - Raio < objx + obj_raio &&
		y_atual + Raio > objy - obj_raio && y_atual - Raio < objy + obj_raio ) {
		Destruir();
		return Dano;
	}
	/*else if (FrameAtual > 0) { //cálculo de "leap" ("bug noturno")
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
			float dist = sqrt( pow( inters_x - objx, 2 ) + pow( inters_y - objy, 2 ) );
			//verifica se distância é menor do que a soma dos raios (colisão)
			//se for == tangencia, não colide
			if ( dist < Raio + obj.GetRaio() ) {
				Destruir();
				return Dano;
			}
		}
	}*/
	return 0;
}

void Projetil::CalcularCoordenadasFinais(unsigned int OrigemX, unsigned int OrigemY,
	unsigned int &DestinoX,	unsigned int &DestinoY) {
	//basea-se na equação da reta para saber a direção do movimento
	int dx = DestinoX, ox = OrigemX, dy = DestinoY, oy = OrigemY; //evitar erro na subtração

	float tx = 0, ty = 0; //tx: t a serem aplicados na equação vetorial da reta

	//encontrando os valores de t
	if (dx - ox < 0)  //vai para a esquerda
		tx = (float)( -ox ) / ( dx - ox ); //aplica fórmula tentando achar o x mínimo (0)
	else if (dx - ox > 0) //vai para a direita
		tx = (float)( GetMaxX() - ox ) / (dx - ox); //aplica fórmula tentando achar o x máximo (dimensão horizontal da arena)
	//senão, não se move no eixo x

	if (dy - oy < 0) //vai para cima
		ty = (float)( -oy ) / ( dy - oy ); //aplica fórmula tentando achar o y mínimo (0)
	else if (dy - oy > 0) //vai para baixo
		ty = (float)( GetMaxY() -oy ) / ( dy - oy ); //aplica fórmula tentando achar o y máximo (dimensão vertical da arena)
	//senão, não se move no eixo y

	//verifica qual o menor valor de t, encontrando com qual borda colidirá primeiro
	if (tx != 0 && ty != 0) //compara qual dos 2 eh menor
		if ( fabs(tx) <= fabs(ty) ) { //encontra coordenadas de destino aplicando tx na fórmula
			DestinoX = ox + tx * (dx - ox);
			DestinoY = oy + tx * (dy - oy);
		}
		else { //encontra coordenadas de destino aplicando ty na fórmula
			DestinoX = ox + ty * (dx - ox);
			DestinoY = oy + ty * (dy - oy);
		}
	else if (tx != 0) { //encontra coordenadas de destino aplicando tx na fórmula
		DestinoX = ox + tx * (dx - ox);
		DestinoY = oy + tx * (dy - oy);
	}
	else if (ty != 0) { //encontra coordenadas de destino aplicando ty na fórmula
		DestinoX = ox + ty * (dx - ox);
		DestinoY = oy + ty * (dy - oy);
	}
	//senão, valor inválido
}