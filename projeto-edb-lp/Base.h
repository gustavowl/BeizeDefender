#ifndef BASE_H
#define BASE_H

#include "GameObject.h"


/**
* \class Base
*
* \brief Classe derivada de GameObeject que possui os atributos da base do jogo
*
* 
*
*/



class Base: public go::GameObject{
    
    public:

        /**
        * Construtor padrão
        */
        Base();

        /**
        * Construtor que inicializa a base com atributos específicos
        *
        * @param alt_inf altura inferior da base
        * @param larg_inf largura inferior da base
        * @param alt_sup altura superior da base
        * @param larg_sup largura superior da base
        * @param REGEM variável que contém a quantidade de pontos  de vida da base a ser regenerado a cada horda derrotada
        *
        */
        Base(unsigned int alt_inf, unsigned int larg_inf, unsigned int alt_sup, unsigned int larg_sup, int REGEM);  

        /**
        * Destrutor padrão
        */
        ~Base();

        /**
        * Sobrecarga do operador "=" copia os valores de GameObj para Base
        * @param base objeto a ser copiado
        */
        void operator=(const Base &base);

         /**
        * Retorna true caso os pontos de vida da base sejam zerados, ou false caso a base ainda tenha pontos de vida.
        * Além disso, essa função decremeta os pontos de vida da base de acordo com o dano recebido.
        * @param dano pontos de vida a serem decrementados da base
        */
        bool LevarDano(int dano); //retorna se morreu

        /**
        * Regenera a vida da base
        */
        void Regenerar();

        /**
        * Obtém a quantidade de pontos de vida da base
        */
        int GetVida();

        /**
        * Desenha a base
        */
        void Draw();

        

    private:
        int vidaTotal;  /**< Valor que contém o total de pontos de vida da base */ 
        int vida;   /**< Valor que contêm os pontos de vida atual da base */ 
        int regem;  /**< Valor que será regenerado */ 
        unsigned int y_superior; /**< Canto superior esquerdo da tela */
        unsigned int x_esquerda; /**< Canto superior esquerdo da tela */
        unsigned int y_inferior; /**< Canto inferior direito da tela */
        unsigned int x_direita; /**< Canto inferior direito da tela */
};


#endif
