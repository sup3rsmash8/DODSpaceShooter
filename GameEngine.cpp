#include "GameEngine.h"

#include "SDL_ttf.h"

#include <iostream>

#include <windows.h>
#include <tchar.h>
#include <strsafe.h>
#include <thread>

#include "GameBase.h"
#include "Statics.h"
#include "Input.h"
#include "Timer.h"
#include "Random.h"
#include "Collider.h"
#include "ParticleSystem.h"
#include "Particles.h"

//bool GameEngine::m_applicationRunning = false;
//float GameEngine::m_time = 0;
//float GameEngine::m_deltaTime = 0;
//float GameEngine::m_accumulatedTime = 0;
//float GameEngine::m_accumulatedDrawTime = 0;
//GameBase* GameEngine::m_gameBase = nullptr;
//
//SDL_Renderer* GameEngine::m_renderer = nullptr;
//
//SDL_Window* GameEngine::m_window = nullptr;

GameEngine::GameEngine(GameBase* gameBase)
{
    m_gameBase = gameBase;

    m_input = new Input();
    //m_updateEvent 
}

GameEngine::~GameEngine()
{
    delete m_input;

    Uninitialize();
    SDL_Quit();
}

void GameEngine::Initialize()
{
    Random::SRand();
    if (!Statics::m_gameEngine)
        Statics::m_gameEngine = this;
    
    if (m_gameBase)
    {
        SDL_Init(SDL_INIT_EVERYTHING);
        m_applicationRunning = true;

        TTF_Init();

        //m_game = new AsteroidsGame(m_screenResolution);

        m_window = SDL_CreateWindow(m_gameBase->GetGameName().c_str(), SDL_WINDOWPOS_UNDEFINED,
            SDL_WINDOWPOS_UNDEFINED, static_cast<int>(m_gameBase->GetScreenResolution().x), static_cast<int>(m_gameBase->GetScreenResolution().y), SDL_WINDOW_SHOWN);

        m_renderer = SDL_CreateRenderer(m_window, -1, 0);
        
        m_gameBase->InitializeGame();
        m_gameBase->LateInitializeGame();
    }
    else
    {
        std::cout << "WARNING: Null game. This game will not be initialized." << std::endl;
    }
}

void GameEngine::Uninitialize()
{
    m_gameBase->UninitializeGame();

    delete m_gameBase;
    
    if (m_renderer)
        SDL_DestroyRenderer(m_renderer);

    if (m_window)
        SDL_DestroyWindow(m_window);

    std::cout << "Unin" << std::endl;

    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}

void GameEngine::GameLoop()
{
    m_previousTicks = SDL_GetPerformanceCounter();

    while (m_applicationRunning)
    {
        // Delta time, compare the passed ticks this iteration
        // and divide it by the tick rate per second.
        Uint64 currentTicks = SDL_GetPerformanceCounter();
        Uint64 delta = currentTicks - m_previousTicks;
        m_previousTicks = currentTicks;
        static const Uint64 ticksPerSec = SDL_GetPerformanceFrequency();
        m_deltaTime = delta / static_cast<float>(ticksPerSec);

        m_time += m_deltaTime;

        m_accumulatedTime += m_deltaTime;
        m_accumulatedDrawTime += m_deltaTime;

        float timeStep = m_gameBase->GetTimeStep();

        // If we've accumulated more than the game's desired time step,
        // update the game logic.
        if (std::isgreater(m_accumulatedTime, timeStep))
        {
            std::map<Collider*, Collider*> collisions = std::map<Collider*, Collider*>();

            // Start the particle thread
            m_particleThread = SDL_CreateThread(ParticleSystem::Thread_ParticleUpdate, "Thread_ParticleUpdate", &m_deltaTime);

            // Start collision thread
            m_collisionThread = SDL_CreateThread(Collider::Thread_CollisionUpdate, "Thread_CollisionProcedure", &collisions);

            // Physics/Logic update
            UpdateProcess(timeStep, m_accumulatedTime, m_deltaTime);

            // Await our threads before proceeding
            if (m_collisionThread)
            {
                int threadReturnValue = 0;
                SDL_WaitThread(m_collisionThread, &threadReturnValue);
                CollisionCheck(collisions);
            }

            if (m_particleThread)
            {
                int threadReturnValue = 0;
                SDL_WaitThread(m_particleThread, &threadReturnValue);
            }

            PostUpdateProcess();
        }

        while (SDL_PollEvent(&m_evt))
        {
            if (m_evt.type == SDL_QUIT)
                m_applicationRunning = false;

            if (m_input)
            {
                m_input->RegisterInput(m_evt);
            }
        }

        timeStep = m_gameBase->GetDrawTimeStep();

        // Graphics update
        UpdateDrawProcess(timeStep, m_accumulatedDrawTime);

        SDL_RenderPresent(m_renderer);

        //SDL_DetachThread(particleThread);

        if (!m_applicationRunning)
            break;
    }
}

void GameEngine::UpdateProcess(float& timeStep, float& accumulatedTime, float& deltaTime)
{
    accumulatedTime -= timeStep;

    static Timer physTimer = Timer();
    physTimer.Tick();

    deltaTime = physTimer.GetElapsedSeconds();

    Update(deltaTime);

    if (m_input)
    {
        m_input->UpdateHeldReleased();
    }
}

void GameEngine::PostUpdateProcess()
{
    if (m_gameBase)
        m_gameBase->PostExecuteUpdate();
}

void GameEngine::UpdateDrawProcess(float& timeStep, float& accumulatedTime)
{
    if (std::isgreater(accumulatedTime, timeStep))
    {
        accumulatedTime -= timeStep;

        //static Timer drawTimer = Timer();
        //drawTimer.Tick();

        SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 255);
        SDL_RenderClear(m_renderer);

        Particles::RenderAll(m_renderer);

        DrawUpdate(m_renderer);
    }
    // Graphics update
    //while (accumulatedTime >= timeStep)
    //{
        // Clear screen


        
        //accumulatedTime -= timeStep;
    //}
}

void GameEngine::CollisionCheck(std::map<Collider*, Collider*>& collisions)
{
    for (auto& key : collisions)
    {
        if (key.first && key.second)
        {
            key.first->OnCollision(key.second->m_owner);
            key.second->OnCollision(key.first->m_owner);
        }
    }
}

bool GameEngine::Input_GetKey(SDL_Keycode keyCode) const
{    
    return m_input && m_input->GetKey(keyCode);
}

bool GameEngine::Input_GetKeyDown(SDL_Keycode keyCode) const
{
    return m_input && m_input->GetKeyDown(keyCode);
}

bool GameEngine::Input_GetKeyUp(SDL_Keycode keyCode) const
{
    return m_input && m_input->GetKeyUp(keyCode);
}

void GameEngine::Start()
{
    m_gameBase->OnGameStart();
}

void GameEngine::Update(float deltaTime)
{
    if (m_gameBase)
    {
        m_gameBase->ExecuteUpdate(deltaTime);
    }
}

void GameEngine::DrawUpdate(SDL_Renderer* renderer)
{
    if (m_gameBase)
    {
        m_gameBase->ExecuteDrawUpdate(renderer);
    }
}
