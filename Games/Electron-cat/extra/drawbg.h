// void load_map(int* map_buffer, int* maps, int map_id){
// 	for (int y = 0; y < 23; y++)
// 		for (int x = 0; x < 40; x++)
// 			map_buffer[y][x] = maps[map_id][y][x];
// }

void draw_bg(){

	clear_screen(back_color);

	set_render_color(back_color - 0x05050500);

	for(int x=0; x<56; x++){

		for(int y=0; y<23; y++){

			int xpos = x*19+sin(y+timer/30.0)*3;
			int ypos = y*19+cos(x+timer/30.0)*3;

			if(gamestate==3 || (xpos>18 && xpos<606 && ypos>18 && ypos<326 )) draw_rect(xpos, ypos, 18, 18);

		}


	}



}
