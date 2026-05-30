#ifndef EPSILON_AUDIO_H
#define EPSILON_AUDIO_H


struct audio{
	int sound;
	int channel;
};

audio * selected_audio = NULL;


audio* create_audio(int path, bool predecode) {
	audio* aud = malloc(sizeof(audio));
	aud->sound = path;
	aud->channel = -1;
	return aud;
}


void destroy_audio(){ // do nothing again
}



void play_audio() {
	selected_audio->channel = play_sound(selected_audio->sound);
}



void pause_audio() {
	select_channel(selected_audio->channel);
	pause_channel(selected_audio->channel);
}



void stop_audio() {
	select_channel(selected_audio->channel);
	stop_channel(selected_audio->channel);

}



void resume_audio() {
	select_channel(selected_audio->channel);
	play_channel(selected_audio->channel);
}



void set_speed(float speed) {
	select_channel(selected_audio->channel);
	set_channel_speed(speed);
}



void audio_set_volume(float volume) {
	select_channel(selected_audio->channel);
	set_channel_volume(volume);
}



void unload_audio() { // nothing at all
}



int audio_is_playing() {


	return (get_channel_state(selected_audio->channel) == channel_playing);

}

#endif
