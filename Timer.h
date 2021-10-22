#pragma once

#include "SDL.h"

struct Timer
{
private:
	Uint64 m_previousTick;
	float m_elaspedSeconds;

public:
	void Tick()
	{
		const Uint64 currentTick = SDL_GetPerformanceCounter();

		const Uint64 delta = currentTick - m_previousTick;

		m_previousTick = currentTick;

		static const Uint64 ticksPerSec = SDL_GetPerformanceFrequency();

		m_elaspedSeconds = delta / static_cast<float>(ticksPerSec);
	}

	float GetElapsedSeconds() const { return m_elaspedSeconds; }
};