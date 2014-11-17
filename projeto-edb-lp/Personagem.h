#ifndef _PERSONAGEM_H_
#define _PERSONAGEM_H_

#include "GameObject.h"
#include "ListaEncadeada/lista.h"
#include "Projetil.h"

class Personagem : public go::GameObject {
protected:
	Lista<Projetil*> Projeteis; //projéteis que foram atirados e ainda estão dentro da arena
	int Vida;
	void Draw(unsigned int red, unsigned int green, unsigned int blue);
public:
	bool LevarDano(unsigned int dano); //retorna se morreu
	int VerificarColisao(const GameObject obj); //retorna dano causado pelas balas ao obj, e destrói (mas n remove)
	//projéteis que causaram dano. Função exterior tem q tirar vida do obj
	int VerificarColisaoQuadrada(const GameObject obj); //retorna dano causado pelas balas ao obj, e destrói (mas n remove)
	//projéteis que causaram dano. Função exterior tem q tirar vida do obj
	//verifica colisão com a base (projeto final player não vai precisar dessa função, só inimigo)
	virtual void Atirar(unsigned int destino_x, unsigned int destino_y); //atira projétil de tipo 1
	void Mover(); //sobrescreve operação de mover. Move tanto o player quanto suas balas
	Lista<Projetil*> GetProjeteisToDraw(); //retorna uma lista com posição de todos os projéteis
	//para desenhar
	int GetVida() const; //serve para saber se verifica colisão com ele, já que algumas balas provavelmente ainda estarão
	//na arena, mesmo com o personagem já destruído

	Personagem(); //cria personagem "vazio"
	Personagem(unsigned int posicao_x, unsigned int posicao_y, WalkType walk_type);
	Personagem(int velocidade, int vida, WalkType walk_type); //gera posição inicial randômicamente (nas bordas)
	Personagem(unsigned int posicao_x, unsigned int posicao_y, int velocidade, int vida, WalkType walk_type);
	void operator=(const GameObject &game_obj);
	void operator=(const Personagem &persona); //faz cópia profunda
	~Personagem();
};

#endif