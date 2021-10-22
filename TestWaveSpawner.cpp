#include "TestWaveSpawner.h"

TestWaveSpawner::TestWaveSpawner(const Vector2 position, float rotation, bool enabled) : WaveSpawner(position, rotation, enabled)
{

}

void TestWaveSpawner::ConstructWave(std::vector<Wave>& waveObjects)
{
	float xPos = GetPosition().x;

	std::vector<WaveObject> waveObjs1;
	waveObjs1.push_back(WaveObject(GameObjectID::ENEMY_SHIP, { xPos, Random::Range(0, 600) }, 0.2f));
	waveObjs1.push_back(WaveObject(GameObjectID::ENEMY_SHIP, { xPos, Random::Range(0, 600) }, 0.2f));
	waveObjs1.push_back(WaveObject(GameObjectID::ENEMY_SHIP, { xPos, Random::Range(0, 600) }, 0.2f));
	waveObjs1.push_back(WaveObject(GameObjectID::ENEMY_SHIP, { xPos, Random::Range(0, 600) }, 0.2f));

	Wave wave1 = Wave(waveObjs1);
	
	waveObjects.push_back(wave1);
}
