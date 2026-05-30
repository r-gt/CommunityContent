
bool changed_level=0;


void goto_next_level(texture * tex, audio * win){

    selected_audio = win;

    if(nltimer < -1+0.016666666 ){
        play_sound(win_wav);

    }


    set_render_color(nloverlay_color);


    draw_rect(
        320-ease((nltimer+0.5)*2, QUINT, QUINT)*320 + ease((nltimer-2.5)*2, QUINT, QUINT)*320,
        180-ease((nltimer+0.5)*2, QUINT, QUINT)*180 +ease((nltimer-2.5)*2, QUINT, QUINT)*180 ,
        ease((nltimer+0.5)*2, QUINT, QUINT)*640 - ease((nltimer-2.5)*2, QUINT, QUINT)*640 ,
        ease((nltimer+0.5)*2, QUINT, QUINT)*360 - ease((nltimer-2.5)*2, QUINT, QUINT)*360
    );


    selected_texture = tex;

    if(nltimer>0.5 && nltimer<2.2){

    set_mask(0,13,16,34);

    draw_texture(260+ease(((nltimer-1)*1.5), CUBIC, CUBIC)*120,260+ease(((nltimer-0.4)*2), CUBIC, NONE)*-90+ease(((nltimer-1.6)*2), CUBIC, NONE)*90);
    }



    set_mask(0,0,16,12);
    draw_texture(260+ease(((nltimer-1)*1.5), CUBIC, CUBIC)*120,-20+ease(((nltimer+0)*2), CUBIC, CUBIC)*165+ease(((nltimer-1.5)*2), CUBIC, NONE)*-165);

    set_mask(16,0,59,48);

    draw_texture(260, 360+ease(((nltimer)*2), NONE, CUBIC)*-139+ease(((nltimer-2)*2), CUBIC, NONE)*139);
    draw_texture(380, 360+ease(((nltimer)*2), NONE, CUBIC)*-139+ease(((nltimer-2)*2), CUBIC, NONE)*139);


    nltimer+=0.016666666;


    if(!changed_level && nltimer>2){
        changed_level=1;
        level++;
        pa=0;
        pax=0;

        for (int y = 0; y < 23; y++)
            for (int x = 0; x < 40; x++)
                map_buffer[y][x] = maps[level][y][x];
    }

    if(nltimer>3){
        changed_level=0;
        nltimer=-1;
        player_waiting=0;

    }


}
