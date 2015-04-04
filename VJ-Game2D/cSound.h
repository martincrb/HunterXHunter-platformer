#pragma once
#pragma comment(lib, "fmod_vc.lib")
#include "fmod\fmod.hpp"
#include <string>
#include <vector>

#define MUSIC_CHANNEL 0
#define EFFECTS_CHANNEL 1

#define BG_MUSIC 0
#define EFFECT 1

#define N_SND 9 //number of sounds

#define TITLE_MUSIC 0
#define LEVEL_BG 1
#define LEVEL_WATER_BG 2
#define GON_JUMP 3
#define KILLUA_JUMP 4
#define BOO_HI 5
#define GET_COIN 6
#define BREAK_BLOCK 7
#define KICK 8
class cSound
{
public:
	cSound();
	~cSound();
	void LoadSound(int id,std::string file, int type);
	void Play(int id, int channel);
	void Stop(int id);
	void PauseChannel(int channel);
	void setVolume(int channel, float volume);
	void ResumeChannel(int channel);
	void UpdateSound();
	void init();
	void FreeAll();
private:
	float musicVolume;
	float effectsVolume;
	FMOD::System *system;
	FMOD::ChannelGroup *channelEffects;
	FMOD::ChannelGroup *channelMusic;
	FMOD::Sound* sounds[N_SND];
};

