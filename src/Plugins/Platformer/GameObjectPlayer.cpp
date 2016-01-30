#include "CShPluginPlatformer.h"

#define PLAYER_SPEED 3.0f

#define ANIMATION_IDLE_COUNT 24
#define ANIMATION_RUN_COUNT 12

//--------------------------------------------------------------------------------------------------
/// @todo comment
//--------------------------------------------------------------------------------------------------
/*explicit*/ GameObjectPlayer::GameObjectPlayer(b2Body * body, ShEntity2 * pEntity)
: GameObject(body)
, m_eJumpState(e_jump_state_none)
, m_pEntity(pEntity)
, m_iCurrentAnimation(0)
, m_fAnimationTime(0.0f)
{
	//
	// Action Move Left
	{
#if SH_PC
		ShInput * pInput = ShInput::CreateInputPressed(ShInput::e_input_device_keyboard, ShInput::e_input_device_control_pc_key_left, 0.1f);
		m_aActions[e_action_move_left].m_aKeyInputs.Add(pInput);
#elif SH_LINUX
		ShInput * pInput = ShInput::CreateInputPressed(ShInput::e_input_device_keyboard, ShInput::e_input_device_control_linux_key_left, 0.1f);
		m_aActions[e_action_move_left].m_aKeyInputs.Add(pInput);
#endif // SH_PC
	}

	{
#if SH_PC
		ShInput * pInput = ShInput::CreateInputPressed(ShInput::e_input_device_pad_first, ShInput::e_input_device_control_pc_pad_left, 0.1f);
		m_aActions[e_action_move_left].m_aKeyInputs.Add(pInput);
#elif SH_LINUX
		ShInput * pInput = ShInput::CreateInputPressed(ShInput::e_input_device_pad_first, ShInput::e_input_device_control_linux_pad_left, 0.1f);
		m_aActions[e_action_move_left].m_aKeyInputs.Add(pInput);
#endif // SH_PC
	}

	{
#if SH_PC
		ShInput * pInput = ShInput::CreateInputPressed(ShInput::e_input_device_pad_first, ShInput::e_input_device_control_pc_pad_left_thumb_x, -0.1f);
		m_aActions[e_action_move_left].m_aLeftJoystickInputs.Add(pInput);
#elif SH_LINUX
		ShInput * pInput = ShInput::CreateInputPressed(ShInput::e_input_device_pad_first, ShInput::e_input_device_control_linux_pad_left_thumb_x, -0.1f);
		m_aActions[e_action_move_left].m_aLeftJoystickInputs.Add(pInput);
#endif // SH_PC
	}

	//
	// Action Move Right
	{
#if SH_PC
		ShInput * pInput = ShInput::CreateInputPressed(ShInput::e_input_device_keyboard, ShInput::e_input_device_control_pc_key_right, 0.1f);
		m_aActions[e_action_move_right].m_aKeyInputs.Add(pInput);
#elif SH_LINUX
		ShInput * pInput = ShInput::CreateInputPressed(ShInput::e_input_device_keyboard, ShInput::e_input_device_control_linux_key_right, 0.1f);
		m_aActions[e_action_move_right].m_aKeyInputs.Add(pInput);
#endif // SH_PC
	}

	{
#if SH_PC
		ShInput * pInput = ShInput::CreateInputPressed(ShInput::e_input_device_pad_first, ShInput::e_input_device_control_pc_pad_right, 0.1f);
		m_aActions[e_action_move_right].m_aKeyInputs.Add(pInput);
#elif SH_LINUX
		ShInput * pInput = ShInput::CreateInputPressed(ShInput::e_input_device_pad_first, ShInput::e_input_device_control_linux_pad_right, 0.1f);
		m_aActions[e_action_move_right].m_aKeyInputs.Add(pInput);
#endif // SH_PC
	}

	{
#if SH_PC
		ShInput * pInput = ShInput::CreateInputPressed(ShInput::e_input_device_pad_first, ShInput::e_input_device_control_pc_pad_left_thumb_x, 0.1f);
		m_aActions[e_action_move_right].m_aRightJoystickInputs.Add(pInput);
#elif SH_LINUX
		ShInput * pInput = ShInput::CreateInputPressed(ShInput::e_input_device_pad_first, ShInput::e_input_device_control_linux_pad_left_thumb_x, 0.1f);
		m_aActions[e_action_move_right].m_aRightJoystickInputs.Add(pInput);
#endif // SH_PC
	}

	//
	// Action Jump
	{
#if SH_PC
		ShInput * pInput = ShInput::CreateInputJustPressed(ShInput::e_input_device_keyboard, ShInput::e_input_device_control_pc_key_space, 0.1f);
		m_aActions[e_action_jump].m_aKeyInputs.Add(pInput);
#elif SH_LINUX
		ShInput * pInput = ShInput::CreateInputJustPressed(ShInput::e_input_device_keyboard, ShInput::e_input_device_control_linux_key_space, 0.1f);
		m_aActions[e_action_jump].m_aKeyInputs.Add(pInput);
#endif // SH_PC
	}

	{
#if SH_PC
		ShInput * pInput = ShInput::CreateInputJustPressed(ShInput::e_input_device_pad_first, ShInput::e_input_device_control_pc_pad_a, 0.1f);
		m_aActions[e_action_jump].m_aKeyInputs.Add(pInput);
#elif SH_LINUX
		ShInput * pInput = ShInput::CreateInputJustPressed(ShInput::e_input_device_pad_first, ShInput::e_input_device_control_linux_pad_a, 0.1f);
		m_aActions[e_action_jump].m_aKeyInputs.Add(pInput);
#endif // SH_PC
	}

	// animations

}

