#include "cSound.h"
#include "Globals.h"

cSound::cSound()
{
	
	
	
}


cSound::~cSound()
{
}

void cSound::init() {
	//init FMOD
	FMOD::System_Create(&system);
	system->init(32, FMOD_INIT_NORMAL, 0);
	system->createChannelGroup(NULL, &channelMusic);
	system->createChannelGroup(NULL, &channelEffects);
	effectsVolume = 1.0;
	musicVolume = 1.0;
	for (int i = 0; i < N_SND; ++i) {
		already_released[i] = true;
	}
}
void cSound::LoadSound(int id, std::string file, int type) {
	//sounds.push_back(sound1);
	already_released[id] = false;
	switch (type) {
	case (BG_MUSIC) :
		system->createStream(file.c_str(), FMOD_2D | FMOD_LOOP_NORMAL, 0, &sounds[id]);
		break;
	case (EFFECT):
		system->createSound(file.c_str(), FMOD_2D, 0, &sounds[id]);
		break;

	}
}
void cSound::setVolume(int channel, float volume) {
	if (channel == MUSIC_CHANNEL) {
		musicVolume = volume;
	}
	else if (channel == EFFECTS_CHANNEL) {
		effectsVolume = volume;
	}
}
void cSound::Play(int id, int channel) {

	if (channel == MUSIC_CHANNEL) {
		channelMusic->setVolume(musicVolume);
		system->playSound(sounds[id], channelMusic, false, 0);
		
		//channelMusic->setPaused(false);
	}
	else if (channel == EFFECTS_CHANNEL) {
		channelEffects->setVolume(effectsVolume);
		system->playSound(sounds[id], channelEffects, false, 0);
		
		//channelEffects->setPaused(false);
	}
}
void cSound::Stop(int id) {
	//channelMusic->release();
	//channelEffects->release();
	if (!already_released[id]) {
		sounds[id]->release();
		already_released[id] = true;
	}
	
}

void cSound::PauseChannel(int channel) {
	if (channel == MUSIC_CHANNEL) {
		channelMusic->setPaused(true);
	}
	else if (channel == EFFECTS_CHANNEL) {
		channelEffects->setPaused(true);
	}
}
void cSound::ResumeChannel(int channel) {
	if (channel == MUSIC_CHANNEL) {
		channelMusic->setPaused(false);
	}
	else if (channel == EFFECTS_CHANNEL) {
		channelEffects->setPaused(false);
	}
}

void cSound::UpdateSound() {
	channelEffects->setVolume(effectsVolume);
	channelMusic->setVolume(musicVolume);
	system->update();
}

void cSound::FreeAll() {
	for (int i = 0; i < N_SND; ++i) {
		if (!already_released[i] && sounds[i] != NULL)
			sounds[i]->release();
	}
	system->close();
	system->release();
}