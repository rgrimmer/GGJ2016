#include "CShPluginPlatformer.h"

#define PLAYER_SPEED 10.0f

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
#else if SH_LINUX
	m_aInputs[e_input_move_left] = ShInput::CreateInputPressed(ShInput::e_input_device_keyboard, ShInput::e_input_device_control_linux_key_left, 0.1f);
	m_aInputs[e_input_move_right] = ShInput::CreateInputPressed(ShInput::e_input_device_keyboard, ShInput::e_input_device_control_linux_key_right, 0.1f);
	m_aInputs[e_input_jump] = ShInput::CreateInputJustPressed(ShInput::e_input_device_keyboard, ShInput::e_input_device_control_linux_key_space, 0.1f);
#endif //SH_PC

}

//--------------------------------------------------------------------------------------------------
/// @todo comment
//--------------------------------------------------------------------------------------------------
/*virtual*/ GameObjectPlayer::~GameObjectPlayer(void)
{
	m_pBody->SetUserData(NULL);
	b2World * world = m_pBody->GetWorld();
	world->DestroyBody(m_pBody);
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
void GameObjectPlayer::Update(void)
{
	b2Vec2 vSpeed = m_pBody->GetLinearVelocity();

	if (ShInput::IsTrue(m_aInputs[e_input_move_left]))
	{
		vSpeed.x = PLAYER_SPEED;
	}

	if (ShInput::IsTrue(m_aInputs[e_input_move_right]))
	{
		vSpeed.x = -PLAYER_SPEED;
	}

	if (ShInput::IsTrue(m_aInputs[e_input_jump]))
	{
		m_pBody->ApplyLinearImpulse(b2Vec2(0.0f, 5.0f), m_pBody->GetPosition(), false);
	}

	m_pBody->SetLinearVelocity(b2Vec2(vSpeed));

	ShEntity2::SetPositionX(m_pEntity, m_pBody->GetPosition().x);
	ShEntity2::SetPositionY(m_pEntity, m_pBody->GetPosition().y);
}
