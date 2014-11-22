#include "Drop.h"
#include "Player.h"
#include "GameObject.h"
#include <allegro5/allegro_primitives.h>
#include "iostream"
#include "ListaEncadeada/lista.h"
#include <cmath>

Drop::Drop(int energia, int XOrigem, int YOrigem){
	*this = GameObject(XOrigem, YOrigem, 0, 5, STATIC);
	this->energia = energia;
}

Drop::Drop(){
	
}

void Drop::operator=(const GameObject &GameObj) {
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
	TipoMovimento = STATIC;
}

void Drop::Draw(Lista<Drop*> &fila_cafe){
	int i = 0;
	Drop *cafe;
	while ( fila_cafe.GetElem( i, cafe ) ) {
		al_draw_filled_circle(cafe->XOrigem, cafe->YOrigem, 5, al_map_rgb(255, 255, 255));
		i++;
	}
}

void Drop::Pegar(Player &p, Lista<Drop*> &fila_cafe){
	int i = 0;
	Drop *cafe;
	while ( fila_cafe.GetElem( i, cafe ) ) {

		if(cafe->VerificarColisao(p, *cafe)){
			p.AdicionarMunicao(cafe->GetEnergia());
			fila_cafe.Remove(i);
			delete cafe;
			i = 0;
		}
		else
			i++;
	}
}


int Drop::VerificarColisao(Player &p, Drop &cafe){

	int x_atual = cafe.GetXAtual(), y_atual = cafe.GetYAtual(); //evita erro de subtração
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

int Drop::GetEnergia(){
	return energia;
}