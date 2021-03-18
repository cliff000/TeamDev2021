#include "Sound.h"
#include "Dxlib.h"

std::map<std::string, int> Sound::soundMap;

Sound::Sound(const char* soundPass) {
	read(soundPass);
	sound = soundMap[soundPass];
}

Sound::~Sound() {

}


void Sound::read(const char* soundPass) {
	if (soundMap.find(soundPass) == soundMap.end())
		soundMap[soundPass] = LoadSoundMem(soundPass);
}

void Sound::clear() {
	InitSoundMem();
	soundMap.clear();
}

void Sound::play(int playType, int topPositionFlag) {
	if (CheckSoundMem(sound) == 0) {
		PlaySoundMem(sound, playType, topPositionFlag);
	}
}

void Sound::stop() {
	StopSoundMem(sound);
}

void Sound::changeVolume(int volume) {
	ChangeVolumeSoundMem(volume, sound);
}