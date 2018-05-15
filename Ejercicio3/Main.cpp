#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480
#define REC_WIDTH 15
#define REC_HEIGHT 60
#define WHITE al_map_rgb(255, 255, 255)

int main(int argc, char **argv) {
	ALLEGRO_DISPLAY* display = NULL;
	ALLEGRO_EVENT_QUEUE* event_queue = NULL;
	ALLEGRO_KEYBOARD_STATE keyState;
	const float FPS = 60.0;
	bool exit = false;
	float posP1_x = 0;
	float posP1_y = 0;
	float posP2_x = SCREEN_WIDTH - REC_WIDTH;
	float posP2_y = 0;
	float moveSpeed = 5;

	if (!al_init()) {
		fprintf(stderr, "failed to initialize allegro!\n");
		return -1;
	}

	display = al_create_display(SCREEN_WIDTH, SCREEN_HEIGHT);
	if (!display) {
		fprintf(stderr, "failed to create display!\n");
		return -1;
	}

	event_queue = al_create_event_queue();
	if (!event_queue) {
		fprintf(stderr, "failed to create event_queue!\n");
		al_destroy_display(display);
		return -1;
	}

	ALLEGRO_TIMER* timer = al_create_timer(1.0 / FPS);
	al_init_primitives_addon();
	al_install_keyboard();	
	al_register_event_source(event_queue, al_get_keyboard_event_source());
	al_register_event_source(event_queue, al_get_timer_event_source(timer));
	al_start_timer(timer);

	al_clear_to_color(al_map_rgb(0, 0, 0));
	al_flip_display();

	while (!exit) {
		ALLEGRO_EVENT events;
		al_wait_for_event(event_queue, &events);

		if (events.type == ALLEGRO_EVENT_KEY_UP) {
			switch (events.keyboard.keycode) {
				case ALLEGRO_KEY_ESCAPE:
					exit = true;
			}
		}

		if (events.type == ALLEGRO_EVENT_TIMER) {
			al_get_keyboard_state(&keyState);
			if (al_key_down(&keyState, ALLEGRO_KEY_S) &&
				(posP1_y<SCREEN_HEIGHT - REC_HEIGHT)) {

				posP1_y += moveSpeed;
			} else if (al_key_down(&keyState, ALLEGRO_KEY_W) &&
				(posP1_y>0)) {

				posP1_y -= moveSpeed;
			}
			if (al_key_down(&keyState, ALLEGRO_KEY_DOWN) &&
				(posP2_y<SCREEN_HEIGHT - REC_HEIGHT)) {

				posP2_y += moveSpeed;
			}
			else if (al_key_down(&keyState, ALLEGRO_KEY_UP) &&
				(posP2_y>0)) {

				posP2_y -= moveSpeed;
			}
		}

		al_draw_filled_rectangle(posP1_x, posP1_y,
			posP1_x + REC_WIDTH, posP1_y + REC_HEIGHT, WHITE);


		al_draw_filled_rectangle(posP2_x, posP2_y,
			posP2_x + REC_WIDTH, posP2_y + REC_HEIGHT, WHITE);

		al_flip_display();
		al_clear_to_color(al_map_rgb(0, 0, 0));
	}

	al_destroy_display(display);

	return 0;
}