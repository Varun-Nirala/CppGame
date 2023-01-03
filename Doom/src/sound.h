#ifndef __SOUND_H__
#define __SOUND_H__

#include <SDL.h>
#include <SDL_mixer.h>

#include <string>

class Game;

class Sound
{
public:
	virtual ~Sound() {};
	Sound(Game *pGame) : m_pGame(pGame) {}
	virtual void init(const std::string& path) = 0;
	virtual void play(int loopCount = 0) = 0;
	virtual void pause() {};
	virtual void resume() {};
	virtual void stop() {};

	const Game* game() const { return m_pGame; }
	Game* game() { return m_pGame; }

protected:
	Game			*m_pGame{};
};

class SoundEffect : public Sound
{
public:
	~SoundEffect();
	SoundEffect(Game* pGame) : Sound(pGame) {}
	void init(const std::string& path) override;
	void play(int loopCount = 0) override;

private:
	Mix_Chunk* m_pSoundChunk{};
};

class Music : public Sound
{
public:
	~Music();
	Music(Game* pGame) : Sound(pGame) {}
	void init(const std::string& path) override;
	void play(int loopCount = 0) override;
	void pause() override;
	void resume() override;
	void stop() override;

private:
	Mix_Music		*m_pMusic{};
};

#endif //!__SOUND_H__