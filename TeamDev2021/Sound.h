#pragma once
#include <map>
#include <string>

class Sound
{
protected:
	static std::map<std::string, int> soundMap;
	int sound;

public:
	Sound() {}
	Sound(const char* soundPass);
	~Sound();

	static void read(const char* soundPass);
	static void clear();

	void play(int playType, int topPositionFlag);
	void stop();
	void changeVolume(int volume);
};

