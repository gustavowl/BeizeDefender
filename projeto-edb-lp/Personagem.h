#ifndef _PERSONAGEM_H_
#define _PERSONAGEM_H_

#include "GameObject.h"
#include "ListaEncadeada/lista.h"
#include "Projetil.h"

class Personagem : public go::GameObject {
protected:
	Projetil ProjetilBase; //projétil que será inserido na lista
	Lista<Projetil*> Projeteis; //projéteis que foram atirados e ainda estão dentro da arena
	int Vida;
	int danoFisico;
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
	//só move caso Personagem atual não esteja sobrepondo nenhum personagem da lista
	void Mover(Lista<Personagem*> &list_pers, Personagem* This); 
	void SetProjetilBase(const Projetil &novo_projetil); //utilizado para mudar tipo do projétil
	Lista<Projetil*> GetProjeteis() const; //retorna lista e projéteis (usado nos operator= de classe filha)
	//substituir por destruido?
	//serve para saber se verifica colisão com ele, já que algumas balas provavelmente ainda estarão
	//na arena, mesmo com o personagem já destruído
	int GetVida() const;
	//retorna se o personagem E os projéteis dele foram destruídos
	bool PersonagemEProjeteisDestruidos();
	Projetil GetProjetilBase() const;
	int GetDanoFisico();

	Personagem(); //cria personagem "vazio"
	//pode ser utilizado para o jogador padrão
	Personagem(unsigned int posicao_x, unsigned int posicao_y, WalkType walk_type);
	//utilizado para o inimigo
	//gera posição inicial randômicamente (nas bordas)
	Personagem(int velocidade, int vida, int raio, WalkType walk_type, Projetil projetil_base);
	//será utilizado para o jogador
	Personagem(unsigned int posicao_x, unsigned int posicao_y, int velocidade, int vida, int raio,
		WalkType walk_type, Projetil projetil_base);
	Personagem(const Personagem &persona); //construtor de cópia
	void operator=(const GameObject &game_obj);
	void operator=(const Personagem &persona); //faz cópia profunda
	~Personagem();
};

#endif