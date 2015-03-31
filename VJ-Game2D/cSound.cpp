#include "cSound.h"


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
}
void cSound::LoadSound(int id, std::string file, int type) {
	//sounds.push_back(sound1);
	switch (type) {
	case (BG_MUSIC) :
		system->createStream(file.c_str(), FMOD_2D | FMOD_LOOP_NORMAL, 0, &sounds[id]);
		break;
	case (EFFECT):
		system->createSound(file.c_str(), FMOD_2D, 0, &sounds[id]);
		break;

	}
}
void cSound::Play(int id, int channel) {

	if (channel == MUSIC_CHANNEL) {
		system->playSound(sounds[id], channelMusic, false, 0);
	}
	else if (channel == EFFECTS_CHANNEL) {
		system->playSound(sounds[id], channelEffects, false, 0);
	}
}
void cSound::Stop(int id) {
	sounds[id]->release();
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
	system->update();
}

void cSound::FreeAll() {
	for (int i = 0; i < N_SND; ++i) {
		sounds[i]->release();
	}
	system->close();
	system->release();
}