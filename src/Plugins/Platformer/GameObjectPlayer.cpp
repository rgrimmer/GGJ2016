#include "CShPluginPlatformer.h"

#define PLAYER_SPEED 1.0f

//--------------------------------------------------------------------------------------------------
/// @todo comment
//--------------------------------------------------------------------------------------------------
/*explicit*/ GameObjectPlayer::GameObjectPlayer(b2Body * body, ShEntity2 * pEntity)
: GameObject(body)
, m_pEntity(pEntity)
{
#if SH_PC
	m_aInputs[e_input_move_left] = ShInput::CreateInputPressed(ShInput::e_input_device_keyboard, ShInput::e_input_device_control_pc_key_left, 0.1f);
	m_aInputs[e_input_move_right] = ShInput::CreateInputPressed(ShInput::e_input_device_keyboard, ShInput::e_input_device_control_pc_key_right, 0.1f);
	m_aInputs[e_input_jump] = ShInput::CreateInputJustPressed(ShInput::e_input_device_keyboard, ShInput::e_input_device_control_pc_key_space, 0.1f);
#elif SH_LINUX
	m_aInputs[e_input_move_left] = ShInput::CreateInputPressed(ShInput::e_input_device_keyboard, ShInput::e_input_device_control_linux_key_left, 0.1f);
	m_aInputs[e_input_move_right] = ShInput::CreateInputPressed(ShInput::e_input_device_keyboard, ShInput::e_input_device_control_linux_key_right, 0.1f);
	m_aInputs[e_input_jump] = ShInput::CreateInputJustPressed(ShInput::e_input_device_keyboard, ShInput::e_input_device_control_linux_key_space, 0.1f);
#endif // SH_PC

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
void GameObjectPlayer::SetState(EState eState)
{
	m_eState = eState;
}

//--------------------------------------------------------------------------------------------------
/// @todo comment
//--------------------------------------------------------------------------------------------------
GameObjectPlayer::EState GameObjectPlayer::GetState(void) const
{
	return(m_eState);
}

//--------------------------------------------------------------------------------------------------
/// @todo comment
//--------------------------------------------------------------------------------------------------
void GameObjectPlayer::Update(float dt)
{
	b2Vec2 vSpeed(0.0f, m_pBody->GetLinearVelocity().y);

	if (ShInput::IsTrue(m_aInputs[e_input_move_left]))
	{
		vSpeed.x = -PLAYER_SPEED;
	}

	if (ShInput::IsTrue(m_aInputs[e_input_move_right]))
	{
		vSpeed.x = PLAYER_SPEED;
	}

	m_pBody->SetLinearVelocity(b2Vec2(vSpeed));

	if (ShInput::IsTrue(m_aInputs[e_input_jump]))
	{
		m_pBody->ApplyLinearImpulse(b2Vec2(0.0f, 20.0f), m_pBody->GetPosition(), false);
	}


	ShEntity2::SetPositionX(m_pEntity, m_pBody->GetPosition().x * RATIO_B2_SH);
	ShEntity2::SetPositionY(m_pEntity, m_pBody->GetPosition().y * RATIO_B2_SH);
}
