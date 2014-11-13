#ifndef _OBJETOS_H_
#define _OBJETOS_H_

enum IDS{PLAYER, BULLET, ENEMY};

//nosso jogador
struct SpaceShip 
{
	int ID;
	int x;
	int y;
	int vidas;
	int velocidade;
	int boundx;
	int boundy;
	int score;

};

struct Projetil
{

	int ID;
	int x;
	int y;
	bool vida;
	int velocidade;
};

#endif