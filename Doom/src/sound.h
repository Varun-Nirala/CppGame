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

	virtual void init(const std::string& path, int volume) = 0;
	virtual void play(int loopCount = 0) = 0;
	virtual void pause() {};
	virtual void resume() {};
	virtual void stop() {};

	virtual void incrementVolume() {}
	virtual void decrementVolume() {}

	virtual int getCurrentVolume() { return 0; }

	virtual void setVolume(int /*val*/) {}

	virtual void clear() {};

protected:
	int		m_channel{};
	int		m_volume{};
};

class SoundEffect : public Sound
{
public:
	static SoundEffect* createSoundEffect(const std::string& path, int volume)
	{
		return new SoundEffect(path, volume);
	}

	~SoundEffect();
	SoundEffect() = default;
	SoundEffect(const std::string& path, int volume);
	void init(const std::string& path, int volume) override;
	void play(int loopCount = 0) override;

	void incrementVolume() override;
	void decrementVolume() override;
	int getCurrentVolume() override;
	void setVolume(int val) override;

	void clear() override;
private:
	Mix_Chunk* m_pSoundChunk{};
};

class Music : public Sound
{
public:
	static Music* createMusic(const std::string& path, int volume)
	{
		return new Music(path, volume);
	}

	~Music();
	Music() = default;
	Music(const std::string& path, int volume);
	void init(const std::string& path, int volume) override;
	void play(int loopCount = 0) override;
	void pause() override;
	void resume() override;
	void stop() override;

	void incrementVolume() override;
	void decrementVolume() override;
	int getCurrentVolume() override;
	void setVolume(int val) override;

	void clear() override;

private:
	Mix_Music		*m_pMusic{};
};

#endif //!__SOUND_H__