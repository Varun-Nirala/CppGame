#include "sound.h"

#include "common/logger.h"

SoundEffect::~SoundEffect()
{
	clear();
}

SoundEffect::SoundEffect(const std::string& path)
{
	init(path);
}

void SoundEffect::init(const std::string &path)
{
	clear();
	m_pSoundChunk = Mix_LoadWAV(path.c_str());
	if (!m_pSoundChunk)
	{
		ns_Util::Logger::LOG_ERROR("Error initialising sound effect : ", path, '\n');
		assert(false);
		return;
	}
}

void SoundEffect::play(int loopCount)
{
	const int channel = Mix_PlayChannel(1, m_pSoundChunk, loopCount);
	if (channel < 0)
	{
		ns_Util::Logger::LOG_ERROR("Error playing sound effect!\n");
		assert(false);
		return;
	}
}

void SoundEffect::clear()
{
	if (m_pSoundChunk)
	{
		Mix_FreeChunk(m_pSoundChunk);
		m_pSoundChunk = nullptr;
	}
}

Music::~Music()
{
	clear();
}

Music::Music(const std::string& path)
{
	init(path);
}

void Music::init(const std::string& path)
{
	clear();
	m_pMusic = Mix_LoadMUS(path.c_str());
	if (!m_pMusic)
	{
		ns_Util::Logger::LOG_ERROR("Error initialising music : ", path, '\n');
		assert(false);
		return;
	}
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

void Music::clear()
{
	if (m_pMusic)
	{
		Mix_FreeMusic(m_pMusic);
		m_pMusic = nullptr;
	}
}