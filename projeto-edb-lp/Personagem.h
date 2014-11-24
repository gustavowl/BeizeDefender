#ifndef _PERSONAGEM_H_
#define _PERSONAGEM_H_

#include "GameObject.h"
#include "ListaEncadeada/lista.h"
#include "Projetil.h"
#include "SpriteManip.h"

using namespace SpManip;

/**
* \class Personagem
*
* \brief Classe que herda de GameObject. Contém atributos e métodos comuns entre inimigo e player
*/
class Personagem : public go::GameObject {
protected:
	Projetil ProjetilBase; /**< Armazena projétil que será inserido na lista*/
	Lista<Projetil*> Projeteis; /**< Lista simplesmente encadeada que contém os projéteis no campo de batalha (arena)*/
	int Vida; /**< Armazena a vida atual do personagem. Vida <= 0: personagem morreu*/
	int danoFisico; /**< Dano causado a outros personagens ao se colidir com eles*/
	bool atirando; /**< Utilizado para desenhar sprites, e mudar ação.*/
	/**
	* Desenha Personagem na tela. Leva em conta atributos de GO
	* @param red quantidade de vermelho (RGB) da cor do personagem
	* @param green quantidade de verde (RGB) da cor do personagem
	* @param blue quantidade de azul (RGB) da cor do personagem
	*/
	void Draw(unsigned int red, unsigned int green, unsigned int blue);
public:
	/**
	* Faz com que o personagem leve o dano especificado
	* \return Retorna se personagem morreu ou não (Vida atingiu 0)
	*/
	bool LevarDano(unsigned int dano);
	/**
	* Verifica colisão das balas do Personagem atual com um objeto circular enviado por parâmetro. Destrói (mas não
	* remove da lista Projeteis) aqueles que causaram dano. É necessário que uma função exterior tire vida do objeto.
	* \return retorna o dano causado ao objeto
	* @param obj recebe objeto com o qual serão verificadas as colisões dos projéteis do personagem
	*/
	int VerificarColisao(const GameObject obj);
	/**
	* Verifica colisão das balas do Personagem atual com um objeto quadrado enviado por parâmetro. Destrói (mas não
	* remove da lista Projeteis) aqueles que causaram dano. É necessário que uma função exterior tire vida do objeto.
	* \return retorna o dano causado ao objeto
	* @param obj recebe objeto com o qual serão verificadas as colisões dos projéteis do personagem
	*/
	int VerificarColisaoRetangular(const GameObject obj);
	/**
	* Atira projétil base
	* @param destino_x posição X de destino do projétil
	* @param destino_y posição Y de destino do projétil
	*/
	virtual void Atirar(unsigned int destino_x, unsigned int destino_y);
	/**
	* Sobrescreve função Mover() de GameObject. Move tanto o personagem quanto suas balas.
	* só movimenta o personagem caso ele não tenha morrido.
	*/	
	void Mover();
	/**
	* Sobrecarrega função Mover(). Move tanto o player quanto suas balas.
	* Só movimenta o personagem caso ele não tenha morrido e caso futura posição do personagem atual não
	* sobreponha nenhum porsonagem da lista.
	* @param &list_pers Lista simplesmente encadeada dos personagens a se verificar colisão futura
	* @param *This ponteiro do personagem atual presente em &list_pers
	*/
	void Mover(Lista<Personagem*> &list_pers, Personagem* This); 
	/**
	* Utilizado para mudar o Projétil base
	* @param &novo_projetil Projétil enviado por referência. Será o novo projétil base
	*/
	void SetProjetilBase(const Projetil &novo_projetil);
	/**
	* Usado na sobrecarga de operadores = da classe filha
	* \return Retorna lista de projéteis que estão na arena
	*/
	Lista<Projetil*> GetProjeteis() const;
	/**
	* \return retorna vida atual do personagem
	*/
	int GetVida() const;
	/**
	* \return retorna se o personagem E os projéteis dele foram destruídos. Caso verdadeiro, 
	* pode remover o Personagem do jogo, caso falso, tem que esperar as balas do personagem
	* serem destruídas (saírem do jogo).
	*/
	bool PersonagemEProjeteisDestruidos();
	/**
	* \return Retorna o projétil base
	*/
	Projetil GetProjetilBase() const;
	/**
	* \return Retorna o dano físico
	*/
	int GetDanoFisico();

	/**
	* Construtor padrão, cria personagem "vazio"
	*/

	Personagem();
	/**
	* Construtor
	* Pode ser utilizado para construir o jogador padrão. Chama construtor de GameObject que recebe
	* os mesmos parâmetros, com excessão do raio e da velocidade.
	* @param posicao_x coordenada X de origem do personagem
	* @param posicao_y coordenada X de origem do personagem
	* @param TipoMov tipo de movimento que será feito pelo personagem
	*/
	Personagem(unsigned int posicao_x, unsigned int posicao_y, WalkType walk_type);
	/**
	* Construtor utilizado para o inimigo
	* Chama construtor equivalente de GameObject
	* Gera posição inicial aleatoriamente nas bordas da arena
	* @param velocidade velocidade do personagem
	* @param vida vida inicial do personagem
	* @param raio raio utilizado para detecção de colisão
	* @param walk_type tipo de movimento que será feito pelo personagem
	* @param projetil_base Projétil que será atirado pelo personagem
	*/
	Personagem(int velocidade, int vida, int raio, WalkType walk_type, Projetil projetil_base,
		SpriteManip sp_inim);
	/**
	* Construtor utilizado pelo Player
	* Chama construtor equivalente de GameObject
	* @param posicao_x coordenada X de origem do personagem
	* @param posicao_y coordenada X de origem do personagem
	* @param velocidade velocidade do personagem
	* @param vida vida inicial do personagem
	* @param raio raio utilizado para detecção de colisão
	* @param walk_type tipo de movimento que será feito pelo personagem
	* @param projetil_base Projétil que será atirado pelo personagem
	*/
	Personagem(unsigned int posicao_x, unsigned int posicao_y, int velocidade, int vida, int raio,
		WalkType walk_type, Projetil projetil_base, SpriteManip sp_player);
	/**
	* Construtor de cópia
	* Realiza cópia profunda do personagem enviado por referência
	* @param &persona Personagem a ser copiado (enviado por referência)
	*/
	Personagem(const Personagem &persona);
	/**
	* Sobrecarga de operador =
	* Realiza cópia profunda do GameObject enviado por referência
	* @param &game_obj GameObject a ser copiado (enviado por referência)
	*/
	void operator=(const GameObject &game_obj);
	/**
	* Sobrecarga de operador =
	* Realiza cópia profunda do Personagem enviado por referência
	* @param &persona Personagem a ser copiado (enviado por referência)
	*/
	void operator=(const Personagem &persona);

	/**
	* Destrutor
	* Desaloca valores e nós de Lista<Projetil*> Projeteis que foram armazenados dinamicamente
	*/
	~Personagem();
};

#endif