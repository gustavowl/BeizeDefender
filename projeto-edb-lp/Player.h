#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "Personagem.h"
#include "ListaEncadeada/lista.h"
#include "ListaEncadeada/FilaDupl.h"
#include "Projetil.h"

class Player : public Personagem {
private:
	//inimigo pode ter isso tb
	//struct Municao {
	int MaxMunicao;
	int MunicaoAtual;
	int regem;
	int VidaTotal;
	FilaDupl<Projetil*> ataques; 

	//Lista<Projetil*> Projeteis; //projéteis que foram atirados e ainda estão dentro da arena
	//};
	//int Vida;
	//munição do projétil do tipo 1
	//Municao ProjT1;
public:
	//bool LevarDano(unsigned int dano); //retorna se morreu
	//int VerificarColisao(const GameObject obj); //retorna dano causado pelas balas ao obj, e destrói (mas n remove)
	//projéteis que causaram dano. Função exterior tem q tirar vida do obj
	//int VerificarColisaoQuadrada(const GameObject obj); //retorna dano causado pelas balas ao obj, e destrói (mas n remove)
	//projéteis que causaram dano. Função exterior tem q tirar vida do obj
	//verifica colisão com a base (projeto final player não vai precisar dessa função, só inimigo)
	void AdicionarMunicao(unsigned int qtd); //adiciona munição ao Projétil de tipo 1
	void Atirar(unsigned int destino_x, unsigned int destino_y); //atira projétil de tipo 1
	//void Mover(); //sobrescreve operação de mover. Move tanto o player quanto suas balas
	//Lista<Projetil*> GetProjeteisToDraw(); //retorna uma lista com posição de todos os projéteis
	//para desenhar
	int GetMunicaoAtual();
	void Draw();
	//int GetVida();
	void Regenerar();
	void ProxProjetil(); // avança para o proximo ataque
	void AntProjetil(); // volta para o ataque anterior
	void SalvarAtaques(); // cria a lista com os ataques, é chamado no construtor de player


	Player();
	Player(unsigned int posicao_x, unsigned int posicao_y);
	Player(unsigned int posicao_x, unsigned int posicao_y, int max_municao, int municao_atual, 
		int velocidade, int vida, int raio, int REGEM ,Projetil projetil_base);
	void operator=(const Personagem &persona);
};

#endif
