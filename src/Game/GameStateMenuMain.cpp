#include "Game.h"

//--------------------------------------------------------------------------------------------------
/// @todo comment
//--------------------------------------------------------------------------------------------------
/*explicit*/ GameStateMenuMain::GameStateMenuMain(void)
: GameState()
, m_aTextZoneMenu()
, m_pTextZonePlay(shNULL)
, m_pTextZoneCredits(shNULL)
, m_iMenuSelectedIndex(0)
, m_pEntityHiglight(shNULL)
{

}

//--------------------------------------------------------------------------------------------------
/// @todo comment
//--------------------------------------------------------------------------------------------------
/*virtual*/ GameStateMenuMain::~GameStateMenuMain(void)
{

}

//--------------------------------------------------------------------------------------------------
/// @todo comment
//--------------------------------------------------------------------------------------------------
void GameStateMenuMain::Initialize(void)
{
	//create inputs
	m_aInputs[e_input_up] = ShInput::CreateInputJustPressed(ShInput::e_input_device_keyboard, ShInput::e_input_device_control_pc_key_up, 0.1f);
	m_aInputs[e_input_down] = ShInput::CreateInputJustPressed(ShInput::e_input_device_keyboard, ShInput::e_input_device_control_pc_key_down, 0.1f);
	m_aInputs[e_input_validate] = ShInput::CreateInputJustPressed(ShInput::e_input_device_keyboard, ShInput::e_input_device_control_pc_key_return, 0.1f);
	m_aInputs[e_input_cancel] = ShInput::CreateInputJustPressed(ShInput::e_input_device_keyboard, ShInput::e_input_device_control_pc_key_escape, 0.1f);
}

//--------------------------------------------------------------------------------------------------
/// @todo comment
//--------------------------------------------------------------------------------------------------
void GameStateMenuMain::Release(void)
{

}

//--------------------------------------------------------------------------------------------------
/// @todo comment
//--------------------------------------------------------------------------------------------------
void GameStateMenuMain::Obscuring(void)
{
	DeActivate();
}

//--------------------------------------------------------------------------------------------------
/// @todo comment
//--------------------------------------------------------------------------------------------------
void GameStateMenuMain::Revealed(void)
{
	Activate();
}

//--------------------------------------------------------------------------------------------------
/// @todo comment
//--------------------------------------------------------------------------------------------------
void GameStateMenuMain::Exiting(void)
{
	DeActivate();
}

//--------------------------------------------------------------------------------------------------
/// @todo comment
//--------------------------------------------------------------------------------------------------
void GameStateMenuMain::Entered(void)
{
	Activate();
}

//--------------------------------------------------------------------------------------------------
/// @todo comment
//--------------------------------------------------------------------------------------------------
void GameStateMenuMain::Activate(void)
{
	CShIdentifier levelIdentifier("level_main_menu");

	bool bLoaded = ShLevel::Load(CShIdentifier(levelIdentifier));
	SH_ASSERT(bLoaded);

	m_pTextZonePlay = ShTextZone::Find(levelIdentifier, CShIdentifier("text_zone_play"));
	SH_ASSERT(shNULL != m_pTextZonePlay);

	m_pTextZoneCredits = ShTextZone::Find(levelIdentifier, CShIdentifier("text_zone_credits"));
	SH_ASSERT(shNULL != m_pTextZoneCredits);

	m_aTextZoneMenu.Add(m_pTextZonePlay);
	m_aTextZoneMenu.Add(m_pTextZoneCredits);

	char szEntityHighlightName[1024];
	sprintf(szEntityHighlightName, "sprite_%s_menu_highlight_001", SPRITE_LIBRARY);
	m_pEntityHiglight = ShEntity2::Find(levelIdentifier, CShIdentifier(szEntityHighlightName));
	SH_ASSERT(NULL != m_pEntityHiglight);

	m_iMenuSelectedIndex = 0;
	UpdateHighlightPosition();
}

//--------------------------------------------------------------------------------------------------
/// @todo comment
//--------------------------------------------------------------------------------------------------
void GameStateMenuMain::DeActivate(void)
{
	m_aTextZoneMenu.Empty();

	ShLevel::Release();
}

//--------------------------------------------------------------------------------------------------
/// @todo comment
//--------------------------------------------------------------------------------------------------
void GameStateMenuMain::Update(float dt)
{
	if (ShInput::IsTrue(m_aInputs[e_input_down]))
	{
		m_iMenuSelectedIndex = (m_iMenuSelectedIndex + 1) % m_aTextZoneMenu.GetCount();
		UpdateHighlightPosition();
	}
	else if(ShInput::IsTrue(m_aInputs[e_input_up]))
	{
		m_iMenuSelectedIndex = (m_iMenuSelectedIndex + m_aTextZoneMenu.GetCount() - 1) % m_aTextZoneMenu.GetCount();
		UpdateHighlightPosition();
	}
	else if(ShInput::IsTrue(m_aInputs[e_input_validate]))
	{
		switch(m_iMenuSelectedIndex)
		{
			case e_menu_play : 
			{
				Game::instance().PushWithTransition(Game::GAME);
			}
			break;

			case e_menu_credits :
			{
				Game::instance().PushWithTransition(Game::CREDITS);
			}
			break;
		}
	}
}

//--------------------------------------------------------------------------------------------------
/// @todo comment
//--------------------------------------------------------------------------------------------------
void GameStateMenuMain::UpdateHighlightPosition(void)
{
	float fWidth = ShTextZone::GetSize(m_aTextZoneMenu[m_iMenuSelectedIndex]).m_x * 0.5f;
	ShObject::SetPositionX(m_pEntityHiglight, -fWidth - ShEntity2::GetWidth(m_pEntityHiglight) * 0.5f) ;
	ShObject::SetPositionY(m_pEntityHiglight, ShObject::GetPosition2(m_aTextZoneMenu[m_iMenuSelectedIndex]).m_y);
}

//--------------------------------------------------------------------------------------------------
/// @todo comment
//--------------------------------------------------------------------------------------------------
/*virtual*/ void GameStateMenuMain::OnTouchDown(int iTouch, float positionX, float positionY)
{
	
}

//--------------------------------------------------------------------------------------------------
/// @todo comment
//--------------------------------------------------------------------------------------------------
/*virtual*/ void GameStateMenuMain::OnTouchUp(int iTouch, float positionX, float positionY)
{

}

//--------------------------------------------------------------------------------------------------
/// @todo comment
//--------------------------------------------------------------------------------------------------
/*virtual*/ void GameStateMenuMain::OnTouchMove(int iTouch, float positionX, float positionY)
{

}