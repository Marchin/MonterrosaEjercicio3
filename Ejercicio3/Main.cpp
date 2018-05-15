#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480
#define REC_WIDTH 15
#define REC_HEIGHT 60
#define WHITE al_map_rgb(255, 255, 255)

int main(int argc, char **argv) {
	ALLEGRO_DISPLAY *display = NULL;
	float posP1_x = 0;
	float posP1_y = 0;
	float posP2_x = SCREEN_WIDTH - REC_WIDTH;
	float posP2_y = 0;

	if (!al_init()) {
		fprintf(stderr, "failed to initialize allegro!\n");
		return -1;
	}

	display = al_create_display(SCREEN_WIDTH, SCREEN_HEIGHT);
	if (!display) {
		fprintf(stderr, "failed to create display!\n");
		return -1;
	}

	al_init_primitives_addon();

	//al_clear_to_color(al_map_rgb(0, 0, 0));

	al_draw_filled_rectangle(posP1_x, posP1_y, 
		posP1_x + REC_WIDTH, posP1_y + REC_HEIGHT, WHITE);


	al_draw_filled_rectangle(posP2_x, posP2_y, 
		posP2_x + REC_WIDTH, posP2_y + REC_HEIGHT, WHITE);

	al_flip_display();

	al_rest(10.0);

	al_destroy_display(display);

	return 0;
}