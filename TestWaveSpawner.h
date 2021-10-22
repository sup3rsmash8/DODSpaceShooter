#pragma once

#include "WaveSpawner.h"

class TestWaveSpawner : public WaveSpawner
{
public:
	TestWaveSpawner(const Vector2 position, float rotation = 0, bool enabled = true);

protected:
	virtual void ConstructWave(std::vector<Wave>& waveObjects) override;
};

