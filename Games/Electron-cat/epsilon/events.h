#ifndef EPSILON_EVENTS_H
#define EPSILON_EVENTS_H

bool running = true;



bool key_is_pressed(int* key) {
	if(strcmp(key, "left")  == 0 && gamepad_left()    > 0) return true;
	if(strcmp(key, "right") == 0 && gamepad_right()   > 0) return true;

	if(strcmp(key, "z")     == 0 && gamepad_button_a() > 0) return true;
	if(strcmp(key, "x")     == 0 && (gamepad_button_b() > 0 || gamepad_button_x() > 0)) return true;
	if(strcmp(key, "v")     == 0 && gamepad_button_r() > 0) return true;
	if(strcmp(key, "r")     == 0 && gamepad_button_start() > 0) return true;
	if(strcmp(key, "q")     == 0 && gamepad_button_l() > 0) return true;
	return false;
}



bool mouse_button_is_pressed(int * button) {
return false;
}



float mouse_x(void) {
	return 0;
}



float mouse_y(void) {
	return 0;
}



void check_close_button(){

	// be useless here: the function.

}


#endif
