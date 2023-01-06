#ifndef __SOUND_H__
#define __SOUND_H__

#include <SDL.h>
#include <SDL_mixer.h>

#include <string>

class Game;

class Sound
{
public:
	virtual ~Sound() { clear(); }
	Sound() = default;

	virtual void init(const std::string& path) = 0;
	virtual void play(int loopCount = 0) = 0;
	virtual void pause() {};
	virtual void resume() {};
	virtual void stop() {};

	virtual void clear() {};
};

class SoundEffect : public Sound
{
public:
	~SoundEffect();
	SoundEffect() = default;
	SoundEffect(const std::string& path);
	void init(const std::string& path) override;
	void play(int loopCount = 0) override;
	void clear() override;
private:
	Mix_Chunk* m_pSoundChunk{};
};

class Music : public Sound
{
public:
	~Music();
	Music() = default;
	Music(const std::string& path);
	void init(const std::string& path) override;
	void play(int loopCount = 0) override;
	void pause() override;
	void resume() override;
	void stop() override;
	void clear() override;

private:
	Mix_Music		*m_pMusic{};
};

#endif //!__SOUND_H__