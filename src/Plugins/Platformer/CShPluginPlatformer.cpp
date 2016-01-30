#include "CShPluginPlatformer.h"

#include <Box2D/Box2D.h>

BEGIN_DERIVED_CLASS(CShPluginPlatformer, CShPlugin)
	// ...
END_CLASS()

CShPluginPlatformer::CShPluginPlatformer(void)
: CShPlugin(CShIdentifier("Platformer"))
, m_pWorld(shNULL)
, m_aBody()
{

}

/*virtual*/ CShPluginPlatformer::~CShPluginPlatformer(void)
{

}

void CShPluginPlatformer::Initialize(void)
{

}

void CShPluginPlatformer::Release(void)
{

}

/*virtual*/ void CShPluginPlatformer::OnPlayStart(const CShIdentifier & levelIdentifier)
{
	m_camera.Initialize();

	//
	// Create a world with gravity
	b2Vec2 gravity;
	gravity.Set(0.0f, -9.8f);
	m_pWorld = new b2World(gravity);

	b2Body *pBody = shNULL;
	CShArray<ShEntity2 *> aEntities;

	ShEntity2::GetEntity2Array(levelIdentifier, aEntities);

	int nEntityCount = aEntities.GetCount();
	for (int nEntity = 0; nEntity < nEntityCount; ++nEntity)
	{
		int iDataSetCount = ShObject::GetDataSetCount(aEntities[nEntity]);

		//
		//Generate all body
		for (int nDataSet = 0; nDataSet < iDataSetCount; ++nDataSet)
		{
			ShDataSet * pDataSet = ShObject::GetDataSet(aEntities[nEntity], nDataSet);

			CShIdentifier idDataSetIdentifier = ShDataSet::GetDataSetIdentifier(pDataSet);

			if (CShIdentifier("player") == idDataSetIdentifier)
			{
				int iDataCount = ShDataSet::GetDataCount(pDataSet);

				ShObject* pShape = shNULL;
				const CShVector2 vPosition = ShObject::GetPosition2(aEntities[nEntity]);
				const float fWidth = ShEntity2::GetWidth(aEntities[nEntity]);
				const float fHeight = ShEntity2::GetHeight(aEntities[nEntity]);
				const b2BodyType b2Type = b2_dynamicBody;
				const int iCategoryBits = GameObject::e_type_player;
				const int iMaskBits = 255;
				const bool isSensor = false;

				for (int nData = 0; nData < iDataCount; ++nData)
				{
					CShIdentifier dataIdentifier = ShDataSet::GetDataIdentifier(pDataSet, nData);

					if (dataIdentifier == CShIdentifier("shape"))
					{
						ShDataSet::GetDataValue(pDataSet, nData, &pShape);
					}
				}

				pBody = CreateBodyShape(vPosition, fWidth, fHeight, b2Type, iCategoryBits, iMaskBits, isSensor);
				m_aBody.Add(pBody);
				m_pPlayer = new GameObjectPlayer(pBody, aEntities[nEntity]);
			}
			else if(CShIdentifier("enemy") == idDataSetIdentifier)
			{
				int iDataCount = ShDataSet::GetDataCount(pDataSet);

				ShObject* pShape = shNULL;
				const CShVector2 vPosition = ShObject::GetPosition2(aEntities[nEntity]);
				const float fWidth = ShEntity2::GetWidth(aEntities[nEntity]);
				const float fHeight = ShEntity2::GetHeight(aEntities[nEntity]);
				const b2BodyType b2Type = b2_dynamicBody;
				const int iCategoryBits = GameObject::e_type_enemy;
				const int iMaskBits = 255;
				const bool isSensor = false;

				for (int nData = 0; nData < iDataCount; ++nData)
				{
					CShIdentifier dataIdentifier = ShDataSet::GetDataIdentifier(pDataSet, nData);

					if (dataIdentifier == CShIdentifier("shape"))
					{
						ShDataSet::GetDataValue(pDataSet, nData, &pShape);
					}
				}

				pBody = CreateBodyShape(vPosition, fWidth, fHeight, b2Type, iCategoryBits, iMaskBits, isSensor);
				m_aBody.Add(pBody);
				m_aEnemy.Add(new GameObjectEnemy(pBody, aEntities[nEntity]));
			}
			else if (CShIdentifier("platform") == idDataSetIdentifier)
			{
				int iDataCount = ShDataSet::GetDataCount(pDataSet);
				ShObject* pShape = shNULL;
				const CShVector2 vPosition = ShObject::GetPosition2(aEntities[nEntity]);
				const float fWidth = ShEntity2::GetWidth(aEntities[nEntity]);
				const float fHeight = ShEntity2::GetHeight(aEntities[nEntity]);
				const b2BodyType b2Type = b2_staticBody;
				const int iCategoryBits = GameObject::e_type_platform;
				const int iMaskBits = 255;
				const bool isSensor = false;

				for (int nData = 0; nData < iDataCount; ++nData)
				{
					CShIdentifier dataIdentifier = ShDataSet::GetDataIdentifier(pDataSet, nData);

					if (dataIdentifier == CShIdentifier("shape"))
					{
						ShDataSet::GetDataValue(pDataSet, nData, &pShape);
					}
				}

				pBody = CreateBodyShape(vPosition, fWidth, fHeight, b2Type, iCategoryBits, iMaskBits, isSensor);
				m_aBody.Add(pBody);
				m_aPlatform.Add(new GameObjectPlatform(pBody, aEntities[nEntity]));
			}
		}
	}

	SH_ASSERT(shNULL != pBody)

	m_camera.FollowObject(m_pPlayer->GetEntity());
}

