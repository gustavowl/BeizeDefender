#include <iostream>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <math.h>
#include "GameObject.h"
#include "ListaEncadeada/lista.h"
using namespace teste;

void DrawProjetil(Lista<GameObject*> projeteis);
void DrawPlayer(GameObject player);

int main(void) 
{
  int i, X, Y, fps = 25;
  unsigned int speed = 10; //pixels por segundos
  float v, qtd_ite = 0;
	bool done = false;
  
  GameObject arena(480, 640); 
  GameObject player(240, 320, speed, 10, LINEAR);
  Lista<GameObject*> projeteis;
  
  //em GameObject tem um enum: enum WalkType { STATIC, LINEAR, SMOOTH }; 

  
  //Lista<GameObject*> NomeDaLista //inicializa lista encadeada
  //NomedaLista.Size(); //retorna o tamanho
  //NomeDaLista.GetElem(1, go); (retorna elemento da posição 1 para go)
  //        método retorna bool /\ (se go tem elemento válido)
  //NomeDaLista.Search(go); //procura pelo objeto "go" na lista e retorna posição
  //NomeDaLista.Insert(2, go); //insere objeto go na posição 2 da lista, retorna
                              // se inseriu ou n
  //NomeDaLista.Remove(3); remove objeto da posição 3, retorna se removeu
  //NomeDaLista.Remove(4, go); objeto da posição 4, salva em go e retorna se removeu
  //NomeDaLista.Print(); //imprime tds os objetos da lista, separando com espaço
  //NomeDaLista.Print('\n'); //imprime tds os objetos da lista, separando com "enter"

  
	//variaveis do allegro

	ALLEGRO_TIMER *timer = NULL;
	ALLEGRO_DISPLAY *display = NULL;
	ALLEGRO_EVENT_QUEUE *event_queue = NULL;

	if(!al_init())
		return -1;

	timer = al_create_timer(1.0 / fps);
	if (!timer) {
		return -1;
	}

  //Pega dimensões da arena
	display = al_create_display((int)arena.GetMaxX(), (int)arena.GetMaxY());

	if(!display)
		return -1;

	al_init_primitives_addon();
	al_install_mouse();	

	event_queue = al_create_event_queue();

	al_register_event_source(event_queue, al_get_timer_event_source(timer));
	al_register_event_source(event_queue, al_get_display_event_source(display));
	al_register_event_source(event_queue, al_get_mouse_event_source());

	al_start_timer(timer);
	


	ALLEGRO_EVENT ev;

	while(!done)
	{
		if ( al_get_next_event(event_queue, &ev) ) {
		  //if (al_wait_for_event_until(event_queue, &ev, &timeout)) {

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
          player.AtualizarDestino(ev.mouse.x, ev.mouse.y);
				}
				
				else if(ev.mouse.button & 1)
				{
          //TAREFA PENDENTE: realizar cálculo para ir até o fim da tela
          //player->atirar();
          
          GameObject *projetil = new GameObject(player.GetXAtual(), player.GetYAtual(),
           	15, ev.mouse.x, ev.mouse.y, 2, LINEAR);
          
          projeteis.Insert(projeteis.Size(), projetil);
          
				//	FireProjetil(projeteis, projeteis.Size());

				}
			}

			else if (ev.type == ALLEGRO_EVENT_TIMER) { 
				player.Mover();
        //move projéteis
        int i = 0;
        GameObject *temp;
        while ( projeteis.GetElem(i, temp) ) {
          temp->Mover();
          i++;
        }
				al_draw_rectangle(180, 160, 480, 320, al_map_rgb(255, 0, 255), 10);
        //implementar \/
				DrawProjetil(projeteis);
        
				//UpdateProjetil(projeteis, );
				DrawPlayer(player);
				al_flip_display();
				al_clear_to_color(al_map_rgb(0,0,0));
			}
		}
	}

	al_destroy_display(display);

	return 0;
}


void DrawPlayer(GameObject player)
{
  int i = 0;
  unsigned int x, y;
  player.GetPosicaoAtual(x, y);
  al_draw_filled_circle(x, y, 10, al_map_rgb(255, 0, 255));
}

void DrawProjetil(Lista<GameObject*> projeteis)
{
  int i = 0;
  unsigned int x, y;
  GameObject *temp;
  while ( projeteis.GetElem(i, temp) ) {
    temp->GetPosicaoAtual(x, y);
    al_draw_filled_circle(x, y, 2, al_map_rgb(255, 255, 255));
    i++;
  }

}

/*
//posição da bala é atualizada
void FireProjetil(Lista <GameObject*> projeteis)
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

// verifica se essa posição ultrapasso os limites
void UpdateProjetil(Lista <GameObject*> projeteis, int tam)
{
	for(int i = 0; i < tam; ++i)
	{
		bala[i].x += bala[i].velocidade;
		if(bala[i].x > LARGURA)
			bala[i].vida = false;
	}
}*/
