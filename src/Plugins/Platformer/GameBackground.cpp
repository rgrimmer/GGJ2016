#include "CShPluginPlatformer.h"

/**
 * @brief GameBackground::GameBackground
 */
GameBackground::GameBackground(void)
: m_fLastPosX(0.0f)
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
	// ...
}

/**
 * @brief GameBackground::Release
 */
void GameBackground::Release(void)
{
	m_fLastPosX = 0.0f;
	m_aPlane.Empty();
}

/**
 * @brief GameBackground::LoadParallax
 * @param pNode
 */
void GameBackground::LoadParallax(const CShIdentifier & levelIdentifier, ShScriptTreeNode * pNode)
{
	int planeCount = ShScriptTreeNode::GetChildCount(pNode);

	m_aPlane.SetCount(planeCount);

	for (int i = 0; i < planeCount; ++i)
	{
		ShScriptTreeNode * pPlaneNode = ShScriptTreeNode::GetChild(pNode, i);
		const CShIdentifier & planeIdentifier = ShScriptTreeNode::GetIdentifier(pPlaneNode);
		SH_ASSERT(CShIdentifier("plane") == planeIdentifier);

		bool success = ShScriptTreeNode::GetAttributeValueAsFloat(pPlaneNode, CShIdentifier("speed"), m_aPlane[i].speed);

		int entityCount = ShScriptTreeNode::GetChildCount(pPlaneNode);

		m_aPlane[i].aEntities.SetCount(entityCount);

		for (int j = 0; j < entityCount; ++j)
		{
			ShScriptTreeNode * pEntityNode = ShScriptTreeNode::GetChild(pPlaneNode, j);
			const CShIdentifier & entityIdentifier = ShScriptTreeNode::GetIdentifier(pEntityNode);
			SH_ASSERT(CShIdentifier("entity") == entityIdentifier);

			CShString strIdentifier;
			bool success = ShScriptTreeNode::GetAttributeValueAsString(pEntityNode, CShIdentifier("identifier"), strIdentifier);

			m_aPlane[i].aEntities[j] = ShEntity2::Find(levelIdentifier, CShIdentifier(strIdentifier));
			SH_ASSERT(shNULL != m_aPlane[i].aEntities[j]);
		}
	}
}

/**
 * @brief GameBackground::Update
 * @param dt
 */
void GameBackground::Update(float dt, const CShVector2 & center)
{
	float speed = 0.0f;
	float translation = center.m_x - m_fLastPosX;

	int planeCount = m_aPlane.GetCount();

	for (int i = 0; i < planeCount; ++i)
	{
		Plane & plane = m_aPlane[i];

		speed += plane.speed;

		int entityCount = plane.aEntities.GetCount();

		for (int j = 0; j < entityCount; ++j)
		{
			ShEntity2 * pEntity = plane.aEntities[j];
			ShEntity2::Translate(pEntity, CShVector3(translation + speed * dt * translation, 0.0f, 0.0f));
		}
	}

	m_fLastPosX = center.m_x;
}
