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

	// bola
	float ball_x = 400; // Posición inicial X
	float ball_y = 390; // Posición inicial Y
	float ball_radius = 10; // Radio de la bola
	float ball_dx = 1; // Velocidad en X
	float ball_dy = 3.5; // Velocidad en Y

	//Nave
	float nave_x = 300;
	float nave_y = 400; 
	float nave_width = 120;
	float nave_height = 20;

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
		//movimiento de la nave
		if (nave_x + 125> width)
			derecha=false;
		if (nave_x < 0)
			izquierda = false;
		if (derecha)
			nave_x += 2;
		if (izquierda)
			nave_x -= 2;

		ball_x += ball_dx;
		ball_y += ball_dy;


		if (ball_x - ball_radius < 0 || ball_x + ball_radius > 720) {
			ball_dx *= -0.9; // Rebotar en X
		}
		if (ball_y - ball_radius < 0) {
			ball_dy *= -0.9; // Rebotar en Y
		}
		if (ball_y + ball_radius >= nave_y && ball_y - ball_radius <= nave_y + nave_height &&
			ball_x + ball_radius >= nave_x && ball_x - ball_radius <= nave_x + nave_width) {
			ball_dy *= -1; // Rebotar en Y
			ball_y = nave_y - ball_radius; // Ajustar la posición de la bola para que no se solape
		}

		//si el teclado esta presionado
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
			al_draw_filled_rectangle(nave_x, nave_y, nave_x + nave_width, nave_y + nave_height, al_map_rgb(255, 0, 0)); // Rectángulo verde
			al_draw_filled_circle(ball_x, ball_y, ball_radius, al_map_rgb(255,255, 255)); // Bola roja
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


