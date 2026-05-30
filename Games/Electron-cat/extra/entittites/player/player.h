

float px, py, pa, pax; // pa = player acceleration, we only have horizontal acceleration
int coyote=0;

#define PLAYER_SPEED 1
#define GRAVITY 0.4
#define FRICTION 0.5

int p_sprite;
bool is_on_floor = 0;

// 71x100
bool was_measuring = 0;
void player_logic(tilemap * cat, tilemap * explosion, texture * player_marker){

	selected_tilemap = cat;

	if(nltimer==-1 || nltimer>2.5){
	// walls

		if( (measuring || map_buffer[(int)(py+8)/16][(int)(px)/16] != 1) && key_is_pressed("left")){
			pax -= PLAYER_SPEED;
			set_tilemap_scale(-1,1);
		}

		if( (measuring || map_buffer[(int)(py+8)/16][(int)(px+16)/16] != 1) && key_is_pressed("right")){
			pax += PLAYER_SPEED;
			set_tilemap_scale(1,1);
		}


		pax = clamp(pax, -4.5, 4.5);
		if(pax > 0) pax -= FRICTION;
		else if(pax < 0) pax += FRICTION;
		px += pax;



		if( !measuring ){
			if( map_buffer[(int)(py+8)/16][(int)(px)/16] == 1){
				px = (int)(px/16 + 1) * 16;
				pax = 0;
			}

			if( map_buffer[(int)(py+8)/16][(int)(px+16)/16] == 1){
				px = (int)((px+16)/16) * 16 - 16;
				pax = 0;
			}
		}



			if(pa>8) pa=8;
			py+=pa;
			pa+=GRAVITY;



		if(py>320){ py=320; is_on_floor=1; }
		if(py<32) {py=32; pa=1; }

		if(px>592) px=592;
		if(px<32)px=32;





		// roofs
		if(
			(map_buffer [(int)(py)/16] [(int)(px+4)/16] == 1 ||
			map_buffer [(int)(py)/16] [(int)(px+12)/16] == 1) &&
			!measuring
		) pa=1;





		// floor

		// Detect the moment measuring is turned off (collision resumes)
		if (was_measuring && !measuring) {
			if (map_buffer[(int)(py+8)/16][(int)(px+4)/16] == 1 ||
				map_buffer[(int)(py+8)/16][(int)(px+12)/16] == 1 ||
				map_buffer[(int)(py)/16][(int)(px+4)/16] == 1 ||
				map_buffer[(int)(py)/16][(int)(px+12)/16] == 1) {
				player_alive = 0;
				}
		}
		was_measuring = measuring;



		if( (map_buffer [(int)(py+16)/16] [(int)(px+4)/16] == 1 ||
			map_buffer [(int)(py+16)/16] [(int)(px+12)/16] == 1)
			&& !measuring
		){

			int tile_top = ((int)(py+16)/16) * 16;

			py = tile_top - 16;
			pa = 0;
			is_on_floor = 1;



			} else if(py<320) is_on_floor = 0;




			if(map_buffer [(int)(py)/16] [(int)(px+4)/16] == 0) player_alive=0;


			if (is_on_floor) {
				coyote = 15; // e.g. 0.13 seconds
			} else {
				coyote--;
			}

			if(key_is_pressed("z") || key_is_pressed("up")){

				if (coyote > 0) {
					is_on_floor=1;
					coyote = 0; // prevent double-jumping
				}


				if(is_on_floor){
					coyote==0;
					pa=-7;
					is_on_floor=false;
				}
			}





		if(map_buffer [(int)(py+15)/16] [(int)(px+4)/16] == 5|| map_buffer [(int)(py+15)/16] [(int)(px+12)/16]==5){

			spring_animation[(int)(py+15)/16][(int)(px+8)/16]=1;
			pa=-10;
		}



		if(key_is_pressed("v") || key_is_pressed("x")) measuring=1;
		else measuring=0;





	}


	set_tilemap_color(accent_color);



	if(pa==0){
		if(!key_is_pressed("left") && !key_is_pressed("right")){

			switch(wrap(timer, 61)){
				case 10: p_sprite=0; break;
				case 20: p_sprite=1; break;
				case 30: p_sprite=2; break;
				case 40: p_sprite=3; break;
				case 50: p_sprite=2; break;
				case 60: p_sprite=1; break;

			}

		}
		else{
			if(wrap(timer,20)<=10) p_sprite=6;
			else if(wrap(timer,20)>=10) p_sprite=7;
		}

	}

	if(!is_on_floor){

		if(pa>0.0) p_sprite=5;
		else p_sprite=4;

	}



	if(!measuring)

		draw_tile(px+ (16*(selected_tilemap->source.scale[0]<0)), py, p_sprite);


		if (player_accesibility && measuring){

		selected_texture = player_marker;


		set_scale(selected_tilemap->source.scale[0], 1);



		draw_texture(px+20-(20*(selected_tilemap->source.scale[0]>0)), py+16);

	}






}
