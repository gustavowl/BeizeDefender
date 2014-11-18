#include "Base.h"
#include <allegro5/allegro_primitives.h>


Base::Base(unsigned int x_esq, unsigned int y_sup, unsigned int x_dir, unsigned int y_inf)
{
    vida = 10; //aumentaar pra quanto?
    y_superior = y_sup;
    x_esquerda = x_esq;
    y_inferior = y_inf;
    x_direita = x_dir;
    regem = 0; //0 enquanto não define =D =D
    
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

void Base::Draw()
{
   // al_init_primitives_addon();
    al_draw_rectangle(x_esquerda, y_superior, x_direita, y_inferior, al_map_rgb(255, 0, 255), 10);

}

int Base::GetVida() 
{
    return vida;
}

bool Base::LevarDano(int dano) 
{
  vida -= dano;
  if (vida <= 0)
    return true;
  return false;
}
