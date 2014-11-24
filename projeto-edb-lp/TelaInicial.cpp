#include <allegro5/allegro.h> 
#include <allegro5/allegro_image.h>
#include "TelaInicial.h"

TelaInicial::TelaInicial()
{}

int TelaInicial::Executar(ALLEGRO_EVENT_QUEUE * event_queue,  ALLEGRO_EVENT &ev, ALLEGRO_DISPLAY *display)
{
    //ALLEGRO_BITMAP *game_over = NULL;
    //ALLEGRO_BITMAP *novo_jogo = NULL;
    //ALLEGRO_BITMAP *instrucoes = NULL;
    //ALLEGRO_BITMAP *creditos = NULL;
    //ALLEGRO_BITMAP *sair = NULL;

    ALLEGRO_BITMAP *menu = NULL;

    //novo_jogo = al_load_bitmap("mnuNewGame.bmp");
    //instrucoes = al_load_bitmap("mnuOptions.bmp");
    //creditos = al_load_bitmap("mnuHighscoresM.bmp");
    //sair = al_load_bitmap("mnuExit.bmp");

    menu = al_load_bitmap("Menu/Menu.png");

    //al_draw_bitmap(novo_jogo, 384, 160, 0);
    //al_draw_bitmap(instrucoes, 384, 240, 0);
    //al_draw_bitmap(creditos, 384, 320, 0);
    //al_draw_bitmap(sair, 448, 400, 0);

    al_draw_bitmap(menu, 0, 0, 0);

	al_flip_display();
	al_clear_to_color( al_map_rgb(0,0,0));

    while(true) 
    {
      if ( al_get_next_event(event_queue, &ev) ) 
      {

        if(ev.mouse.button & 1)
        {
              /*Novo Jogo*/
              if(ev.mouse.x >= 350 && ev.mouse.x <= 675 && ev.mouse.y >=122 && ev.mouse.y <= 206)
              {
                   // al_destroy_bitmap(novo_jogo);
                   // al_destroy_bitmap(instrucoes);
                   // al_destroy_bitmap(creditos);
                   // al_destroy_bitmap(sair);
                    al_destroy_bitmap(menu);

                    return 1;
              }
              /*Instruções*/
              else if(ev.mouse.x >= 350 && ev.mouse.x <= 675 && ev.mouse.y >=218 && ev.mouse.y <= 303) {

                  //  al_destroy_bitmap(novo_jogo);
                  //  al_destroy_bitmap(instrucoes);
                  //  al_destroy_bitmap(creditos);
                  //  al_destroy_bitmap(sair);
                    al_destroy_bitmap(menu);


                    return 2;
              }
              /*Creditos*/
              else if(ev.mouse.x >= 350 && ev.mouse.x <= 675 && ev.mouse.y >=315 && ev.mouse.y <= 397) 
              {
                  //  al_destroy_bitmap(novo_jogo);
                  //  al_destroy_bitmap(instrucoes);
                  //  al_destroy_bitmap(creditos);
                  //  al_destroy_bitmap(sair);
                    al_destroy_bitmap(menu);


                    return 3;
              }
              /*Sair*/
              else if(ev.mouse.x >= 350 && ev.mouse.x <= 675 && ev.mouse.y >=412 && ev.mouse.y <= 495) 
              {
                  //  al_destroy_bitmap(novo_jogo);
                  //  al_destroy_bitmap(instrucoes);
                  //  al_destroy_bitmap(creditos);
                  //  al_destroy_bitmap(sair);
                    al_destroy_bitmap(menu);
                    return 6;
              }
        }
      }
    }
}