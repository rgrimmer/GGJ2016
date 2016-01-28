#include "Game.h"

//--------------------------------------------------------------------------------------------------
/// @todo comment
//--------------------------------------------------------------------------------------------------
/*explicit*/ Transition::Transition(void)
: m_eState(e_state_idle)
, m_fStateTime(0.0f)
, m_pEntityBackground(shNULL)
{

}

//--------------------------------------------------------------------------------------------------
/// @todo comment
//--------------------------------------------------------------------------------------------------
/*virtual*/ Transition::~Transition(void)
{

}

//--------------------------------------------------------------------------------------------------
/// @todo comment
//--------------------------------------------------------------------------------------------------
void Transition::Initialize(void)
{
	m_fStateTime = 0.0f;

	CShIdentifier levelIdentifier("level_transition");
	ShLevel::Load(CShIdentifier(levelIdentifier));

	char szEntityName[1024];
	sprintf(szEntityName, "sprite_%s_background", SPRITE_LIBRARY);
	m_pEntityBackground = ShEntity2::Find(levelIdentifier, CShIdentifier("sprite_ggj_background"));
	SH_ASSERT(NULL != m_pEntityBackground);

	ShObject::SetAlpha(m_pEntityBackground, 0.0f);
	ShEntity2::SetShow(m_pEntityBackground, false);

	m_eState = e_state_idle;
}

//--------------------------------------------------------------------------------------------------
/// @todo comment
//--------------------------------------------------------------------------------------------------
void Transition::Release(void)
{
	ShLevel::Release();
}

//--------------------------------------------------------------------------------------------------
/// @todo comment
//--------------------------------------------------------------------------------------------------
void Transition::Update(float dt)
{
	m_fStateTime += dt;

	if (e_state_transition_in == m_eState)
	{
		if (m_fStateTime < 1.0f)
		{
			ShObject::SetAlpha(m_pEntityBackground, m_fStateTime);
		}
		else
		{
			ShObject::SetAlpha(m_pEntityBackground, 1.0f);
			m_eState = e_state_waiting;
		}
	}
	else if(e_state_transition_out == m_eState)
	{
		if (m_fStateTime < 1.0f)
		{
			ShObject::SetAlpha(m_pEntityBackground, 1.0f - m_fStateTime);
		}
		else
		{
			ShObject::SetAlpha(m_pEntityBackground, 0.0f);
			ShEntity2::SetShow(m_pEntityBackground, false);
			m_eState = e_state_idle;
		}
	}
}

//--------------------------------------------------------------------------------------------------
/// @todo comment
//--------------------------------------------------------------------------------------------------
void Transition::SetState(EState eState)
{
	if (e_state_transition_in == eState)
	{
		ShEntity2::SetShow(m_pEntityBackground, true);
	}

	m_eState = eState;
	m_fStateTime = 0.0f;
}

//--------------------------------------------------------------------------------------------------
/// @todo comment
//--------------------------------------------------------------------------------------------------
const Transition::EState Transition::GetState(void) const
{
	return m_eState;
}

