#include "video.h"
#include "time.h"
#include "audio.h"
#include "input.h"
#include "misc.h"
#include "super_definitions.h"



int timer=0;
float nltimer=-1;
float inittimer=2.5; //2.5
float fintimer=0;

bool measuring=0;
bool player_alive = 1;
bool player_waiting = 0;
bool player_accesibility = 0;

bool q_state = 0;
bool f9_state =0;
bool f10_state =0;

int level = 0;
int points_to_reach = 0;



int actual_map=0;




int accent_color = 0xFFFFDF00;
int back_color = 0xFF221305;
int nloverlay_color = 0xFF120A03;

float bgm_volume = 0.6;

int gamestate=0; // 0:warning; 1:title; 2: actual game.
bool title_on = 0;



#include "extra/easings.h"
#include "extra/goodies.h"
#include "epsilon/engine.h"
#include "extra/Save maps.h"
#include "extra/gameover.h"

int[MAP_ROWS][MAP_COLS] map_buffer;
int[MAP_ROWS][MAP_COLS] spring_animation;

#include "extra/drawbg.h"
#include "extra/entittites/player/player.h"
#include "extra/menu/nextlevel/nextlevel.h"
#include "extra/playbgm.h"


void main(void){

	texture * player_marker = create_texture(player_png);
	set_origin(11,6);
	set_mask(9,4,5,2);
	set_texture_color(accent_color);

	tilemap * cat = create_tilemap(0, 0, 16, 16, 4, 2);
	load_texture_tilemap(player_png);
	set_tilemap_scale(01,1);



	tilemap * explosion = create_tilemap(0, 0, 71, 100, 6, 2);
	load_texture_tilemap(explosion_png);
	set_tilemap_color(0xFFFFFFFF);
	set_tilemap_scale(1,1);


	audio * explosion_a = create_audio(explosion_wav, 1);

	tilemap * world_texture = create_tilemap(0, 0, 16, 16, 6, 4);
	load_texture_tilemap(map_png);


	texture * nextlevel_texture = create_texture(box_png);
	set_texture_color(0xFFFFFFFF);

	texture * title_texture = create_texture(menu_png);

	texture * killscreen = create_texture(death_png);
	set_mask(0,0,388,75);

	texture * overlay1 = create_texture(map1_png);
	texture * overlay2 = create_texture(map2_png);
	texture * overlay3 = create_texture(map3_png);

	texture * finale = create_texture(finale_png);


	audio* bgm1 = create_audio(bg_remix1_wav, 0);
	audio* bgm2 = create_audio(bg_remix2_wav, 0);


	// even if defined, for some reason this specific audio didn't work, at all
	// sadly, i had to patch every line of code where this is used
	audio * win_sound = create_audio(win_wav, 0);


	audio * pickup_sound = create_audio(pickup_wav, 0);


	 for (int y = 0; y < 23; y++)
	 	for (int x = 0; x < 40; x++)
	 		map_buffer[y][x] = maps[level][y][x];



	while(running){ // set running=false to close the game.

		//clear_screen(back_color);
		draw_bg();
		timer++;

		switch(level){
			case(0): selected_texture=overlay1; set_texture_color(accent_color); draw_texture(0,0); break;
			case(1): selected_texture=overlay2; set_texture_color(accent_color); draw_texture(0,0); break;
			case(2): selected_texture=overlay3; set_texture_color(accent_color); draw_texture(0,0); break;
		}




		if(gamestate<3 && gamestate>0 ){


			set_render_color(nloverlay_color);


			if(
				(key_is_pressed("left") ||
				key_is_pressed("right") ||
				key_is_pressed("z") ||
				key_is_pressed("x") ||
				key_is_pressed("v") ||
				key_is_pressed("space") )&& !title_on
			){
				gamestate=1;
				title_on=1;
			}

			if(!title_on){
				selected_texture = title_texture;

				set_mask(0, 0, 315, 156);
				set_texture_color(0xFFFFFFFF);
				draw_texture(48,48);

			}

			if(gamestate>0) play_background_noise(bgm1, bgm2);



			if(key_is_pressed("r")){
				dtimer=0;
				player_alive=1;
				for (int y = 0; y < 23; y++)
					for (int x = 0; x < 40; x++)
						map_buffer[y][x] = maps[level][y][x];
			}

			points_to_reach = 0;



			int positrontimer = wrap(timer/5,4);

			selected_tilemap = world_texture;

			set_tilemap_scale(1,1);

			selected_audio = pickup_sound;
			if(map_buffer[(int)(py+8)/16][(int)(px+8)/16] == 4) play_audio();


			for(int x=0; x<40; x++){

				for(int y=0; y<23; y++){


					switch(map_buffer[y][x]){
						case -1: break;
						case 0:
							set_tilemap_color(0xFF0000FF);
							set_tilemap_scale(1,1);
							draw_tile(x*16,y*16, 1+6*positrontimer);
							break;

						case 1:
							set_tilemap_color(0xFFFFDC00);
							set_tilemap_scale(1,1); draw_tile(x*16,y*16, 2+6*wrap(timer/7,4));
							break;

						case 2:
							px=x*16;
							py=y*16;
							map_buffer[y][x]=-1;
							break;

						case 3:

							set_tilemap_color(0xFF007FFF);
							set_tilemap_scale(1,1); draw_tile(x*16,y*16, 5+6*wrap(timer/10,4));

							break;

						case 4:
							set_tilemap_color(0xFF00FFFF);
							set_tilemap_scale(1,1); draw_tile(x*16,y*16, 4+6*wrap(timer/16,4));
							points_to_reach++;
							break;

						case 5:

							if(spring_animation[y][x] !=0 && spring_animation[y][x] <16) spring_animation[y][x]++;
							else spring_animation[y][x]=0;

							set_tilemap_color(0xFF00FF00);
							set_tilemap_scale(1,1); draw_tile(x*16,y*16, (int)(3+6*(spring_animation[y][x]/4)) );
							break;


					}



				}

			}



			if(map_buffer[(int)(py+8)/16][(int)(px+8)/16] == 4) {
				map_buffer[(int)(py+8)/16][(int)(px+8)/16] = -1;
			}



			if(!player_alive && !player_waiting) game_over(px,py, explosion, explosion_a, killscreen);
			else player_logic(cat, explosion, player_marker);




			if(map_buffer[(int)(py+8)/16][(int)(px+8)/16] == 3 && points_to_reach==0) {
				player_waiting=1;


			}

			if(player_waiting){
				if(level< 13 || (level == 13 && !(nltimer == -1))){
					goto_next_level(nextlevel_texture, win_sound);


				}else if(level == 13){

					if(inittimer > 3 ){
						play_sound(win_wav);

					}


					inittimer-=0.01;

					if(inittimer<2.5) gamestate=3;


				}
			}


				if(timer>34 && inittimer < 3)inittimer+=0.005;

			if(level == 14) gamestate=3;
		}



		if(gamestate==3){
			stop_audio();
			if (inittimer < 3) inittimer+=0.005;

			selected_texture = finale;
			draw_texture(0,360-ease(fintimer, QUINT, BACK)*360);

			set_texture_color(accent_color);




			if (inittimer >= 3)fintimer+=0.01;
		}


		set_render_color(nloverlay_color);
		draw_rect(
			320-ease((inittimer+0.5)*2, QUINT, QUINT)*320 + ease((inittimer-2.5)*2, QUINT, QUINT)*320,
				  180-ease((inittimer+0.5)*2, QUINT, QUINT)*180 +ease((inittimer-2.5)*2, QUINT, QUINT)*180 ,
				  ease((inittimer+0.5)*2, QUINT, QUINT)*640 - ease((inittimer-2.5)*2, QUINT, QUINT)*640 ,
				  ease((inittimer+0.5)*2, QUINT, QUINT)*360 - ease((inittimer-2.5)*2, QUINT, QUINT)*360
		);

		if(gamestate==0){

			selected_texture = title_texture;

			set_mask(0,156,552,41);
			set_texture_color(0xFFFFFFFF);
			draw_texture(55, 320 + ease(timer/70.0-2.9, BACK, NONE) *200);
			//
			if(timer > 300) gamestate++;

		}

		if(player_accesibility){
			selected_texture = title_texture;
			set_mask(0, 208, 223, 16);

			set_texture_color(accent_color - 0x00505000);
			draw_texture(16,544);

		}

		if(level> 13) inittimer-=0.01;


		if (key_is_pressed("q")) {
			if (q_state == 0) {
				player_accesibility = !player_accesibility; // fire the toggle
				q_state = 1;
			}
		} else {
			q_state = 0;
		}


		if(player_waiting) measuring=0;
		end_frame();

	}
}
