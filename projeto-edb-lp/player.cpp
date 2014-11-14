#include <iostream>
#include <math.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include "objetos.h"

//#define SMOOTHSTEP(x) ((x) * (x) * (3 - 2 * (x)))


//Globais
const int LARGURA = 640;
const int ALTURA = 480;
const int NUM_BALAS = 5;
//protótipos

void InitShip(SpaceShip &ship);
void DrawShip(SpaceShip &ship);

void InitProjetil(Projetil bala[], int tam);
void DrawProjetil(Projetil bala[], int tam);
void FireProjetil(Projetil bala[], int tam, int vX, int vY);
void UpdateProjetil(Projetil bala[], int tam);

int main(void) 
{
	int i, X, Y, fps = 25;
	unsigned int speed = 10; //pixels por segundos
	float v, qtd_ite = 0;
	bool done = false;

	// variáveis de objetos

	SpaceShip ship;
	Projetil balas[5];
	//variaveis do allegro

	//int pos_x = LARGURA/2; // valor referente ao ponteiro do mouse
	//int pos_y = ALTURA/2;	// idem
	ALLEGRO_TIMER *timer = NULL;


	ALLEGRO_DISPLAY *display = NULL;	// ponteiro para a estrutura ALLEGRO_DISPLAY
	ALLEGRO_EVENT_QUEUE *event_queue = NULL;

	if(!al_init())
		return -1;

	timer = al_create_timer(1.0 / fps);
	if (!timer) {
		return -1;
	}

	display = al_create_display(LARGURA, ALTURA);

	if(!display)
		return -1;

	al_init_primitives_addon();
	al_install_mouse();	

	event_queue = al_create_event_queue();		//ainda não sei o que é

	al_register_event_source(event_queue, al_get_timer_event_source(timer));
	al_register_event_source(event_queue, al_get_display_event_source(display));
	al_register_event_source(event_queue, al_get_mouse_event_source());

	al_start_timer(timer);
	
	InitShip(ship);
	InitProjetil(balas, NUM_BALAS);
	int xx = ship.x;
	int yy = ship.y;
	int xd = ship.x;
	int yd = ship.y;
	int vX = 0;
	int vY = 0;
	int dist =0;

	ALLEGRO_EVENT ev;

	while(!done)
	{
		if ( al_get_next_event(event_queue, &ev) ) {
		//if (al_wait_for_event_until(event_queue, &ev, &timeout)) {
			//al_draw_rectangle(180, 160, 480, 320, al_map_rgb(255, 0, 255), 5);

		    //al_draw_rectangle(180, 160, 480, 320, al_map_rgb(255, 0, 255), 5);


			if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
			{	
				done = true;
			}
			else if(ev.type == ALLEGRO_EVENT_MOUSE_AXES)
			{
				
			}
			else if(ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
			{

				if(ev.mouse.button & 2) {
					xx = ship.x;
					yy = ship.y;
					xd = ev.mouse.x;
					yd = ev.mouse.y;
					dist = sqrt(pow(xx - xd, 2) + pow(yy - yd, 2)); //pitágoras
					qtd_ite = (float)dist / speed;
					i = 0;

				}
				
				else if(ev.mouse.button & 1)
				{
					vX = ship.x;
					vY = ship.y;

					FireProjetil(balas, NUM_BALAS, vX, vY);

					//DrawProjetil(balas, NUM_BALAS);
				}
			}

			else if (ev.type == ALLEGRO_EVENT_TIMER) {
				
				
				if (i <= qtd_ite && qtd_ite > 0)
				{
				 	v = (float)i / qtd_ite;
				 	v = v * v * (3 - 2 * v); //comente essa linha para tirar smoothstep

				 //	std::cout << "V: " << v << "qtd_ite: " << qtd_ite << "i: " << i << std::endl;

					X = round(((xd)*v) + (xx*(1 - v)));
					Y = round(((yd)*v) + (yy*(1 - v)));
					vX = speed*(ev.mouse.x - ship.x)/dist;
					vY = speed*(ev.mouse.y - ship.y)/dist;




				  	ship.x = X;
					ship.y = Y;


					
					//std::cout << "X " << ship.x << "  Y  " << ship.y << "\n";

					i++;
					//InitShip(ship);
				}


				al_draw_rectangle(180, 160, 480, 320, al_map_rgb(255, 0, 255), 10);
				DrawProjetil(balas, NUM_BALAS);
				UpdateProjetil(balas, NUM_BALAS);
				DrawShip(ship);
				al_flip_display();
				al_clear_to_color(al_map_rgb(0,0,0));
			}
		}
	}

	al_destroy_display(display);

	return 0;
}

void InitShip(SpaceShip &ship)
{
	ship.x = 20;
	ship.y = ALTURA/2;
	ship.ID = PLAYER;
	ship.vidas = 3;
	ship.velocidade = 7;
	ship.boundx = 6;
	ship.boundy = 0;
}

void DrawShip(SpaceShip &ship)
{

	//std::cout << "X " << ship.x << "  Y  " << ship.y << "\n";
//	al_draw_filled_rectangle(ship.x,ship.y,ship.x+30,ship.y+30, al_map_rgb(255,255,255));

 	al_draw_filled_rectangle(ship.x, ship.y -9,ship.x +10, ship.y - 7, al_map_rgb(255, 0, 0));
	al_draw_filled_rectangle(ship.x, ship.y +9,ship.x +10, ship.y + 7, al_map_rgb(255, 0, 0));

	al_draw_filled_triangle(ship.x - 12, ship.y -17, ship.x +12, ship.y, ship.x -12, ship.y + 17, al_map_rgb(0,255,0));
	al_draw_filled_rectangle(ship.x - 12, ship.y -2,ship.x +15, ship.y + 2, al_map_rgb(0, 0, 255));

	///al_draw_filled_rectangle(pos_x,pos_y,pos_x+30,pos_y+30, al_map_rgb(255,255,255));


}

void InitProjetil(Projetil bala[], int tam) 
{
	for(int i = 0; i < tam; ++i)
	{
		bala[i].ID = BULLET;
		bala[i].velocidade = 10;
		bala[i].vida = false;
	}
}
void DrawProjetil(Projetil bala[], int tam)
{
	for(int i = 0; i < tam; ++i)
	{
		if(bala[i].vida)
			al_draw_filled_circle(bala[i].x, bala[i].y, 2, al_map_rgb(255, 255, 255));
	}

}
void FireProjetil(Projetil bala[], int tam, int vX, int vY)
{
	for(int i = 0; i < tam; ++i)
	{
		if(!bala[i].vida)
		{
			bala[i].x = vX;
			bala[i].y = vY;
			bala[i].vida = true;
			break;
		}
	}

}
void UpdateProjetil(Projetil bala[], int tam)
{
	for(int i = 0; i < tam; ++i)
	{
		bala[i].x += bala[i].velocidade;
		if(bala[i].x > LARGURA)
			bala[i].vida = false;
	}
}


// T*pontofinal + (1-T)*pontoinicial
