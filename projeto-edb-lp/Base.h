#ifndef BASE_H
#define BASE_H


class Base{
    
    public:
        Base();
        ~Base();
        void PerderVida();
        void Regenerar();

    private:
        int vida;
        int regem;
        int altura;
        int largura;
        Movimentacao movimentoBase;
};

#endif
