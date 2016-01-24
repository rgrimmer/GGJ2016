#pragma once

#include <ShSDK/ShSDK.h>

#include "GameState.h"
#include "GameStateMenuMain.h"
#include "GameStateGame.h"

#define MAX_GAME_STATES 2

class Game
{
public:

	static void OnPreInitialize		(void);
	static void OnPostInitialize	(void);
	static void OnPreUpdate			(float dt);
	static void OnPostUpdate		(float dt);
	static void OnPreRelease		(void);
	static void OnPostRelease		(void);

	static void OnTouchDown			(int iTouch, float fPositionX, float fPositionY);
	static void OnTouchUp			(int iTouch, float fPositionX, float fPositionY);
	static void OnTouchMove			(int iTouch, float fPositionX, float fPositionY);

public:

	enum EState
	{
		MENU,
		GAME
	};

	static Game & instance (void)
	{
		if (nullptr == instance_)
		{
			instance_ = new Game();
		}

		return(*instance_);
	}

	void        push				(EState state);
	void        pop					(void);

	inline GameState * get(EState state)
	{
		switch (state)
		{
			case MENU:
			{
				return(&m_stateMainMenu);
			}
			break;

			case GAME:
			{
				return(&m_stateGame);
			}
			break;

			default:
			{
				return((GameState*)nullptr); // this should never happen
			}
		}
	}

private:

	static Game *				instance_;
	GameState *					m_aStates [MAX_GAME_STATES];
	int							m_iCurrentState;

	GameStateMenuMain			m_stateMainMenu;
	GameStateGame				m_stateGame;

};
