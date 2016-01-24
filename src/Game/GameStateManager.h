#pragma once

#include "GameState.h"

#define MAX_GAME_STATES 2

class GameStateManager
{

public:

    enum EState
    {
        MENU,
        GAME
    };

    static GameStateManager & instance (void)
    {
        if (nullptr == instance_)
        {
            instance_ = new GameStateManager();
        }

        return(*instance_);
    }
	
	GameStateManager(void);
	~GameStateManager(void);

    void        initialize			(void);
    void        release				(void);
    void        update				(float dt);

    void        touchBegin			(int iTouch, const CShVector2 & pos);
    void        touchEnd			(int iTouch, const CShVector2 & pos);
    void        touchMove			(int iTouch, const CShVector2 & pos);

    void        push				(EState state);
    void        pop					(void);

    // Get State

    GameState * get(EState state)
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
                return((GameState*)0); // this should never happen
            }
        }

    }

private:

    static GameStateManager *	instance_;
    GameState *					m_aStates [MAX_GAME_STATES];
    int							m_iCurrentState;

    GameStateMenuMain			m_stateMainMenu;
    GameStateGame				m_stateGame;
};