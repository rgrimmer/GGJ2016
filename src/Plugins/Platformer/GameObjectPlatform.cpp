#include "CShPluginPlatformer.h"


//--------------------------------------------------------------------------------------------------
/// @todo comment
//--------------------------------------------------------------------------------------------------
/*explicit*/ GameObjectPlatform::GameObjectPlatform(void)
: GameObject(shNULL)
, m_pEntity(shNULL)
{

}

//--------------------------------------------------------------------------------------------------
/// @todo comment
//--------------------------------------------------------------------------------------------------
/*explicit*/ GameObjectPlatform::GameObjectPlatform(b2Body * body, ShEntity2 * pEntity)
: GameObject(body)
, m_pEntity(pEntity)
{

}

//--------------------------------------------------------------------------------------------------
/// @todo comment
//--------------------------------------------------------------------------------------------------
/*virtual*/ GameObjectPlatform::~GameObjectPlatform(void)
{

}

//--------------------------------------------------------------------------------------------------
/// @todo comment
//--------------------------------------------------------------------------------------------------
/*virtual*/ GameObjectPlatform::EType GameObjectPlatform::GetType(void) const
{
	return(e_type_platform);
}

//--------------------------------------------------------------------------------------------------
/// @todo comment
//--------------------------------------------------------------------------------------------------
void GameObjectPlatform::SetState(EState eState)
{
	m_eState = eState;
}

//--------------------------------------------------------------------------------------------------
/// @todo comment
//--------------------------------------------------------------------------------------------------
GameObjectPlatform::EState GameObjectPlatform::GetState(void) const
{
	return(m_eState);
}

//--------------------------------------------------------------------------------------------------
/// @todo comment
//--------------------------------------------------------------------------------------------------
void GameObjectPlatform::Update(float dt)
{

}
