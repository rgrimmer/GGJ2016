#include "Game.h"

#include "../Plugins/Platformer/CShPluginPlatformer.h"

extern CShPluginPlatformer plugin_platformer;

//--------------------------------------------------------------------------------------------------
/// @todo comment
//--------------------------------------------------------------------------------------------------
/*explicit*/ GameStateGame::GameStateGame(void)
: GameState()
, m_eState(e_state_intro)
{

}

//--------------------------------------------------------------------------------------------------
/// @todo comment
//--------------------------------------------------------------------------------------------------
/*virtual*/ GameStateGame::~GameStateGame(void)
{

}

//--------------------------------------------------------------------------------------------------
/// @todo comment
//--------------------------------------------------------------------------------------------------
void GameStateGame::Initialize(void)
{

}

//--------------------------------------------------------------------------------------------------
/// @todo comment
//--------------------------------------------------------------------------------------------------
void GameStateGame::Release(void)
{

}

//--------------------------------------------------------------------------------------------------
/// @todo comment
//--------------------------------------------------------------------------------------------------
void GameStateGame::Obscuring(void)
{
	DeActivate();
}

//--------------------------------------------------------------------------------------------------
/// @todo comment
//--------------------------------------------------------------------------------------------------
void GameStateGame::Revealed(void)
{
	Activate();
}

//--------------------------------------------------------------------------------------------------
/// @todo comment
//--------------------------------------------------------------------------------------------------
void GameStateGame::Exiting(void)
{
	DeActivate();
}

//--------------------------------------------------------------------------------------------------
/// @todo comment
//--------------------------------------------------------------------------------------------------
void GameStateGame::Entered(void)
{
	Activate();
}

//--------------------------------------------------------------------------------------------------
/// @todo comment
//--------------------------------------------------------------------------------------------------
void GameStateGame::Activate(void)
{
	Game::instance().PlaySound(Sound::e_sound_music_game);
	ShLevel::Load(CShIdentifier("level_game"));	

	/*m_pEntitySmoke = ShEntity2::Find(CShIdentifier("level_game"), CShIdentifier("sprite_ggj_smoke_001"));
	ShEntity2::SetShow(m_pEntitySmoke, false);*/

	SetState(e_state_play);
}

//--------------------------------------------------------------------------------------------------
/// @todo comment
//--------------------------------------------------------------------------------------------------
void GameStateGame::DeActivate(void)
{
	ShLevel::Release();
}


//--------------------------------------------------------------------------------------------------
/// @todo comment
//--------------------------------------------------------------------------------------------------
void GameStateGame::Update(float dt)
{
	m_fStateTime += dt;

	switch (m_eState)
	{
		case e_state_intro:
		{
			if (m_fStateTime > 1.0f)
			{
				SetState(e_state_smoke);
			}
		}
		break;

		case e_state_smoke:
		{
			if (m_fStateTime < 3.0f)
			{
				ShObject::SetAlpha(m_pEntitySmoke, 1.0f - (m_fStateTime / 3.0f));
			}
			else
			{
				SetState(e_state_play);
			}
		}
		break;

		case e_state_play:
		{
			if (plugin_platformer.RestartGame())
			{
				plugin_platformer.m_bRestartGame = false;
				plugin_platformer.SetPaused(true);
				Game::instance().ChangeWithTransition(Game::GAME);
			}
		}
		break;
	}
}

//--------------------------------------------------------------------------------------------------
/// @todo comment
//--------------------------------------------------------------------------------------------------
/*virtual*/ void GameStateGame::OnTouchDown(int iTouch, float positionX, float positionY)
{

}

//--------------------------------------------------------------------------------------------------
/// @todo comment
//--------------------------------------------------------------------------------------------------
/*virtual*/ void GameStateGame::OnTouchUp(int iTouch, float positionX, float positionY)
{

}

//--------------------------------------------------------------------------------------------------
/// @todo comment
//--------------------------------------------------------------------------------------------------
/*virtual*/ void GameStateGame::OnTouchMove(int iTouch, float positionX, float positionY)
{

}

//--------------------------------------------------------------------------------------------------
/// @todo comment
//--------------------------------------------------------------------------------------------------
void GameStateGame::SetState(EState state)
{
	m_eState = state;

	if (state == e_state_smoke)
	{
		ShEntity2::SetShow(m_pEntitySmoke, true);
		ShObject::SetAlpha(m_pEntitySmoke, 0.0f);
	}

	plugin_platformer.SetPaused(state != e_state_play);

	m_fStateTime = 0.0f;
}
