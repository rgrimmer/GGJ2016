#include "CShPluginPlatformer.h"

#define PLAYER_SPEED 1.0f

//--------------------------------------------------------------------------------------------------
/// @todo comment
//--------------------------------------------------------------------------------------------------
/*explicit*/ GameObjectPlayer::GameObjectPlayer(b2Body * body, ShEntity2 * pEntity)
: GameObject(body)
, m_eJumpState(e_jump_state_none)
, m_pEntity(pEntity)
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
/*virtual*/ GameObjectPlayer::EType GameObjectPlayer::GetType(void) const
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

	if (CheckAction(e_action_move_left))
	{
		vSpeed.x = -PLAYER_SPEED;
	}

	if (CheckAction(e_action_move_right))
	{
		vSpeed.x = PLAYER_SPEED;
	}

	m_pBody->SetLinearVelocity(b2Vec2(vSpeed));

	switch (m_eJumpState)
	{
		case e_jump_state_none:
		{
			if (CheckAction(e_action_jump))
			{
				m_pBody->SetAwake(true);
				m_pBody->ApplyLinearImpulse(b2Vec2(0.0f, 20.0f), m_pBody->GetPosition(), false);

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
				m_pBody->ApplyLinearImpulse(b2Vec2(0.0f, 20.0f), m_pBody->GetPosition(), false);

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

	ShEntity2::SetPositionX(m_pEntity, m_pBody->GetPosition().x * RATIO_B2_SH);
	ShEntity2::SetPositionY(m_pEntity, m_pBody->GetPosition().y * RATIO_B2_SH);
}

ShEntity2 * GameObjectPlayer::GetEntity(void) const
{
	return m_pEntity;
}
