// Arkanoid.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <iostream>
#include <stdio.h>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>

#define FPS 60.0
#define FPS2 30.0

using namespace std;
int main()
{
	if (!al_init()) {
		al_show_native_message_box(NULL, "Ventana Emergente", "Error", "No se puede inicializar Allegro", NULL, NULL);
		return 0;
	}

	al_init_font_addon();
	al_init_ttf_addon();
	al_init_image_addon();
	al_init_primitives_addon();
	al_install_keyboard();
	al_install_mouse();

	ALLEGRO_DISPLAY* Pantalla = al_create_display(720, 480);
	ALLEGRO_EVENT_QUEUE* Eventos= al_create_event_queue();
	ALLEGRO_TIMER*Timer= al_create_timer(1.0 / FPS);
	ALLEGRO_BITMAP* Bitmap = NULL;

	Bitmap = al_load_bitmap("mapa de bits.png");
	assert(Bitmap != NULL);


	al_register_event_source(Eventos, al_get_keyboard_event_source());
	al_register_event_source(Eventos, al_get_display_event_source(Pantalla));
	al_register_event_source(Eventos, al_get_mouse_event_source());
	al_register_event_source(Eventos, al_get_timer_event_source(Timer));

	bool juego = true;
	bool derecha = false,izquierda=false;
	float x = 360, y=400;
	int width = al_get_display_width(Pantalla);
	al_start_timer(Timer);
	while (juego)
	{
		
		ALLEGRO_EVENT Evento;
		al_wait_for_event(Eventos, &Evento);

		if (Evento.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
		{
			juego = false;
		}
		if (x + 200> width)
			derecha=false;
		if (x < 0)
			izquierda = false;
		if (derecha)
			x += 2;
		if (izquierda)
			x -= 2;
		
		if (Evento.type == ALLEGRO_EVENT_KEY_DOWN)
		{
			if (Evento.keyboard.keycode == ALLEGRO_KEY_RIGHT)
			{
				derecha = true;
			}
			if (Evento.keyboard.keycode == ALLEGRO_KEY_LEFT)
			{
				izquierda = true;
			}
		}
		if (Evento.type == ALLEGRO_EVENT_KEY_UP)
		{
			if (Evento.keyboard.keycode == ALLEGRO_KEY_RIGHT)
			{
				derecha = false;
			}
			if (Evento.keyboard.keycode == ALLEGRO_KEY_LEFT)
			{
				izquierda = false;
			}
		}

		if (Evento.type == ALLEGRO_EVENT_TIMER)
		{
			al_clear_to_color(al_map_rgb(0, 0, 255));
			al_draw_bitmap(Bitmap, x, y,0);
			al_flip_display();
		}
		
	}

	al_destroy_display(Pantalla);
	al_uninstall_keyboard();
	al_uninstall_mouse();
	al_destroy_bitmap(Bitmap);
	al_destroy_timer(Timer);
	return 0;
}

