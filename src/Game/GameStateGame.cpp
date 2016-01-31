#include "Game.h"

#include "../Plugins/Platformer/CShPluginPlatformer.h"

#define SMOKE_PARTICLES_COUNT 60

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

	CShTimer::GetInstance()->Pause();
	ShLevel::Load(CShIdentifier("level_game"));
	CShTimer::GetInstance()->Resume();

	m_pEntityPlayerDead = ShEntity2::Find(CShIdentifier("level_game"), CShIdentifier("sprite_ggj_player_dead_001"));
	ShEntity2::SetShow(m_pEntityPlayerDead, true);

	const CShVector3 & pos = ShEntity2::GetPosition(m_pEntityPlayerDead);

	m_aEntitySmoke.SetCount(SMOKE_PARTICLES_COUNT);

	CShRandomValue rv;

	for (int i = 0; i < SMOKE_PARTICLES_COUNT; ++i)
	{
		float scale = rv.GetNextFloat(0.5f, 1.2f);
		float distance = rv.GetNextFloat(0.0f, 450.0f);
		float angle = rv.GetNextFloat(0.0f, SHC_2PI);

		float offset_x = cos(angle) * distance;
		float offset_y = sin(angle) * distance;

		m_aEntitySmoke[i].startTime = rv.GetNextFloat(0.0f, 0.5f);
		m_aEntitySmoke[i].duration = rv.GetNextFloat(1.1f, 3.5f);

		m_aEntitySmoke[i].pEntity = ShEntity2::Create(CShIdentifier("level_game"), GID(NULL), GID(layer_default), CShIdentifier("ggj"), CShIdentifier("smoke"), pos + CShVector3(offset_x, offset_y, 1.0f), CShEulerAngles(0.0f, 0.0f, 0.0f), CShVector3(scale, scale, 1.0f));

		ShEntity2::SetShow(m_aEntitySmoke[i].pEntity, false);
	}

	SetState(e_state_intro);
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
			if (m_fStateTime > 5.0f)
			{
				SetState(e_state_smoke);
			}
		}
		break;

		case e_state_smoke:
		{
			if (m_fStateTime < 4.0f)
			{
				if (m_fStateTime > 1.0f)
				{
					ShEntity2::SetAlpha(m_pEntityPlayerDead, 1.0f - (m_fStateTime / 3.0f));
				}

				for (int i = 0; i < SMOKE_PARTICLES_COUNT; ++i)
				{
					float completion = shMax(0.0f, -(m_aEntitySmoke[i].startTime-m_fStateTime)) / m_aEntitySmoke[i].duration;

					if (completion < 0.2f)
					{
						ShObject::SetAlpha(m_aEntitySmoke[i].pEntity, completion*5.0f);
					}
					else
					{
						ShObject::SetAlpha(m_aEntitySmoke[i].pEntity, 1.0f - completion);
					}
				}
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
		for (int i = 0; i < SMOKE_PARTICLES_COUNT; ++i)
		{
			ShEntity2::SetShow(m_aEntitySmoke[i].pEntity, true);
			ShObject::SetAlpha(m_aEntitySmoke[i].pEntity, 0.0f);
		}
	}
	else if (state == e_state_play)
	{
		ShEntity2::SetAlpha(m_pEntityPlayerDead, 1.0f);
		ShEntity2::SetShow(m_pEntityPlayerDead, false);
	}

	plugin_platformer.SetPaused(state != e_state_play);

	m_fStateTime = 0.0f;
}
