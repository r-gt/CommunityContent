
int dtimer=0;


void game_over(int px, int py, tilemap * explosion, audio * sound, texture * killscreen){
	dtimer++;
	set_render_color(0xFFFFFFFF);


	selected_audio = sound;
	if(dtimer==1) play_audio();


	selected_tilemap = explosion;
	if(dtimer>1 && dtimer<10) draw_tile(px-30,py-50,0);
	if(dtimer>9 && dtimer<20) draw_tile(px-30,py-50,1);
	if(dtimer>19 && dtimer<30) draw_tile(px-30,py-50,2);
	if(dtimer>29 && dtimer<40) draw_tile(px-30,py-50,3);
	if(dtimer>39 && dtimer<50) draw_tile(px-30,py-50,4);
	if(dtimer>49 && dtimer<60) draw_tile(px-30,py-50,5);
	if(dtimer>59 && dtimer<70) draw_tile(px-30,py-50,6);
	if(dtimer>69 && dtimer<80) draw_tile(px-30,py-50,7);
	if(dtimer>79 && dtimer<90) draw_tile(px-30,py-50,8);


	 player_alive=0;


	selected_texture = killscreen;
	set_mask(0,0,388,75);

	set_scale(1 + sin(timer/20.0)/10.0, 1+cos(timer/20.0)/5.0);

	draw_texture(290- killscreen->scale[0]*338/2 , 100 - killscreen->scale[1]*75/2);

	set_scale(1,1);

	set_texture_color(0xFFFFFFFF);

	for(int i=0; i<58; i++){


		set_mask(89+i*4, 109, 8, 16);
		draw_texture(297+i*8, 280+sin((timer+(i*4))/20.0)*3);

	}

	for(int i=0; i<116; i++){

		set_mask(90+i*2, 126, 4, 14);
		draw_texture(300+i*4, 300+sin((timer+(i*2))/20.0)*3);

	}

}



