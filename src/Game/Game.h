#pragma once

#include <ShSDK/ShSDK.h>

#include "Transition.h"
#include "Sound.h"

#include "GameState.h"
#include "GameStateMenuMain.h"
#include "GameStateMenuCredits.h"
#include "GameStateGame.h"

#define SPRITE_LIBRARY "ggj"

#define DISPLAY_WIDTH 1920
#define DISPLAY_HEIGHT 1080

#define MAX_GAME_STATES 3

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

private:
	Game(void);
public:

	enum EAction
	{
		e_action_none,
		e_action_push,
		e_action_pop
	};

	enum EState
	{
		MENU,
		CREDITS,
		GAME
	};

	struct SAction
	{
		EAction action;

		union
		{
			EState state;
		};
	};

	static Game & instance (void)
	{
		if (nullptr == instance_)
		{
			instance_ = new Game();
		}

		return(*instance_);
	}

	void        Push				(EState state);
	void        Pop					(void);
	void        PushWithTransition	(EState state);
	void        PopWithTransition	(void);

	inline GameState * get(EState state)
	{
		switch (state)
		{
			case MENU:
			{
				return(&m_stateMainMenu);
			}
			break;

			case CREDITS:
			{
				return(&m_stateCredits);
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

	Transition					m_transition;
	Sound						m_sound;

	GameStateMenuMain			m_stateMainMenu;
	GameStateMenuCredits		m_stateCredits;
	GameStateGame				m_stateGame;

	float						m_fRescaleRatio;

	SAction						m_registeredAction;

};
