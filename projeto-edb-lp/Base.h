#ifndef BASE_H
#define BASE_H

#include "GameObject.h"

class Base: public go::GameObject{
    
    public:
        Base();
        Base(unsigned int alt_inf, unsigned int larg_inf, unsigned int alt_sup, unsigned int larg_sup, int REGEM);  
        ~Base();
        bool LevarDano(int dano); //retorna se morreu
        void Regenerar();
        int GetVida();
        void Draw();
        void operator=(const Base &base);

    private:
        int vidaTotal;
        int vida;
        int regem;
        unsigned int y_superior; //canto superior esquerdo da tela
        unsigned int x_esquerda; //canto superior esquerdo da tela
        unsigned int y_inferior; //canto inferior direito da tela
        unsigned int x_direita; //canto inferior direito da tela
};


#endif