//--------------------------------------------------------------------------------------------------
/// @todo comment
//--------------------------------------------------------------------------------------------------
/*virtual*/ GameObjectPlayer::~GameObjectPlayer(void)
{

}

//--------------------------------------------------------------------------------------------------
/// @todo comment
//--------------------------------------------------------------------------------------------------
void GameObjectPlayer::Initialize(const CShIdentifier & levelIdentifier)
{
	char szEntityName[1024];

	m_aAnimationEntity[e_animation_idle].SetCount(ANIMATION_IDLE_COUNT);

	for (int i = 0; i < ANIMATION_IDLE_COUNT; ++i)
	{
		sprintf(szEntityName, "player_anim_idle_%d", i);

		m_aAnimationEntity[e_animation_idle][i] = ShEntity2::Create(levelIdentifier, GID(NULL), GID(layer_default),
			CShIdentifier("ggj"),
			CShIdentifier(szEntityName),
			CShVector3(0.0f,0.0f, 15.0f),
			CShEulerAngles_ZERO,
			CShVector3(1.0f,1.0f,1.0f));

		ShEntity2::SetShow(m_aAnimationEntity[e_animation_idle][i], false);
		ShEntity2::SetPivotBottomCenter(m_aAnimationEntity[e_animation_idle][i]);
	}

	m_aAnimationEntity[e_animation_run].SetCount(ANIMATION_RUN_COUNT);

	for (int i = 0; i < ANIMATION_RUN_COUNT; ++i)
	{
		sprintf(szEntityName, "player_anim_run_%d", i);

		m_aAnimationEntity[e_animation_run][i] = ShEntity2::Create(levelIdentifier, GID(NULL), GID(layer_default),
			CShIdentifier("ggj"),
			CShIdentifier(szEntityName),
			CShVector3(0.0f,0.0f, 15.0f),
			CShEulerAngles_ZERO,
			CShVector3(1.0f,1.0f,1.0f));

		ShEntity2::SetShow(m_aAnimationEntity[e_animation_run][i], false);
		ShEntity2::SetPivotBottomCenter(m_aAnimationEntity[e_animation_run][i]);
	}

	m_eCurrentAnimation = e_animation_idle;
	m_iCurrentAnimation = 0;
}

