#pragma once
#include <irrKlang.h>
#include <string>
#include <unordered_map>
class SoundEngine
{
public:
	SoundEngine();

	enum class Sounds
	{
		None = 0,
		Applause = 1,
		Descent = 2,
		Explosion = 3,
		Respawn = 4,
		ShieldCharge = 5,
		Shoot = 6,
		SpecialShoot = 7,
		Music = 8,
	};

	static SoundEngine* _instance;
	static irrklang::ISound* Play2DAudio(const char* filePath, bool loop = false);
	static irrklang::ISound* Play2DAudio(Sounds sound, bool loop = false);
	static void SetMainVolume(float volume);

private:
	irrklang::ISoundEngine* _irrklangEngine;
	static std::unordered_map<Sounds, const char*> _audioPaths;
	void ConfigureAudioPaths() const;
};