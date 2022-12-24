#include <random>
#include <chrono>

static inline int getRandomNumber(int min, int max)
{
	static std::random_device rd;
	static std::mt19937 gen(rd());

	std::uniform_int_distribution<> distrib(min, max);

	return distrib(gen);
}

static inline std::chrono::time_point<std::chrono::steady_clock> getCurrentTime()
{
	return std::chrono::steady_clock::now();
}

static inline int64_t getElapsedTimeInMicroseconds(const std::chrono::time_point<std::chrono::steady_clock>& previousTime)
{
	return std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::steady_clock::now() - previousTime).count();
}