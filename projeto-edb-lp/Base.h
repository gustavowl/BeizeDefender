#ifndef BASE_H
#define BASE_H

#include "GameObject.h"
#include <iostream>
#include <allegro5/allegro_primitives.h>
#include "ListaEncadeada/lista.h"
#include "Projetil.h"
#include <string>

class Base: public go::GameObject{
    
    public:
        Base(unsigned int alt_inf, unsigned int larg_inf, unsigned int alt_sup, unsigned int larg_sup, std::string id);  
        ~Base();
        bool PerderVida(Lista <GameObject*> projeteis, Projetil * projetil);
        void Regenerar();
        unsigned int GetVida();
        void SetVida();
        void DrawBase();

    private:
        std::string ID;
        unsigned int vida;
        int regem;
        unsigned int altura_inferior;
        unsigned int largura_inferior;
        unsigned int altura_superior;
        unsigned int largura_superior;
        //Movimentacao movimentoBase;
};


Base::Base(unsigned int alt_inf, unsigned int larg_inf, unsigned int alt_sup, unsigned int larg_sup, std::string id)
{
    vida = 10;
    ID = id;
    altura_superior = alt_sup;
    altura_inferior = alt_inf;
    largura_superior = larg_sup;
    largura_inferior = larg_inf;
}


Base::~Base()
{}

void Base::DrawBase()
{
   // al_init_primitives_addon();
    al_draw_rectangle(altura_inferior, largura_inferior, altura_superior, largura_superior, al_map_rgb(255, 0, 255), 10);

}

void Base::SetVida() 
{
    vida -= 1;
}

unsigned int Base::GetVida() 
{
    return vida;
}

bool Base::PerderVida(Lista <GameObject*> projeteis, Projetil * projetil) 
{
    GameObject *temp;

    unsigned int xp, yp;
    unsigned int x1 = 384;
    unsigned int x2 = 240;
    unsigned int y1 = 400;
    unsigned int y2 = 640;

    int i = 0;
    int raio = 2;
  //  int life = GetVida();


    while ( projeteis.GetElem(i, temp) ) {
        temp->GetPosicaoAtual(xp, yp);
        int xptemp = xp;
        int yptemp = yp;

        if ((xptemp >= x2 && xptemp <= x1) || (yptemp >= y1 && yptemp <= y2))
        {
            if(vida <= 0) {
                std::cout << "You Die " << std::endl;
                return true;
                break;
            }
            projetil->Destruir();
            SetVida();
            std::cout << "Vida: " << GetVida() << std::endl;
        }
        i++;
    }
}


#endif

/*

  Base base(180, 160, 480, 320, "player");

                base.DrawBase(180,160,480,320);

                base.PerderVida(projeteis, temp_teste);


*/

