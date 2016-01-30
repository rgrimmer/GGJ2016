#include "CShPluginPlatformer.h"

#define PLAYER_SPEED 1.0f

#define ANIMATION_IDLE_COUNT 24

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
	m_iCurrentAnimation = 0;

	char szEntityName[1024];

	for (int i = 0; i < ANIMATION_IDLE_COUNT; ++i)
	{
		sprintf(szEntityName, "player_anim_idle_%d", i);

		ShEntity2* pEntity = ShEntity2::Create(levelIdentifier,
			CShIdentifier(GID(NULL)),
			CShIdentifier("layer_default"),
			CShIdentifier("ggj"),
			CShIdentifier(szEntityName),
			CShVector3(0.0f,0.0f, 15.0f),
			CShEulerAngles_ZERO,
			CShVector3(1.0f,1.0f,1.0f));

		ShEntity2::SetShow(pEntity, false);
		ShEntity2::SetPivotBottomCenter(pEntity);

		m_aAnimationEntity[e_animation_idle].Add(pEntity);
	}

	m_apCurrentAnimation = m_aAnimationEntity[e_animation_idle];
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



	//update animation
	m_fAnimationTime += dt;

	ShEntity2::SetShow(m_apCurrentAnimation[m_iCurrentAnimation], false);

	while (m_fAnimationTime > 0.05f)
	{
		m_iCurrentAnimation++;
		m_iCurrentAnimation %= m_apCurrentAnimation.GetCount();
		m_fAnimationTime -= 0.05f;
	}

	ShEntity2::SetShow(m_apCurrentAnimation[m_iCurrentAnimation], true);

	ShEntity2::SetPositionX(m_apCurrentAnimation[m_iCurrentAnimation], m_pBody->GetPosition().x * RATIO_B2_SH);
	ShEntity2::SetPositionY(m_apCurrentAnimation[m_iCurrentAnimation], m_pBody->GetPosition().y * RATIO_B2_SH);
}

void GameObjectPlayer::SetState(EState state)
{
	ShEntity2::SetShow(m_apCurrentAnimation[m_iCurrentAnimation], false);
	m_eState = state;

	switch (m_eState)
	{
		case e_state_idle :
		{
			m_apCurrentAnimation = m_aAnimationEntity[e_animation_idle];
		}
		break;
	}
}

ShEntity2 * GameObjectPlayer::GetEntity(void) const
{
	return m_apCurrentAnimation[m_iCurrentAnimation];
}
