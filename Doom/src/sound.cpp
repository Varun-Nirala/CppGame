#include "sound.h"

#include "common/logger.h"

#include <algorithm>

SoundEffect::~SoundEffect()
{
	clear();
}

SoundEffect::SoundEffect(const std::string& path, int volume)
{
	init(path, volume);
}

void SoundEffect::init(const std::string &path, int volume)
{
	clear();
	m_pSoundChunk = Mix_LoadWAV(path.c_str());
	if (!m_pSoundChunk)
	{
		ns_Util::Logger::LOG_ERROR("Error initialising sound effect : ", path, '\n');
		assert(false);
		return;
	}
	setVolume(volume);
}

void SoundEffect::play(int loopCount)
{
	m_channel = Mix_PlayChannel(1, m_pSoundChunk, loopCount);
	if (m_channel < 0)
	{
		ns_Util::Logger::LOG_ERROR("Error playing sound effect!\n");
		assert(false);
		return;
	}
}

void SoundEffect::incrementVolume()
{
	m_volume = std::clamp(m_volume + 5, 0, MIX_MAX_VOLUME);
	Mix_Volume(m_channel, m_volume);
}

void SoundEffect::decrementVolume()
{
	m_volume = std::clamp(m_volume - 5, 0, MIX_MAX_VOLUME);
	Mix_Volume(m_channel, m_volume);
}

int SoundEffect::getCurrentVolume()
{
	m_volume = Mix_Volume(m_channel, -1);
	return m_volume;
}

void SoundEffect::setVolume(int val)
{
	m_volume = std::clamp(val, 0, MIX_MAX_VOLUME);
	Mix_Volume(m_channel, m_volume);
}

void SoundEffect::clear()
{
	if (m_pSoundChunk)
	{
		Mix_FreeChunk(m_pSoundChunk);
		m_pSoundChunk = nullptr;
		m_channel = 0;
	}
}

Music::~Music()
{
	clear();
}

Music::Music(const std::string& path, int volume)
{
	init(path, volume);
}

void Music::init(const std::string& path, int volume)
{
	clear();
	m_pMusic = Mix_LoadMUS(path.c_str());
	if (!m_pMusic)
	{
		ns_Util::Logger::LOG_ERROR("Error initialising music : ", path, '\n');
		assert(false);
		return;
	}
	setVolume(volume);
}

void Music::play(int loopCount)
{
	if (Mix_PlayingMusic() == 0)
	{
		if (Mix_PlayMusic(m_pMusic, loopCount) == -1)
		{
			ns_Util::Logger::LOG_ERROR("Error playing music!\n");
			assert(false);
			return;
		}
	}
}

void Music::pause()
{
	if (Mix_PlayingMusic())
	{
		Mix_PauseMusic();
	}
}

void Music::resume()
{
	if (Mix_PausedMusic())
	{
		Mix_ResumeMusic();
	}
}

void Music::stop()
{
	Mix_HaltMusic();
}

void Music::incrementVolume()
{
	m_volume = std::clamp(m_volume + 5, 0, MIX_MAX_VOLUME);
	Mix_VolumeMusic(m_volume);
}

void Music::decrementVolume()
{
	m_volume = std::clamp(m_volume - 5, 0, MIX_MAX_VOLUME);
	Mix_VolumeMusic(m_volume);
}

int Music::getCurrentVolume()
{
	m_volume = Mix_VolumeMusic(-1);
	return m_volume;
}

void Music::setVolume(int val)
{
	m_volume = std::clamp(val, 0, MIX_MAX_VOLUME);
	Mix_VolumeMusic(m_volume);
}

void Music::clear()
{
	if (m_pMusic)
	{
		Mix_FreeMusic(m_pMusic);
		m_pMusic = nullptr;
	}
}