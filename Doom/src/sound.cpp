#include "sound.h"

#include "common/logger.h"

SoundEffect::~SoundEffect()
{
	Mix_FreeChunk(m_pSoundChunk);
	m_pSoundChunk = nullptr;
}

void SoundEffect::init(const std::string &path)
{
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
	if (Mix_PlayChannel(-1, m_pSoundChunk, loopCount) < 0)
	{
		ns_Util::Logger::LOG_ERROR("Error playing sound effect!\n");
		assert(false);
		return;
	}
}

Music::~Music()
{
	Mix_FreeMusic(m_pMusic);
	m_pMusic = nullptr;
}

void Music::init(const std::string& path)
{
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