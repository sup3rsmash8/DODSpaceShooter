#pragma once

#include "GameBase.h"
#include "SDL_ttf.h"
#include "MulticastFunction.h"
#include <map>
#include "GameObject.h"
//class SpaceShooterGameObject;
//enum class GameObjectID;

enum class RoomID
{
	MAIN_GAME = 0,
	GAME_OVER,
};

class SpaceShooterGame : public GameBase
{
public:
	SpaceShooterGame();
	~SpaceShooterGame();

	typedef std::function<void(Uint32)> OnNewScoreSet;

private:
	static const std::string m_gameName;

	static MulticastFunction<Uint32> m_onNewScoreSet;

	static std::vector<Room*> m_gameRooms;

	Uint32 m_score = 0;

	TTF_Font* m_standardFont = nullptr;

protected:
	virtual Room* GameStartRoom() const override;

	virtual void InitializeGame() override;

	//virtual void ExecuteUpdate(float deltaTime) override;

	//virtual void ExecuteDrawUpdate(SDL_Renderer* renderer) override;

	

public:
	virtual std::string GetGameName() const { return m_gameName; }

	void SetScore(Uint32 newScore)
	{ 
		m_score = newScore; 
		m_onNewScoreSet.Call(std::tuple<Uint32>(newScore));
	}

	Uint32 GetScore() const { return m_score; }

	void Subscribe_OnNewScoreSet(OnNewScoreSet* newScore);
	void Unsubscribe_OnNewScoreSet(OnNewScoreSet* newScore);

	void SetStandardFont(TTF_Font* newFont);
	TTF_Font* GetStandardFont() const { return m_standardFont; }

	void GoToRoomByID(const RoomID roomID, bool rememberPreviousRoom);
};

