#ifndef EPSILON_DRAWING_H
#define EPSILON_DRAWING_H


struct texture{
	int texture_data;	// used to be an SDL texture, now it is the texture ID
	int color;
	int x, y;
	int[4] mask;
	float[2] scale;
	int angle;
	int origin_x, origin_y;
	bool loaded;

} ;

texture *selected_texture = NULL;



void load_texture(int texture){


	selected_texture->x=0;
	selected_texture->y=0;
	selected_texture->mask[0]=0;
	selected_texture->mask[1]=0;
	selected_texture->mask[2]=1024;
	selected_texture->mask[3]=1024;

	selected_texture->scale[0]=1;
	selected_texture->scale[1]=1;
	selected_texture->angle=0;
	selected_texture->origin_x=0;
	selected_texture->origin_y=0;

	if(!selected_texture->loaded){
		selected_texture->loaded=true;
		selected_texture->texture_data = texture;
		select_texture(selected_texture->texture_data);
	}
}



texture * create_texture(int path){

	texture* tex = malloc(sizeof(texture));

	tex->x=0;
	tex->y=0;
	tex->mask[0]=0;
	tex->mask[1]=0;
	tex->mask[2]=1024;
	tex->mask[3]=1024;

	tex->scale[0]=1;
	tex->scale[1]=1;
	tex->angle=0;
	tex->origin_x=0;
	tex->origin_y=0;
	tex->loaded = false;

	selected_texture = tex;

	load_texture(path);

	return tex;
}



void set_scale(float x, float y){
	select_texture(selected_texture->texture_data);
	selected_texture->scale[0]=x;
	selected_texture->scale[1]=y;
}




void set_origin(int x, int y){
	select_texture(selected_texture->texture_data);
	select_region(0);
	selected_texture->origin_x=selected_texture->mask[0] + x;
	selected_texture->origin_y=selected_texture->mask[1] + y;

}



void set_mask(int x, int y, int w, int h){


	select_texture(selected_texture->texture_data);
	select_region(0);
	selected_texture->mask[0]=x;
	selected_texture->mask[1]=y;
	selected_texture->mask[2]=w;
	selected_texture->mask[3]=h;
	selected_texture->origin_x=selected_texture->mask[0];
	selected_texture->origin_y=selected_texture->mask[1];
}


void draw_texture(int x, int y){
	//1 select texture; 2 set mask, 3 set origin, draw zoomed.
	select_region(0);
	int mx=selected_texture->mask[0];
	int my=selected_texture->mask[1];
	int mw = selected_texture->mask[0] + selected_texture->mask[2] - 1;
	int mh = selected_texture->mask[1] + selected_texture->mask[3] - 1;

	int ox = selected_texture->mask[0] + selected_texture->origin_x;
	int oy = selected_texture->mask[1] + selected_texture->origin_y;

	int col= selected_texture->color;

	select_texture(selected_texture->texture_data);
	set_drawing_scale(selected_texture->scale[0], selected_texture->scale[1]);



	asm
	{
		"mov R0, {mx}"
		"out GPU_RegionMinX, R0"
		"mov R0, {my}"
		"out GPU_RegionMinY, R0"
		"mov R0, {mw}"
		"out GPU_RegionMaxX, R0"
		"mov R0, {mh}"
		"out GPU_RegionMaxY, R0"
		"mov R0, {ox}"
		"out GPU_RegionHotSpotX, R0"
		"mov R0, {oy}"
		"out GPU_RegionHotSpotY, R0"

		"mov R0, {col}"
		"out GPU_MultiplyColor, R0"

		"mov R0, {x}"
		"out GPU_DrawingPointX, R0"
		"mov R0, {y}"
		"out GPU_DrawingPointY, R0"
		"out GPU_Command, GPUCommand_DrawRegionZoomed"
	}

}



void destroy_texture(){} // this one is literally useless here





// this is a funny one, I accidentally made this function totally complaint with Carra's draw primitives lib

void draw_line( int x1, int y1, int x2, int y2 ){
	// select the bios's white pixel region
	asm{ "out GPU_SelectedTexture, -1"
		"out GPU_SelectedRegion, 256" }

		// careful with this case or atan2
		// will produce a hardware error
		if( x1 == x2 && y1 == y2 )
		{
			draw_region_at( x1, y1 );
			return;
		}

		// convert line to polar coordinates
		int delta_x = x2 - x1;
		int delta_y = y2 - y1;
		float line_distance = 1 + sqrt( delta_x * delta_x + delta_y * delta_y );
		float line_angle = atan2( delta_y, delta_x );

		// draw the line
		set_drawing_angle( line_angle );
		set_drawing_scale( line_distance, 1 );
		draw_region_rotozoomed_at( x1, y1 );
		set_drawing_scale(1, 1);
}



void draw_rect(int x, int y, int w, int h){
	// select the bios's white pixel region
	asm{ "out GPU_SelectedTexture, -1"
		"out GPU_SelectedRegion, 256" }

		// draw the filled rectangle
		// by stretching the pixel
		set_drawing_scale( w, h );
		draw_region_zoomed_at( x, y );
		set_drawing_scale(1, 1);
}



void draw_point(int x, int y){

	asm
	{
		// select the bios's white pixel region
		"out GPU_SelectedTexture, -1"
		"out GPU_SelectedRegion, 256"

		// draw it at the requested position
		"mov R0, {x}"
		"out GPU_DrawingPointX, R0"
		"mov R0, {y}"
		"out GPU_DrawingPointY, R0"
		"out GPU_Command, GPUCommand_DrawRegion"
	}
}



void render(){} // useless on vircon context too.


void set_render_color(int rgba){

	asm
	{
		"mov R0, {rgba}"
		"out GPU_MultiplyColor, R0"
	}

}


void set_texture_color(int rgba) {

	selected_texture->color = rgba;

}



#include "drawing_tiles.h"

#endif
