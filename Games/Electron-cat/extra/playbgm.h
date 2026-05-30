void play_background_noise(audio* remix1, audio* remix2) {

	if (wrap(timer, 85) == 1) {
		bool pick = rand() % 2;

		selected_audio = remix1;
		audio_set_volume(pick *bgm_volume);

		selected_audio = remix2;
		audio_set_volume(!pick * bgm_volume);
	}

	selected_audio = remix1;
	if (!audio_is_playing()) {

		int pick = rand() % 2;
		audio_set_volume(pick * bgm_volume);

		selected_audio = remix2;
		audio_set_volume(!pick * bgm_volume);

		selected_audio = remix1;
		play_audio();

		selected_audio = remix2;
		play_audio();

		return;
	}

	selected_audio = remix2;
	if (!audio_is_playing()) play_audio();

}
