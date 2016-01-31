#include "Game.h"

//--------------------------------------------------------------------------------------------------
/// @todo comment
//--------------------------------------------------------------------------------------------------
/*explicit*/ GameStateMenuCredits::GameStateMenuCredits(void)
: GameState()
, m_pTextZone(shNULL)
{

}

//--------------------------------------------------------------------------------------------------
/// @todo comment
//--------------------------------------------------------------------------------------------------
/*virtual*/ GameStateMenuCredits::~GameStateMenuCredits(void)
{

}

//--------------------------------------------------------------------------------------------------
/// @todo comment
//--------------------------------------------------------------------------------------------------
void GameStateMenuCredits::Initialize(void)
{

}

//--------------------------------------------------------------------------------------------------
/// @todo comment
//--------------------------------------------------------------------------------------------------
void GameStateMenuCredits::Release(void)
{

}

//--------------------------------------------------------------------------------------------------
/// @todo comment
//--------------------------------------------------------------------------------------------------
void GameStateMenuCredits::Obscuring(void)
{
	DeActivate();
}

//--------------------------------------------------------------------------------------------------
/// @todo comment
//--------------------------------------------------------------------------------------------------
void GameStateMenuCredits::Revealed(void)
{
	Activate();
}

//--------------------------------------------------------------------------------------------------
/// @todo comment
//--------------------------------------------------------------------------------------------------
void GameStateMenuCredits::Exiting(void)
{
	DeActivate();
}

//--------------------------------------------------------------------------------------------------
/// @todo comment
//--------------------------------------------------------------------------------------------------
void GameStateMenuCredits::Entered(void)
{
	Activate();
}

//--------------------------------------------------------------------------------------------------
/// @todo comment
//--------------------------------------------------------------------------------------------------
void GameStateMenuCredits::Activate(void)
{
	CShIdentifier levelIdentifier("level_credits");
	ShLevel::Load(CShIdentifier(levelIdentifier));

	ShLayer * pLayer = ShLayer::Find(CShIdentifier("layer_default"));
	m_pTextZone = ShTextZone::Create(levelIdentifier,
								CShIdentifier("text"),
								pLayer,
								CShAABB2(-1000.0f, 1000.0f, -50.0f, 50.0f),
								CShVector3(0.0f, 0.0f, 5.0f),
								CShEulerAngles_ZERO,
								CShVector3(1.0f, 1.0f, 1.0f),
								ShTextZone::e_align_center_center,
								false,
								CShIdentifier("futura_book_60.abc"),
								CShRGBAf(1.0f,1.0f,1.0f,1.0f));

	ShTextZone::SetText(m_pTextZone, CShString("[font color=\"#FFFF00\"]Game Designer[/font][br /] foxbullbee [br /][font color=\"#FFFF00\"]Sound Designer[/font][br /] Noctiluca [br /][font color=\"#FFFF00\"]Programmers[/font][br /] rgrimmer [br /] magestik"));
}

//--------------------------------------------------------------------------------------------------
/// @todo comment
//--------------------------------------------------------------------------------------------------
void GameStateMenuCredits::DeActivate(void)
{
	ShLevel::Release();
}

//--------------------------------------------------------------------------------------------------
/// @todo comment
//--------------------------------------------------------------------------------------------------
void GameStateMenuCredits::Update(float dt)
{

}

//--------------------------------------------------------------------------------------------------
/// @todo comment
//--------------------------------------------------------------------------------------------------
/*virtual*/ void GameStateMenuCredits::OnTouchDown(int iTouch, float positionX, float positionY)
{

}

//--------------------------------------------------------------------------------------------------
/// @todo comment
//--------------------------------------------------------------------------------------------------
/*virtual*/ void GameStateMenuCredits::OnTouchUp(int iTouch, float positionX, float positionY)
{

}

//--------------------------------------------------------------------------------------------------
/// @todo comment
//--------------------------------------------------------------------------------------------------
/*virtual*/ void GameStateMenuCredits::OnTouchMove(int iTouch, float positionX, float positionY)
{

}
