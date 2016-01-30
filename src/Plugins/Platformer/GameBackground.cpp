#include "CShPluginPlatformer.h"

/**
 * @brief GameBackground::GameBackground
 */
GameBackground::GameBackground(void)
: m_pBackgroundEntity(shNULL)
{

}

/**
 * @brief GameBackground::~GameBackground
 */
GameBackground::~GameBackground(void)
{

}

/**
 * @brief GameBackground::Initialize
 */
void GameBackground::Initialize(const CShIdentifier & levelIdentifier)
{
	//
	// find the sky entity
	m_pBackgroundEntity = ShEntity2::Find(levelIdentifier, CShIdentifier("background"));
	SH_ASSERT(shNULL != m_pBackgroundEntity);
}

/**
 * @brief GameBackground::Release
 */
void GameBackground::Release(void)
{

}

/**
 * @brief GameBackground::Update
 * @param dt
 */
void GameBackground::Update(float dt, const CShVector2 & center)
{
	ShEntity2::SetPositionX(m_pBackgroundEntity, center.m_x);
}
