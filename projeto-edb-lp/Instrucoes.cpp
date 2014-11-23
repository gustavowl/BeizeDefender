#include <allegro5/allegro.h> 
#include <allegro5/allegro_image.h>
#include "Instrucoes.h"


Instrucoes::Instrucoes()
{}

int Instrucoes::Executar(ALLEGRO_EVENT_QUEUE * event_queue,  ALLEGRO_EVENT &ev, ALLEGRO_DISPLAY *display)
{
   
    ALLEGRO_BITMAP *instrucao = NULL;

   
    instrucao = al_load_bitmap("instrucoes.png");

    al_draw_bitmap(instrucao, 0, 0, 0);

	al_flip_display();
	al_clear_to_color( al_map_rgb(0,0,0));

    while(true) 
    {
      if ( al_get_next_event(event_queue, &ev) ) 
      {

        if(ev.mouse.button & 1)
        {
              /*Novo Jogo*/

        	/*

				jogar (x1 = 771, y1 = 48, x2 = 1011, y2 = 111)
voltar (x1 = 771, y1 = 544, x2 = 1011, y2 = 607)

        	*/
              if(ev.mouse.x >= 771 &&  ev.mouse.x <= 1011 && ev.mouse.y >=48 && ev.mouse.y <= 111)
              {
                    
                    al_destroy_bitmap(instrucao);

                    return 1;
              }
              /*Instruções*/
              if(ev.mouse.x >= 771 &&  ev.mouse.x <= 1011 && ev.mouse.y >=544 && ev.mouse.y <= 607)
              {

                    al_destroy_bitmap(instrucao);

                    return 0;
              }
            
        }
      }
    }
}