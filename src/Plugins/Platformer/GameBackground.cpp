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
	//
	// find the sky entity
	{
		Plane p0;

		p0.speed = 0.0f;

		ShEntity2 * pEntity = ShEntity2::Find(levelIdentifier, CShIdentifier("background"));
		SH_ASSERT(shNULL != pEntity);

		p0.aEntities.Add(pEntity);

		m_aPlane.Add(p0);
	}

	//
	// find the first plane elements
	{
		Plane p1;

		p1.speed = -3.0f;

		ShEntity2 * pEntity = ShEntity2::Find(levelIdentifier, CShIdentifier("plane_01_elmt_01"));
		SH_ASSERT(shNULL != pEntity);

		p1.aEntities.Add(pEntity);

		m_aPlane.Add(p1);
	}

	//
	// find the second plane elements
	{
		Plane p2;

		p2.speed = -5.0f;

		ShEntity2 * pEntity = ShEntity2::Find(levelIdentifier, CShIdentifier("plane_02_elmt_01"));
		SH_ASSERT(shNULL != pEntity);

		p2.aEntities.Add(pEntity);

		m_aPlane.Add(p2);
	}

	//
	// find the third plane elements
	{
		Plane p3;

		p3.speed = -8.0f;

		ShEntity2 * pEntity = ShEntity2::Find(levelIdentifier, CShIdentifier("plane_03_elmt_01"));
		SH_ASSERT(shNULL != pEntity);

		p3.aEntities.Add(pEntity);

		m_aPlane.Add(p3);
	}

	//
	// find the ground plane elements
	{
		Plane p4;

		p4.speed = -20.0f;

		ShEntity2 * pEntity1 = ShEntity2::Find(levelIdentifier, CShIdentifier("plane_04_elmt_01"));
		SH_ASSERT(shNULL != pEntity1);

		p4.aEntities.Add(pEntity1);

		ShEntity2 * pEntity2 = ShEntity2::Find(levelIdentifier, CShIdentifier("plane_04_elmt_02"));
		SH_ASSERT(shNULL != pEntity2);

		p4.aEntities.Add(pEntity2);

		m_aPlane.Add(p4);
	}
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
