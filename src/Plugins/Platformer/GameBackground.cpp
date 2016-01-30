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

		m_aPlane[i].totalWidth = 0.0f;

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

			m_aPlane[i].totalWidth += ShEntity2::GetWidth(m_aPlane[i].aEntities[j]) * ShEntity2::GetScale(m_aPlane[i].aEntities[j]).m_x;
		}
	}
}

/**
 * @brief GameBackground::Update
 * @param dt
 */
void GameBackground::Update(float dt, const CShVector2 & center)
{
	float translation = center.m_x - m_fLastPosX;

	int planeCount = m_aPlane.GetCount();

	for (int i = 0; i < planeCount; ++i)
	{
		Plane & plane = m_aPlane[i];

		int entityCount = plane.aEntities.GetCount();

		for (int j = 0; j < entityCount; ++j)
		{
			float translationValue = translation + plane.speed * 0.01f * translation;

			ShEntity2 * pEntity = plane.aEntities[j];
			ShEntity2::Translate(pEntity, CShVector3(translationValue, 0.0f, 0.0f));

			float halfWidth = ShEntity2::GetWidth(pEntity) * ShEntity2::GetScale(pEntity).m_x * 0.5f;
			const CShVector2 & pos = ShEntity2::GetPosition2(pEntity);

			if (translationValue > 0.0f)
			{
				if ((pos.m_x + halfWidth) < (center.m_x - DISPLAY_WIDTH * 0.5f)) // right side of the image out of screen ?
				{
					ShEntity2::Translate(pEntity, CShVector3(-plane.totalWidth, 0.0f, 0.0f));
				}
			}
			else
			{
				if ((pos.m_x - halfWidth) > (center.m_x + DISPLAY_WIDTH * 0.5f)) // left side of the image out of screen ?
				{
					ShEntity2::Translate(pEntity, CShVector3(plane.totalWidth, 0.0f, 0.0f));
				}
			}
		}
	}

	m_fLastPosX = center.m_x;
}
