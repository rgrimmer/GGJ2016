#include "CShPluginPlatformer.h"


//--------------------------------------------------------------------------------------------------
/// @todo comment
//--------------------------------------------------------------------------------------------------
/*explicit*/ GameObjectSpear::GameObjectSpear(b2Body * body, ShEntity2 * pEntity)
: GameObject(body)
, m_pEntity(pEntity)
{
	m_pBody->SetTransform(b2Vec2(0.0f, 0.0f), 0.0f);
	m_pBody->SetActive(false);
}

//--------------------------------------------------------------------------------------------------
/// @todo comment
//--------------------------------------------------------------------------------------------------
/*virtual*/ GameObjectSpear::~GameObjectSpear(void)
{

}

//--------------------------------------------------------------------------------------------------
/// @todo comment
//--------------------------------------------------------------------------------------------------
/*virtual*/ GameObjectSpear::EType GameObjectSpear::GetType(void) const
{
	return(e_type_spear);
}

//--------------------------------------------------------------------------------------------------
/// @todo comment
//--------------------------------------------------------------------------------------------------
void GameObjectSpear::SetState(EState eState, float fCameraCenter)
{
	m_eState = eState;

	if (m_eState == e_state_on)
	{
		//ShEntity2::SetShow(m_pEntity, true);
		m_pBody->SetActive(true);
		float fRandPositionY = rand() % 400 - 200;
		m_pBody->SetTransform(b2Vec2((fCameraCenter + 1920.0f) / RATIO_B2_SH, fRandPositionY / RATIO_B2_SH), 0.0f);
	}
	else if(m_eState == e_state_off)
	{
		//ShEntity2::SetShow(m_pEntity, false);
		m_pBody->SetActive(false);
	}
}

//--------------------------------------------------------------------------------------------------
/// @todo comment
//--------------------------------------------------------------------------------------------------
GameObjectSpear::EState GameObjectSpear::GetState(void) const
{
	return(m_eState);
}

//--------------------------------------------------------------------------------------------------
/// @todo comment
//--------------------------------------------------------------------------------------------------
void GameObjectSpear::Update(float dt)
{
	m_pBody->SetLinearVelocity(b2Vec2(-3.0f, 0.0f));

	ShEntity2::SetPositionX(m_pEntity, m_pBody->GetPosition().x * RATIO_B2_SH);
	ShEntity2::SetPositionY(m_pEntity, m_pBody->GetPosition().y * RATIO_B2_SH);
}
