#include "Game.h"

Game * Game::instance_ = nullptr;


Game::Game(void)
: m_iCurrentState(-1)
{
    for (int i = 0; i < MAX_GAME_STATES; ++i)
    {
        m_aStates[i] = nullptr;
    }
}

/**
 * Called before engine initialization
 */
void Game::OnPreInitialize(void)
{
	// nothing here
}

/**
 * Called after engine initialization
 */
void Game::OnPostInitialize(void)
{
	instance();
	instance_->m_registeredAction.action = e_action_none;

    // Create the Camera
    ShCamera * pCamera = ShCamera::Create(GID(global), GID(camera), false);
    SH_ASSERT(shNULL != pCamera);

    ShCamera::SetPosition(pCamera, CShVector3(0.0f, 0.0f, 100.0f));
    ShCamera::SetTarget(pCamera, CShVector3(0.0f, 0.0f, 0.0f));

    ShCamera::SetUp(pCamera, CShVector3(0.0f, 1.0f, 0.0f));

    ShCamera::SetProjectionOrtho(pCamera);
    ShCamera::SetNearPlaneDistance(pCamera, 0.0f);
    ShCamera::SetFarPlaneDistance(pCamera, 200.0f);

    instance_->m_fRescaleRatio = ShDisplay::GetHeight() / (float)ShDisplay::GetWidth();
    ShCamera::SetViewport(pCamera, DISPLAY_WIDTH, DISPLAY_WIDTH * instance_->m_fRescaleRatio);

    ShCamera::SetCurrent2D(pCamera);

	// Initialize Sound
	instance_->m_sound.Initialize();

	// Initialize Transition
	instance_->m_transition.Initialize();

    // Initialize states
	instance_->m_stateMainMenu.Initialize();
	instance_->m_stateCredits.Initialize();
    instance_->m_stateGame.Initialize();

	instance_->Push(MENU);
}

/**
 * Called on each frame, before the engine update
 */
void Game::OnPreUpdate(float dt)
{
	// nothing here
}

/**
 * Called on each frame, after the engine update
 */
void Game::OnPostUpdate(float dt)
{
	if (Transition::e_state_idle != instance_->m_transition.GetState())
	{
		instance_->m_transition.Update(dt);

		if (Transition::e_state_waiting == instance_->m_transition.GetState())
		{
			switch(instance_->m_registeredAction.action)
			{
				case e_action_pop : 
				{
					instance_->Pop();					
				}
				break;

				case e_action_push : 
				{
					instance_->Push(instance_->m_registeredAction.state);					
				}
				break;

				default: 
					SH_ASSERT_ALWAYS(); //should never happened
				break;
			}

			instance_->m_transition.SetState(Transition::e_state_transition_out);
		}
	}


	instance_->m_aStates[instance_->m_iCurrentState]->Update();
	
}

/**
 * Called before the engine release
 */
void Game::OnPreRelease(void)
{
	// nothing here
}

/**
 * Called after the engine release
 */
void Game::OnPostRelease(void)
{
	// Release states
	instance_->m_stateGame.Release();
	instance_->m_stateMainMenu.Release();

	// Release Sound
	instance_->m_sound.Release();

	// Release Transition
	instance_->m_transition.Release();
}

/**
 * Called after a touch down
 */
void Game::OnTouchDown(int iTouch, float fPositionX, float fPositionY)
{
	instance_->m_aStates[instance_->m_iCurrentState]->OnTouchDown(iTouch, fPositionX, fPositionY);
}

/**
 * Called after a touch up
 */
void Game::OnTouchUp(int iTouch, float fPositionX, float fPositionY)
{
	instance_->m_aStates[instance_->m_iCurrentState]->OnTouchUp(iTouch, fPositionX, fPositionY);
}

/**
 * Called after a touch move
 */
void Game::OnTouchMove(int iTouch, float fPositionX, float fPositionY)
{
	instance_->m_aStates[instance_->m_iCurrentState]->OnTouchMove(iTouch, fPositionX, fPositionY);
}

//--------------------------------------------------------------------------------------------------
/// @todo comment
//--------------------------------------------------------------------------------------------------
void Game::PushWithTransition(EState state)
{
	if (m_transition.GetState() != Transition::e_state_idle)
		return;

	m_registeredAction.action = e_action_push;
	m_registeredAction.state = state;
	m_transition.SetState(Transition::e_state_transition_in);
}

//--------------------------------------------------------------------------------------------------
/// @todo comment
//--------------------------------------------------------------------------------------------------
void Game::PopWithTransition(void)
{
	if (m_transition.GetState() != Transition::e_state_idle)
		return;

	m_registeredAction.action = e_action_pop;
	m_transition.SetState(Transition::e_state_transition_in);
}

//--------------------------------------------------------------------------------------------------
/// @todo comment
//--------------------------------------------------------------------------------------------------
void Game::Push(EState state)
{
	SH_ASSERT(m_iCurrentState < MAX_GAME_STATES);

	if (m_iCurrentState >= 0)
	{
		m_aStates[m_iCurrentState]->Obscuring();
	}

	++m_iCurrentState;

	m_aStates[m_iCurrentState] = get(state);

	m_aStates[m_iCurrentState]->Entered();	
}

//--------------------------------------------------------------------------------------------------
/// @todo comment
//--------------------------------------------------------------------------------------------------
void Game::Pop(void)
{
	SH_ASSERT(m_iCurrentState >= 0);

	m_aStates[m_iCurrentState]->Exiting();

#if SH_DEBUG
	m_aStates[m_iCurrentState] = nullptr;
#endif

	--m_iCurrentState;

	if (m_iCurrentState >= 0)
	{
		m_aStates[m_iCurrentState]->Revealed();
	}	
}

