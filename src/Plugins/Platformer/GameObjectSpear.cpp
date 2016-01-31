#include "CShPluginPlatformer.h"


//--------------------------------------------------------------------------------------------------
/// @todo comment
//--------------------------------------------------------------------------------------------------
/*explicit*/ GameObjectSpear::GameObjectSpear(const CShIdentifier & levelIdentifier, b2BodyType eType, b2Body * body, ShEntity2 * pEntity)
: GameObject(body)
, m_eType(eType)
, m_eState(e_state_off)
, m_bDeActivateBody(false)
{
	m_pBody->SetTransform(b2Vec2(-2000.0f / RATIO_B2_SH, 0.0f), 0.0f);
	m_pBody->SetActive(false);

	if (eType == b2_kinematicBody)
	{
		m_pEntity = pEntity;
	}
	else
	{
		m_pEntity = ShEntity2::Create(levelIdentifier,
						GID(NULL),
						CShIdentifier("layer_default"),
						CShIdentifier("ggj"),
						CShIdentifier("spear"),
						CShVector3(0.0f,0.0f,15.1f),
						CShEulerAngles_ZERO,
						CShVector3(1.0f, 1.0f, 1.0f));
	}

	m_fStateTime = 0.0f;

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

	if (m_eType == b2_kinematicBody)
	{
		if (m_eState == e_state_on)
		{
			m_pBody->SetLinearVelocity(b2Vec2(-3.0f, 0.0f));
			m_pBody->SetActive(true);
			float fRandPositionY = rand() % 800 - 400;
			m_pBody->SetTransform(b2Vec2((fCameraCenter + 1920.0f) / RATIO_B2_SH, fRandPositionY / RATIO_B2_SH), 0.0f);
		}
		else if(m_eState == e_state_off)
		{
			m_pBody->SetActive(false);
		}
	}
	else
	{
		if (m_eState == e_state_on)
		{
			ShEntity2::SetAlpha(m_pEntity, 1.0f);

			m_pBody->SetActive(true);
			float fRandPositionY = rand() % 400 - 200;
			m_pBody->SetTransform(b2Vec2((fCameraCenter - 1100.0f) / RATIO_B2_SH, fRandPositionY / RATIO_B2_SH), SHC_PI);

			float fRandForce = 5 + rand() % 5;
			m_pBody->SetLinearVelocity(b2Vec2(fRandForce,0.0f));
			m_pBody->SetAngularVelocity(-SHC_PI / 4.0f);
			ShEntity2::SetShow(m_pEntity, true);
		}
		else if(m_eState == e_state_plant)
		{
			m_bDeActivateBody = true;
		}
		else if(m_eState == e_state_off)
		{
			m_pBody->SetActive(false);
			ShEntity2::SetShow(m_pEntity, false);
		}
	}

	m_fStateTime = 0.0f;
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
	m_fStateTime += dt;

	if (m_bDeActivateBody)
	{
		m_pBody->SetActive(false);
		m_bDeActivateBody = false;
	}
	else
	{
		if (e_state_on == m_eState)
		{
			ShEntity2::SetPositionX(m_pEntity, m_pBody->GetPosition().x * RATIO_B2_SH);
			ShEntity2::SetPositionY(m_pEntity, m_pBody->GetPosition().y * RATIO_B2_SH);

			ShEntity2::SetRotation(m_pEntity, 0.0f, 0.0f, m_pBody->GetAngle());

			if (ShEntity2::GetPosition2(m_pEntity).m_y < -800.0f)
			{
				SetState(e_state_off, 0.0f);
			}
		}
		else if (e_state_plant == m_eState)
		{
			if (m_fStateTime > 2.0f)
			{
				SetState(e_state_disappear, 0.0f);
			}
		}
		else if (e_state_disappear == m_eState)
		{
			if (m_fStateTime < 1.0f)
			{
				ShEntity2::SetAlpha(m_pEntity, 1.0f - m_fStateTime);
			}
			else
			{
				ShEntity2::SetAlpha(m_pEntity, 0.0f);
				SetState(e_state_off, 0.0f);
			}
		}
	}

}
