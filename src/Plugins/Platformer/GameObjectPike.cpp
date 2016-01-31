#include "CShPluginPlatformer.h"

//--------------------------------------------------------------------------------------------------
/// @todo comment
//--------------------------------------------------------------------------------------------------
/*explicit*/ GameObjectPike::GameObjectPike(CShPluginPlatformer * pPlatformer, b2Body * body, ShEntity2 * pEntity)
: GameObject(body)
, m_pEntity(pEntity)
, m_pPlatformer(pPlatformer)
{
	ShEntity2::SetShow(pEntity, false);
}

//--------------------------------------------------------------------------------------------------
/// @todo comment
//--------------------------------------------------------------------------------------------------
/*virtual*/ GameObjectPike::~GameObjectPike(void)
{

}

//--------------------------------------------------------------------------------------------------
/// @todo comment
//--------------------------------------------------------------------------------------------------
/*virtual*/ GameObject::EType GameObjectPike::GetType(void) const
{
	return(e_type_pike);
}

//--------------------------------------------------------------------------------------------------
/// @todo comment
//--------------------------------------------------------------------------------------------------
void GameObjectPike::Start(void)
{
	ShEntity2::SetShow(m_pEntity, true);
	m_pPlatformer->m_bRestartGame = true;
}

//--------------------------------------------------------------------------------------------------
/// @todo comment
//--------------------------------------------------------------------------------------------------
void GameObjectPike::End(void)
{
	ShEntity2::SetShow(m_pEntity, false);
}

