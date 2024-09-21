//rkanoid.cpp : Este archivo contiene la función "main".La ejecución del programa comienza y termina ahí.
//

#include <iostream>
#include <stdio.h>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <algorithm>
#include <random>

#define FPS 120.0
#define FPS2 30.0


using namespace std;

typedef struct Bloques
{
	float x;
	float y;
	float width;
	float height;
	bool rompe;
	int golpes;
	int ColorR;
	int ColorG;
	int ColorB;
	Bloques* Sig;
}*Blocks;

Blocks CrearBloque(float pos_x, float pos_y, float tamaño, float altura, bool rom, int gol)
{

	Blocks bloque = new (Bloques);
	bloque->x = pos_x;
	bloque->y = pos_y;
	bloque->width = tamaño;
	bloque->height = altura;
	bloque->rompe = rom;
	bloque->golpes = gol;
	bloque->ColorR = rand() % 255;
	bloque->ColorG = rand() % 255;
	bloque->ColorB = rand() % 255;
	bloque->Sig = NULL;
	return bloque;
}
void agregarFinal(Blocks& Lista, Blocks Nuevo)
{
	Blocks Aux;//Puntero creado
	Aux = Lista;//Puntero apunta a la misma dirección que Lista
	if (Aux != NULL)//si la lista no esta vacia
	{
		while (Aux->Sig != NULL)//Puntero siguiente no es null entonces
		{
			Aux = Aux->Sig;//el Aux apunta a lo que apuntaba el puntero siguiente
		}

		Aux->Sig = Nuevo;//el puntero siguiente del elemento ahora apunta al nuevo elemento
	}
	else//si la lista esta vacia
	{
		Lista = Nuevo;//Lista apunta al nuevo elemento
	}


}
void nivel(Blocks& lista, int nivel)
{
	Blocks nuevo;
	float width = 40;
	float height = 15;
	int fila = 1;
	switch (nivel)

	{
	case 1:
		for (int fila = 0; fila < 5; fila++)
		{
			for (int i = 0; i < 18; i++)
			{
				nuevo = CrearBloque((width * i), (height * fila), width, height, true, 1);
				agregarFinal(lista, nuevo);
			}
		}
		break;
	}

}
void eliminarBloque(Blocks& lista, Blocks bloque)
{
	Blocks Aux;
	Aux = lista;
	bool encontro = false;
	while (!encontro)
	{
		if (Aux->Sig == bloque)
		{
		encontro = true;
		Aux->Sig=bloque->Sig;
		}
		else
			Aux = Aux->Sig;
	}
	delete bloque;
}
int main()
{
	int level = 1;
	Blocks lista;
	lista = NULL;
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
	//se crean punteros a funciones de allegro
	ALLEGRO_DISPLAY* Pantalla = al_create_display(720, 480);
	ALLEGRO_EVENT_QUEUE* Eventos = al_create_event_queue();
	ALLEGRO_TIMER* Timer = al_create_timer(1.0 / FPS);
	ALLEGRO_BITMAP* Bitmap = NULL;
	//no se usa es un ejemplo de cargar imagenes
	Bitmap = al_load_bitmap("mapa de bits.png");
	assert(Bitmap != NULL);

	//se agrega un regostro de cada evento en eventos
	al_register_event_source(Eventos, al_get_keyboard_event_source());
	al_register_event_source(Eventos, al_get_display_event_source(Pantalla));
	al_register_event_source(Eventos, al_get_mouse_event_source());
	al_register_event_source(Eventos, al_get_timer_event_source(Timer));

	// bola
	float ball_x = 400; // Posición inicial X
	float ball_y = 390; // Posición inicial Y
	float ball_radius = 7; // Radio de la bola
	float ball_dx = 1; // Velocidad en X
	float ball_dy = 3; // Velocidad en Y

	//Nave
	float nave_x = 300;
	float nave_y = 400;
	float nave_width = 120;
	float nave_height = 20;

	bool juego = true;
	bool derecha = false, izquierda = false;
	float x = 360, y = 400;
	int width = al_get_display_width(Pantalla);
	al_start_timer(Timer);
	nivel(lista, level);

	Blocks Aux;
	while (juego)
	{
		Aux = lista;
		ALLEGRO_EVENT Evento;
		al_wait_for_event(Eventos, &Evento);
		//si se cierraa la ventana
		if (Evento.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
		{
			juego = false;
		}
		//movimiento de la nave
		if (nave_x + 125 > width)
			derecha = false;
		if (nave_x < 0)
			izquierda = false;
		if (derecha)
			nave_x += 2.5;
		if (izquierda)
			nave_x -= 2.5;

		//bola y sus movimientos
		ball_x += ball_dx;
		ball_y += ball_dy;
		if (ball_y >= 480 - ball_radius)
		{

			ball_x = 360;
			ball_y = 400;
		}
		if (ball_x <= ball_radius + 0 || ball_x >= 720 - ball_radius)
			ball_dx *= -1;
		if (ball_y <= ball_radius + 0)
			ball_dy *= -1;

		ball_x = min(ball_x, 720 - ball_radius);
		ball_x = max(ball_x, ball_radius);
		ball_y = max(ball_y, ball_radius);
		//todavia hay errores 


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
		// si el teclado ya no esta presionado
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
		//colisiones bola y bloques
		if (Aux != NULL)
		{
			while (Aux != NULL)//mientras no se haya llegado al final de lista se dibujan los bloques 
			{
				if (ball_y + ball_radius >= Aux->y && ball_y - ball_radius <= Aux->y + Aux->height &&
					ball_x + ball_radius >= Aux->x && ball_x - ball_radius <= Aux->x + Aux->width) {
					ball_dy *= -1; // Rebotar en Y

					Aux->golpes--;
					if (Aux->golpes == 0)
						eliminarBloque(lista, Aux);
					break;
				}
				Aux = Aux->Sig;
			}
		}
		Aux = lista;
		//si a pasado el tiempo entonces se hacen las acciones
		if (Evento.type == ALLEGRO_EVENT_TIMER)
		{
			al_clear_to_color(al_map_rgb(0, 0, 255));;
			while (Aux != NULL)//mientras no se haya llegado al final de lista se dibujan los bloques 
			{
				al_draw_filled_rectangle(Aux->x, Aux->y, Aux->x + Aux->width, Aux->y + Aux->height, al_map_rgb(Aux->ColorR, Aux->ColorG, Aux->ColorB));
				Aux = Aux->Sig;
			}
			al_draw_filled_rectangle(nave_x, nave_y, nave_x + nave_width, nave_y + nave_height, al_map_rgb(255, 0, 0)); // Rectángulo verde
			al_draw_filled_circle(ball_x, ball_y, ball_radius, al_map_rgb(255, 255, 255)); // Bola roja
			al_flip_display();//se actualiza la pantalla
		}
		
		
		

	}
	//se limpia la memoria de lo usado
	al_destroy_display(Pantalla);
	al_uninstall_keyboard();
	al_uninstall_mouse();
	al_destroy_bitmap(Bitmap);
	al_destroy_timer(Timer);
	return 0;
}


