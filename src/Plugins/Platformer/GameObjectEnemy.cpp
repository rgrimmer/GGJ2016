#include "CShPluginPlatformer.h"

//--------------------------------------------------------------------------------------------------
/// @todo comment
//--------------------------------------------------------------------------------------------------
/*explicit*/ GameObjectEnemy::GameObjectEnemy(b2Body * body, ShEntity2 * pEntity)
: GameObject(body)
, m_pEntity(pEntity)
{

}

//--------------------------------------------------------------------------------------------------
/// @todo comment
//--------------------------------------------------------------------------------------------------
/*virtual*/ GameObjectEnemy::~GameObjectEnemy(void)
{

}

//--------------------------------------------------------------------------------------------------
/// @todo comment
//--------------------------------------------------------------------------------------------------
/*virtual*/ GameObject::EType GameObjectEnemy::GetType(void) const
{
	return(e_type_enemy);
}

//--------------------------------------------------------------------------------------------------
/// @todo comment
//--------------------------------------------------------------------------------------------------
void GameObjectEnemy::SetState(EState eState)
{
	m_eState = eState;
}

//--------------------------------------------------------------------------------------------------
/// @todo comment
//--------------------------------------------------------------------------------------------------
GameObjectEnemy::EState GameObjectEnemy::GetState(void) const
{
	return(m_eState);
}

//--------------------------------------------------------------------------------------------------
/// @todo comment
//--------------------------------------------------------------------------------------------------
void GameObjectEnemy::Update(float dt)
{
	b2Vec2 vSpeed(1.0f, m_pBody->GetLinearVelocity().y);

	m_pBody->SetLinearVelocity(vSpeed);

	ShEntity2::SetPositionX(m_pEntity, m_pBody->GetPosition().x * RATIO_B2_SH);
	ShEntity2::SetPositionY(m_pEntity, m_pBody->GetPosition().y * RATIO_B2_SH);
}