//--------------------------------------------------------------------------------------------------
/// @todo comment
//--------------------------------------------------------------------------------------------------
void GameObjectPlayer::Release(void)
{
	for (int i = 0; i < ANIMATION_IDLE_COUNT; ++i)
	{
		ShObject::DestroyObject(m_aAnimationEntity[e_animation_idle][i]);
		m_aAnimationEntity[e_animation_idle][i] = shNULL;
	}

	for (int i = 0; i < ANIMATION_RUN_COUNT; ++i)
	{
		ShObject::DestroyObject(m_aAnimationEntity[e_animation_run][i]);
		m_aAnimationEntity[e_animation_run][i] = shNULL;
	}
}

//--------------------------------------------------------------------------------------------------
/// @todo comment
//--------------------------------------------------------------------------------------------------
/*virtual*/ GameObject::EType GameObjectPlayer::GetType(void) const
{
	return(e_type_player);
}

//--------------------------------------------------------------------------------------------------
/// @todo comment
//--------------------------------------------------------------------------------------------------
bool GameObjectPlayer::CheckAction(EAction eAction) const
{
	const ActionBinding & binding = m_aActions[eAction];

	//
	// Check keys
	{
		int count = binding.m_aKeyInputs.GetCount();

		for (int i = 0; i < count; ++i)
		{
			if (ShInput::IsTrue(binding.m_aKeyInputs[i]))
			{
				return(true);
			}
		}
	}

	//
	// Check left joystick
	{
		int count = binding.m_aLeftJoystickInputs.GetCount();

		for (int i = 0; i < count; ++i)
		{
			if (ShInput::GetValue(binding.m_aLeftJoystickInputs[i]) < -0.3f)
			{
				return(true);
			}
		}
	}

	//
	// Check left joystick
	{
		int count = binding.m_aRightJoystickInputs.GetCount();

		for (int i = 0; i < count; ++i)
		{
			if (ShInput::GetValue(binding.m_aRightJoystickInputs[i]) > 0.3f)
			{
				return(true);
			}
		}
	}

	return(false);
}

//--------------------------------------------------------------------------------------------------
/// @todo comment
//--------------------------------------------------------------------------------------------------
void GameObjectPlayer::Update(float dt)
{
	b2Vec2 vSpeed(0.0f, m_pBody->GetLinearVelocity().y);

	if (e_state_move_left != m_eState && CheckAction(e_action_move_left))
	{
		SetState(e_state_move_left);
	}
	else if (e_state_move_right != m_eState && CheckAction(e_action_move_right))
	{
		SetState(e_state_move_right);
	}
	else if (!CheckAction(e_action_move_right) && !CheckAction(e_action_move_left) && e_state_idle != m_eState)
	{
		SetState(e_state_idle);
	}

	switch (m_eState)
	{
		case e_state_move_left:
		{
			vSpeed.x = -PLAYER_SPEED;
		}
		break;

		case e_state_move_right:
		{
			vSpeed.x = PLAYER_SPEED;
		}
		break;

		case e_state_jump:
		{

		}
		break;
	}

	m_pBody->SetLinearVelocity(b2Vec2(vSpeed));

	switch (m_eJumpState)
	{
		case e_jump_state_none:
		{
			if (CheckAction(e_action_jump))
			{
				m_pBody->SetAwake(true);
				m_pBody->ApplyLinearImpulse(b2Vec2(0.0f, 2000.0f), m_pBody->GetPosition(), false);

				m_eJumpState = e_jump_state_simple;

				// TODO : change sprite
			}
		}
		break;

		case e_jump_state_simple:
		{
			if (CheckAction(e_action_jump))
			{
				m_pBody->SetAwake(true);
				m_pBody->ApplyLinearImpulse(b2Vec2(0.0f, 2000.0f), m_pBody->GetPosition(), false);

				m_eJumpState = e_jump_state_double;

				// TODO : change sprite
			}
		}
		break;

		case e_jump_state_double:
		{
			if (m_pBody->GetLinearVelocity().y > -0.01f && m_pBody->GetLinearVelocity().y < 0.01f && shNULL != m_pBody->GetContactList())
			{
				m_eJumpState = e_jump_state_none;

				// TODO : change sprite
			}
		}
		break;
	}


	//
	// Update animation
	m_fAnimationTime += dt;

	if (shNULL != m_aAnimationEntity[m_eCurrentAnimation][m_iCurrentAnimation])
	{
		ShEntity2::SetShow(m_aAnimationEntity[m_eCurrentAnimation][m_iCurrentAnimation], false);
	}

	while (m_fAnimationTime > 0.05f)
	{
		m_iCurrentAnimation++;
		m_iCurrentAnimation %= m_aAnimationEntity[m_eCurrentAnimation].GetCount();
		m_fAnimationTime -= 0.05f;
	}

	if (shNULL != m_aAnimationEntity[m_eCurrentAnimation][m_iCurrentAnimation])
	{
		ShEntity2::SetShow(m_aAnimationEntity[m_eCurrentAnimation][m_iCurrentAnimation], true);

		ShEntity2::SetPositionX(m_aAnimationEntity[m_eCurrentAnimation][m_iCurrentAnimation], m_pBody->GetPosition().x * RATIO_B2_SH);
		ShEntity2::SetPositionY(m_aAnimationEntity[m_eCurrentAnimation][m_iCurrentAnimation], m_pBody->GetPosition().y * RATIO_B2_SH);
	}
}

