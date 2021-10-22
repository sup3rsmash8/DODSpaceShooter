#include "WaveSpawner.h"
#include "Statics.h"

WaveSpawner::WaveSpawner(const Vector2 position, float rotation, bool enabled)
{
}

void WaveSpawner::Update(float deltaTime)
{
    if (m_timer < 0)
    {
        int rnd = Random::RangeInt(0, 2);
        if (rnd == 0)
        {
            EnemySpaceShip* ship = m_enemyShipPool.GetPooledObject();
            if (ship)
            {
                rnd = Random::RangeInt(0, 4);

                MovePattern pattern;
                switch (rnd)
                {
                default:
                case 0: pattern = MovePattern::STRAIGHT;
                case 1: pattern = MovePattern::SINWAVE;
                case 2: pattern = MovePattern::MOVE_STOP_MOVE;
                }

                ship->SetPosition({ 820, Random::Range(128, 472) });
                ship->SetEnabled(true);
            }
        }
        else if (rnd == 1)
        {
            EnemyAsteroid* asteroid = m_asteroidPool.GetPooledObject();
            if (asteroid)
            {
                asteroid->SetPosition({ 820, Random::Range(128, 472) });
                asteroid->SetEnabled(true);
            }
        }

        m_timer = m_spawnTime;
    }
    else
    {
        m_timer -= deltaTime;
    }
}
