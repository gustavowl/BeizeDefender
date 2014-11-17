#include <iostream>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <math.h>
#include "GameObject.h"
#include "ListaEncadeada/lista.h"
#include "Projetil.h"
#include "Base.h"
#include "Player.h" //fix


using namespace go;

void DrawProjetil(Lista<Projetil*> projeteis); //=D
void DrawPlayer(GameObject player);
void DrawInimigo(GameObject inimigo);
void CollideProjetil(GameObject player, Lista<GameObject*> projeteis, unsigned int raio_j, unsigned int raio_p);
GameObject Distancia(GameObject a, GameObject b);//remover


int main() {
  int i, X, Y, fps = 30;
  unsigned int speed = 10; //pixels por segundos
  float v, qtd_ite = 0;
  bool done = false;
  
  GameObject arena(1024, 640); 
  Player player(1024/2, 640/2);//atualizado
  GameObject inimigo(10, 320, 1, 10, LINEAR);
  Base base(380,200,620,440);//atualizado

  
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
	//std::cout << "x: " << (int)arena.GetMaxX() << " y: " << (int)arena.GetMaxY() << std::endl;
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
          player.Atirar(ev.mouse.x, ev.mouse.y); //oks
              /*player.Mover();
  			      inimigo = Distancia(inimigo, player);
				      inimigo.Mover();
		          //TAREFA PENDENTE: realizar cálculo para ir até o fim da tela
		          //player->atirar();
		          
		          Projetil *projetil = new Projetil(player.GetXAtual(), player.GetYAtual(), ev.mouse.x, ev.mouse.y);
		          teste = projetil;
		          
		          projeteis.Insert(projeteis.Size(), projetil);
		          
						//	FireProjetil(projeteis, projeteis.Size());*/

				}
			}

			else if (ev.type == ALLEGRO_EVENT_TIMER) { 
				player.Mover(); //já move os projéteis do player
				inimigo = Distancia(inimigo, player);
				inimigo.Mover();
        int i = 0;
        Lista<Projetil*> projeteis_from_player = player.GetProjeteisToDraw();
        /*GameObject *temp;
        while ( projeteis.GetElem(i, temp) ) {
          temp->Mover();
          i++;
        }*/
        
				//al_draw_rectangle(180, 160, 480, 320, al_map_rgb(255, 0, 255), 10);
        base.DrawBase();
				DrawProjetil(projeteis_from_player);
				DrawPlayer(player);
				DrawInimigo(inimigo);
				//CollideProjetil(player, projeteis, 10, 2);
				al_flip_display();
				al_clear_to_color(al_map_rgb(0,0,0));
				player.VerificarColisao(inimigo);
        base.LevarDano( player.VerificarColisao(base) );

			}
		}
	}
}



void DrawPlayer(GameObject player)
{
  int i = 0;
  unsigned int x, y;
  player.GetPosicaoAtual(x, y);
  //std::cout << x << ' ' << y << std::endl;
  al_draw_filled_circle(x, y, 10, al_map_rgb(0, 255, 0));
}

void DrawProjetil(Lista<Projetil*> projeteis)
{
  int i = 0;
  unsigned int x, y;
  Projetil *temp;
  while ( projeteis.GetElem(i, temp) ) {
    temp->GetPosicaoAtual(x, y);
    al_draw_filled_circle(x, y, 2, al_map_rgb(255, 255, 255));
    i++;
  }

}

void DrawInimigo(GameObject inimigo)
{
  int i = 0;
  unsigned int x, y;
  inimigo.GetPosicaoAtual(x, y);
  //std::cout << x << ' ' << y << std::endl;
  al_draw_filled_circle(x, y, 10, al_map_rgb(100, 100, 100));
}

GameObject Distancia(GameObject a, GameObject b){
	float distJogador = sqrt( pow(a.GetXAtual() - b.GetXAtual(), 2) + pow(a.GetYAtual() - b.GetYAtual(), 2) );

	float distbase = sqrt( pow(a.GetXAtual() - (640/2), 2) + pow(a.GetYAtual() - (480/2), 2) );

	if(distJogador >= distbase){
		a.AtualizarDestino(b.GetXAtual(), b.GetYAtual());
		a.Mover();
		return a;
	}
	else{
		a.AtualizarDestino((640/2), (480/2));
		a.Mover();
		return a;
	}
}


