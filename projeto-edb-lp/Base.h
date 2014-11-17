#ifndef BASE_H
#define BASE_H

#include "GameObject.h"
//#include <iostream>
#include <allegro5/allegro_primitives.h>
//#include "ListaEncadeada/lista.h"
//#include "Projetil.h"
//#include "Player.h"//acho que são esses
class Base: public go::GameObject{
    
    public:
        Base(unsigned int alt_inf, unsigned int larg_inf, unsigned int alt_sup, unsigned int larg_sup);  
        ~Base();
        bool LevarDano(int dano); //retorna se morreu
        void Regenerar();
        int GetVida();
        void DrawBase();

    private:
        int vida;
        int regem;
        unsigned int altura_inferior;
        unsigned int largura_inferior;
        unsigned int altura_superior;
        unsigned int largura_superior;
};


Base::Base(unsigned int alt_inf, unsigned int larg_inf, unsigned int alt_sup, unsigned int larg_sup)
{
    vida = 10; //aumentaar pra quanto?
    altura_superior = alt_sup;
    altura_inferior = alt_inf;
    largura_superior = larg_sup;
    largura_inferior = larg_inf;
    regem = 0; //0 enquanto não define =D =D
    
    FrameAtual = 0;
    TotalFrames = 0;
    XOrigem = (larg_sup + larg_inf) / 2; //calcula ponto central
    YOrigem = (alt_sup + alt_inf) / 2; //calcula ponto central
    XAtual = XOrigem; //garantir q fica estático
    YAtual = YOrigem; //garantir q fica estático
    XDestino = XOrigem; //garantir q fica estático
    YDestino = YOrigem; //garantir q fica estático
    int ls = larg_sup, li = larg_inf; //evita erro de subtração
    Raio = (ls - li) / 2; //calcular
    Velocidade = 0;
    TipoMovimento = STATIC;
}


Base::~Base()
{}

void Base::DrawBase()
{
   // al_init_primitives_addon();
    al_draw_rectangle(altura_inferior, largura_inferior, altura_superior, largura_superior, al_map_rgb(255, 0, 255), 10);

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


#endif