/*virtual*/ void CShPluginPlatformer::OnPlayStop(const CShIdentifier & levelIdentifier)
{
	SH_SAFE_DELETE(m_pPlayer);

	int iEnemyCount = m_aEnemy.GetCount();
	for (int nEnemy = 0; nEnemy < iEnemyCount; ++nEnemy)
	{
		GameObjectEnemy * pEnemy = m_aEnemy[nEnemy]; 
		SH_SAFE_DELETE(pEnemy);
	}

	int iPlatformCount = m_aPlatform.GetCount();
	for (int nPlatform = 0; nPlatform < iPlatformCount; ++nPlatform)
	{
		GameObjectPlatform * pPlatform = m_aPlatform[nPlatform]; 
		SH_SAFE_DELETE(pPlatform);
	}

	int iBodyCount = m_aBody.GetCount();
	for (int nBody = 0; nBody < iBodyCount; ++nBody)
	{
		b2Body* pBody = m_aBody[nBody];
		m_pWorld->DestroyBody(pBody);
	}

	m_aBody.Empty();
	SH_SAFE_DELETE(m_pWorld);
}

/*virtual*/ void CShPluginPlatformer::OnPlayPause(const CShIdentifier & levelIdentifier)
{

}

/*virtual*/ void CShPluginPlatformer::OnPlayResume(const CShIdentifier & levelIdentifier)
{

}

/*virtual*/ void CShPluginPlatformer::OnPreUpdate(void)
{

}

/*virtual*/ void CShPluginPlatformer::OnPostUpdate(float dt)
{
	m_camera.Update(dt);

	//
	// Update the world of Box2D 
	m_pWorld->Step(dt, 3, 3);


	m_pPlayer->Update(dt);

	int iEnemyCount = m_aEnemy.GetCount();
	for (int nEnemy = 0; nEnemy < iEnemyCount; ++nEnemy)
	{
		GameObjectEnemy * pEnemy = m_aEnemy[nEnemy]; 
		pEnemy->Update(dt);
	}

	int iPlatformCount = m_aPlatform.GetCount();
	for (int nPlatform = 0; nPlatform < iPlatformCount; ++nPlatform)
	{
		GameObjectPlatform * pPlatform = m_aPlatform[nPlatform]; 
		pPlatform->Update(dt);
	}
}

b2Body* CShPluginPlatformer::CreateBodyCircle(const CShVector2 & position, float radius, b2BodyType type, unsigned int categoryBits, unsigned int maskBits, bool isBullet, bool isSensor)
{
	b2Vec2 pos = convert_Sh_b2(position);

	// Create Body
	b2Body * pBody = NULL;
	{
		b2BodyDef bd;
		bd.bullet = isBullet;
		bd.type = type;
		bd.position.x = pos.x;
		bd.position.y = pos.y;
		pBody = m_pWorld->CreateBody(&bd);
	}

	{
		// Create Shape
		b2CircleShape shape;
		shape.m_p.Set(0, 0);
		shape.m_radius = radius / RATIO_B2_SH;

		// Associate Shape to Body
		b2FixtureDef fd;
		fd.shape = &shape;
		fd.density = 100.0f;
		fd.filter.categoryBits = categoryBits;
		fd.filter.maskBits = maskBits;
		fd.isSensor = isSensor;

		pBody->CreateFixture(&fd);
	}

	return(pBody);
}

b2Body* CShPluginPlatformer::CreateBodyShape(const CShVector2 & position, float fWidth, float fHeight, b2BodyType type, unsigned int categoryBits, unsigned int maskBits, bool isSensor)
{
	b2Vec2 pos = convert_Sh_b2(position);

	// Create Body
	b2Body * pBody = NULL;
	{
		b2BodyDef bd;
		bd.type = type;
		bd.position.x = pos.x;
		bd.position.y = pos.y;
		pBody = m_pWorld->CreateBody(&bd);
	}

	{
		b2PolygonShape shape;
		shape.SetAsBox(fWidth * 0.5f / RATIO_B2_SH, fHeight * 0.5f / RATIO_B2_SH);

		// Associate Shape to Body
		b2FixtureDef fd;
		fd.shape = &shape;
		fd.density = 100.0f;
		fd.isSensor = isSensor;
		fd.filter.categoryBits = categoryBits;
		fd.filter.maskBits = maskBits;

		pBody->CreateFixture(&fd);
	}

	return pBody;
}
