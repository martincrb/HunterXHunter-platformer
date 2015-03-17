#include "cData.h"

cData::cData(void) {

	//Start sound Buffers
	alGenBuffers(NUM_SND, soundBuffer);
	if (alGetError() != AL_NO_ERROR)
	{
		printf("alGenBuffers : %d", alGetError());
	}
	
}
cData::~cData(void){}

int cData::GetID(int img)
{
	return texture[img].GetID();
}

void cData::GetSize(int img, int *w, int *h)
{
	texture[img].GetSize(w,h);
}

bool cData::LoadImage(int img, const char *filename, int type)
{
	int res;

	res = texture[img].Load(filename,type);
	if(!res) return false;

	return true;
}

bool cData::LoadSound(ALbyte *filename) {
	ALenum     format;
	ALsizei    size;
	ALsizei    freq;
	ALboolean  loop;
	ALvoid*    data;

	alutLoadWAVFile(filename, &format, &data, &size, &freq, &loop);
	
	if ( alGetError() != AL_NO_ERROR)
	{
		printf("alutLoadWAVFile exciting_sound.wav : %d", alGetError());
		// Delete Buffers
		alDeleteBuffers(NUM_SND, soundBuffer);
		return false;
	}

	alBufferData(soundBuffer[0], format, data, size, freq);
	if (alGetError() != AL_NO_ERROR)
	{
		printf("alBufferData buffer 0 : %d", alGetError());
		// Delete buffers
		alDeleteBuffers(NUM_SND, soundBuffer);
		return false;
	}

	alutUnloadWAV(format, data, size, freq);
	if (alGetError() != AL_NO_ERROR)
	{
		printf("alutUnloadWAV : %d", alGetError());
		// Delete buffers
		alDeleteBuffers(NUM_SND, soundBuffer);
		return false;
	}
}

ALuint* cData::getSoundBuffer() {
	return soundBuffer;
}