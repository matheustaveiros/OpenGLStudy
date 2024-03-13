#include "SoundEngine.h"

SoundEngine* SoundEngine::_instance = nullptr;
std::unordered_map<SoundEngine::Sounds, const char*> SoundEngine::_audioPaths;

SoundEngine::SoundEngine()
{
	_instance = this;

	_irrklangEngine = irrklang::createIrrKlangDevice();
	SetMainVolume(0.1f);
	ConfigureAudioPaths();
}

irrklang::ISound* SoundEngine::Play2DAudio(const char* filePath, bool loop)
{
	return _instance->_irrklangEngine->play2D(filePath, loop);
}

irrklang::ISound* SoundEngine::Play2DAudio(Sounds sound, bool loop)
{
	if (_audioPaths.contains(sound))
	{
		return _instance->_irrklangEngine->play2D(_audioPaths[sound], loop);
	}

	return nullptr;
}

void SoundEngine::SetMainVolume(float volume)
{
	_instance->_irrklangEngine->setSoundVolume(volume);
}

void SoundEngine::ConfigureAudioPaths() const
{
	using enum Sounds;
	_audioPaths.emplace(Applause, "res/sounds/applause.mp3");
	_audioPaths.emplace(Descent, "res/sounds/descent.mp3");
	_audioPaths.emplace(Explosion, "res/sounds/explosion.mp3");
	_audioPaths.emplace(ShieldCharge, "res/sounds/shield_charge.mp3");
	_audioPaths.emplace(Shoot, "res/sounds/shoot.mp3");
	_audioPaths.emplace(SpecialShoot, "res/sounds/shoot_3d.mp3");
	_audioPaths.emplace(Music, "res/sounds/music.mp3");
}
