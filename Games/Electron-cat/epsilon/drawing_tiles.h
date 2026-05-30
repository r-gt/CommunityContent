struct tilemap{
	int[2] grid;
	int[4] tile;
	texture source;

};

tilemap * selected_tilemap = NULL;


tilemap * create_tilemap(int t_x, int t_y, int t_w, int t_h, int grid_x, int grid_y){
	tilemap* tile = calloc(1,sizeof(tilemap));

	tile->tile[0] = t_x;
	tile->tile[1] = t_y;
	tile->tile[2] = t_w;
	tile->tile[3] = t_h;

	tile->grid[0] = grid_x;
	tile->grid[1] = grid_y;

	selected_tilemap = tile;
	return tile;

}

void load_texture_tilemap(int path) {
	texture* old_selected = selected_texture;       // saves current selected_texture
	selected_texture = &selected_tilemap->source;   // points at tilemap's embedded texture
	load_texture(path);                             // loads into it
	selected_texture = old_selected;                // restores — but now source.loaded = true...
}







void draw_tile(int x, int y, int selected) {
	int total = selected_tilemap->grid[0] * selected_tilemap->grid[1];
	selected = selected % total;

	int tile_x = selected % selected_tilemap->grid[0];
	int tile_y = selected / selected_tilemap->grid[0];

	select_texture(selected_tilemap->source.texture_data);  // ← FIRST
	set_drawing_scale(selected_tilemap->source.scale[0], selected_tilemap->source.scale[1]);

	define_region_topleft(                                  // ← THEN define region
	selected_tilemap->tile[0] + tile_x * selected_tilemap->tile[2],
	selected_tilemap->tile[1] + tile_y * selected_tilemap->tile[3],
	selected_tilemap->tile[0] + tile_x * selected_tilemap->tile[2] + selected_tilemap->tile[2] - 1,
	selected_tilemap->tile[1] + tile_y * selected_tilemap->tile[3] + selected_tilemap->tile[3] - 1
	);
	 asm
	 {
		 "mov R0, {x}"
		 "out GPU_DrawingPointX, R0"
		 "mov R0, {y}"
		 "out GPU_DrawingPointY, R0"
		 "out GPU_Command, GPUCommand_DrawRegionZoomed"
	 }



}




void set_tilemap_color(int rgba) {

	asm
	{
		"mov R0, {rgba}"
		"out GPU_MultiplyColor, R0"
	}

}

void set_tilemap_scale(float x, float y){
	selected_tilemap->source.scale[0]=x;
	selected_tilemap->source.scale[1]=y;
}
