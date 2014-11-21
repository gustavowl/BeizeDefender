#include <iostream>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include "TelaInicial.h"
#include "GameManager.h"


 
const float FPS = 30;
int Altura = 640;
int Largura = 1024;
const int BOUNCER_SIZE = 32;

ALLEGRO_DISPLAY *display = NULL;
ALLEGRO_EVENT_QUEUE *event_queue = NULL;
ALLEGRO_TIMER *timer = NULL;
ALLEGRO_BITMAP *novo_jogo = NULL;
ALLEGRO_BITMAP *instrucoes = NULL;
ALLEGRO_BITMAP *creditos = NULL;
ALLEGRO_BITMAP *sair = NULL;


TelaInicial::TelaInicial()
{}

void TelaInicial::Finalizar()
{
      al_destroy_bitmap(novo_jogo);
      al_destroy_bitmap(instrucoes);
      al_destroy_bitmap(creditos);
      al_destroy_bitmap(sair);

      al_destroy_timer(timer);
      al_destroy_event_queue(event_queue);
      al_destroy_display(display);
      al_uninstall_mouse();
}
 
int TelaInicial::Inicializar()
{
 
   if(!al_init()) {
      std::cout <<  "failed to initialize allegro!" << std::endl;
      return -1;
   }
 
   timer = al_create_timer(1.0 / FPS);
   if(!timer) {
      std::cout <<  "failed to create timer!" << std::endl;
      return -1;
   }
 
   display = al_create_display(Largura, Altura);

   if(!display) {
      std::cout <<  "failed to create display!" << std::endl;
      al_destroy_timer(timer);
      return -1;
   }
 
   al_install_keyboard();
   al_init_image_addon();

   novo_jogo = al_load_bitmap("mnuNewGame.bmp");
   instrucoes = al_load_bitmap("mnuOptions.bmp");
   creditos = al_load_bitmap("mnuHighscoresM.bmp");
   sair = al_load_bitmap("mnuExit.bmp");


   int novo_jogo_x = al_get_bitmap_width(novo_jogo);
   int novo_jogo_y = al_get_bitmap_height(novo_jogo);
   int sair_x = al_get_bitmap_width(sair);
   int sair_y = al_get_bitmap_height(sair);
 
   al_clear_to_color(al_map_rgb(255, 0, 255));
 
   al_set_target_bitmap(al_get_backbuffer(display));
 
   event_queue = al_create_event_queue();
   if(!event_queue) {
      std::cout <<  "failed to create event_queue!" << std::endl;
      al_destroy_bitmap(novo_jogo);
      al_destroy_bitmap(instrucoes);
      al_destroy_bitmap(creditos);
      al_destroy_bitmap(sair);

      al_destroy_display(display);
      al_destroy_timer(timer);
      return -1;
   }

   if ( !al_install_mouse() ) {
      al_destroy_event_queue(event_queue);
      al_destroy_timer(timer);
      al_destroy_display(display);
      return -1;
   }
 
   al_register_event_source(event_queue, al_get_display_event_source(display));
   al_register_event_source(event_queue, al_get_keyboard_event_source());
   al_register_event_source(event_queue, al_get_mouse_event_source());
   al_register_event_source(event_queue, al_get_timer_event_source(timer));
   al_start_timer(timer);
 
   while(display != NULL)
   {
      ALLEGRO_EVENT ev;
      al_wait_for_event(event_queue, &ev);
 

      al_draw_bitmap(novo_jogo, 384, 160, 0);
      al_draw_bitmap(instrucoes, 384, 240, 0);
      al_draw_bitmap(creditos, 384, 320, 0);
      al_draw_bitmap(sair, 448, 400, 0);

      //switch(ev.keyboard.keycode)
      if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
         break;
      }

      if(ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
      {

         
         if(ev.mouse.button & 1)
         {
               /*Novo Jogo*/
               if(ev.mouse.x >= 384 && ev.mouse.y >=160 && ev.mouse.y <= 206)
               {
                  Finalizar();
                  display = NULL;
                  GameManager GM;
                  GM.Executar();

               }
               /*Instruções*/
               if(ev.mouse.x >= 384 && ev.mouse.y >=240 && ev.mouse.y <= 291)
                     std::cout << "eu faço algo" << std::endl;
               /*Creditos*/
               if(ev.mouse.x >= 384 && ev.mouse.y >=320 && ev.mouse.y <= 369)
                     std::cout << "eu faço algo" << std::endl;
               /*Sair*/
               if(ev.mouse.x >= 448 && ev.mouse.y >=400 && ev.mouse.y <= 451)
                     std::cout << "eu faço algo" << std::endl;
         }
      }

     
      if (display != NULL) {
         al_flip_display();
         al_clear_to_color(al_map_rgb(0,0,0));
      }

   }

 
  
   
   //al_destroy_display(display);
   
 
}