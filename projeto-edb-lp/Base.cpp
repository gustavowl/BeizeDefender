#include "Base.h"
#include <allegro5/allegro_primitives.h>

Base::Base()
{}

Base::Base(unsigned int x_esq, unsigned int y_sup, unsigned int x_dir, unsigned int y_inf, int REGEM)
{
    vida = 100;
    vidaTotal = vida;
    y_superior = y_sup;
    x_esquerda = x_esq;
    y_inferior = y_inf;
    x_direita = x_dir;
    regem = REGEM;
    
    FrameAtual = 0;
    TotalFrames = 0;
    XOrigem = (x_esq + x_dir) / 2; //calcula ponto central
    YOrigem = (y_sup + y_inf) / 2; //calcula ponto central
    XAtual = XOrigem; //garantir q fica estático
    YAtual = YOrigem; //garantir q fica estático
    XDestino = XOrigem; //garantir q fica estático
    YDestino = YOrigem; //garantir q fica estático
    int xe = x_esq, xd = x_dir; //evita erro de subtração
    Raio = (xd - xe) / 2 + 10; //+ 10 por causa da espessura
    Velocidade = 0;
    TipoMovimento = STATIC;
}


Base::~Base()
{}

void Base::operator=(const Base &base)
{
    vida = base.vida;
    vidaTotal = base.vidaTotal;
    y_superior = base.y_superior;
    x_esquerda = base.x_esquerda;
    y_inferior = base.y_inferior;
    x_direita = base.x_direita;
    regem = base.regem; //0 enquanto não define =D =D
    
    FrameAtual = base.FrameAtual;
    TotalFrames = base.TotalFrames;
    XOrigem = base.XOrigem; //calcula ponto central
    YOrigem = base.YOrigem; //calcula ponto central
    XAtual = base.XOrigem; //garantir q fica estático
    YAtual = base.YOrigem; //garantir q fica estático
    XDestino = base.XOrigem; //garantir q fica estático
    YDestino = base.YOrigem; //garantir q fica estático
    int xe = base.x_esquerda, xd = base.x_direita; //evita erro de subtração
    Raio = base.Raio; //+ 10 por causa da espessura
    Velocidade = base.Velocidade;
    TipoMovimento = STATIC;
}

bool Base::LevarDano(int dano) 
{
  vida -= dano;
  if (vida <= 0)
    return true;
  return false;
}

void Base::Regenerar()
{
    vida += regem;
    if(vida > vidaTotal){
        vida = vidaTotal;
    }
}

int Base::GetVida() 
{
    return vida;
}


void Base::Draw()
{
    if(vida > 0) {
        al_draw_rectangle(x_esquerda, y_superior, x_direita, y_inferior, al_map_rgb(255, 0, 255), 10);    
    }
}