//--------------------------------------------------------------------------------------------------
/// @todo comment
//--------------------------------------------------------------------------------------------------
void GameObjectPlayer::SetState(EState newState)
{
	ShEntity2::SetShow(m_aAnimationEntity[m_eCurrentAnimation][m_iCurrentAnimation], false);

	EState oldState = m_eState;

	switch (newState)
	{
		case e_state_idle:
		{
			m_eCurrentAnimation = e_animation_idle;
			m_iCurrentAnimation = 0;

			if (oldState == e_state_move_right)
			{
				for (int i = 0; i < ANIMATION_IDLE_COUNT; ++i)
				{
					ShEntity2::SetRotation(m_aAnimationEntity[e_animation_idle][i], CShEulerAngles(0.0f, 0.0f, 0.0f));
				}
			}
			else if (oldState == e_state_move_left)
			{
				for (int i = 0; i < ANIMATION_IDLE_COUNT; ++i)
				{
					ShEntity2::SetRotation(m_aAnimationEntity[e_animation_idle][i], CShEulerAngles(0.0f, SHC_PI, 0.0f));
				}
			}
		}
		break;

		case e_state_move_right:
		{
			m_eCurrentAnimation = e_animation_run;
			m_iCurrentAnimation = 0;

			for (int i = 0; i < ANIMATION_RUN_COUNT; ++i)
			{
				ShEntity2::SetRotation(m_aAnimationEntity[e_animation_run][i], CShEulerAngles(0.0f, 0.0f, 0.0f));
			}
		}
		break;

		case e_state_move_left:
		{
			m_eCurrentAnimation = e_animation_run;
			m_iCurrentAnimation = 0;

			for (int i = 0; i < ANIMATION_RUN_COUNT; ++i)
			{
				ShEntity2::SetRotation(m_aAnimationEntity[e_animation_run][i], CShEulerAngles(0.0f, SHC_PI, 0.0f));
			}
		}
		break;
	}

	m_eState = newState;
}

//--------------------------------------------------------------------------------------------------
/// @todo comment
//--------------------------------------------------------------------------------------------------
ShEntity2 * GameObjectPlayer::GetEntity(void) const
{
	return(m_aAnimationEntity[m_eCurrentAnimation][m_iCurrentAnimation]);
}
