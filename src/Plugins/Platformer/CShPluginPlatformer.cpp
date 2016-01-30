#include "CShPluginPlatformer.h"

#include <Box2D/Box2D.h>

static const b2Vec2 gravity(0.0f, -9.8f);

BEGIN_DERIVED_CLASS(CShPluginPlatformer, CShPlugin)
	// ...
END_CLASS()

CShPluginPlatformer::CShPluginPlatformer(void)
: CShPlugin(CShIdentifier("Platformer"))
, m_pWorld(shNULL)
, m_aBody()
, m_bPaused(false)
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
	m_camera.Initialize(levelIdentifier);
	m_background.Initialize(levelIdentifier);

	ShScriptTree * pScriptTree = LoadConfig(levelIdentifier);

	ShScriptTreeNode * pRootNode = ShScriptTree::GetRootNode(pScriptTree);

	int childCount = ShScriptTreeNode::GetChildCount(pRootNode);

	for (int i = 0; i < childCount; ++i)
	{
		ShScriptTreeNode * pNode = ShScriptTreeNode::GetChild(pRootNode, i);
		const CShIdentifier & identifier = ShScriptTreeNode::GetIdentifier(pNode);

		if (CShIdentifier("parallax") == identifier)
		{
			m_background.LoadParallax(levelIdentifier, pNode);
		}
	}

	//
	// Create the Box2D world
	m_pWorld = new b2World(gravity);
	SH_ASSERT(shNULL != m_pWorld);

	//
	//Create contact listener
	m_pContactListener = new GameContactListener();
	m_pWorld->SetContactListener(m_pContactListener);

	//
	// Get all 2D entities
	CShArray<ShEntity2 *> aEntities;
	ShEntity2::GetEntity2Array(levelIdentifier, aEntities);

	//
	// Loop through all entities
	int nEntityCount = aEntities.GetCount();
	for (int nEntity = 0; nEntity < nEntityCount; ++nEntity)
	{
		int iDataSetCount = ShObject::GetDataSetCount(aEntities[nEntity]);

		//
		// Generate all body
		for (int nDataSet = 0; nDataSet < iDataSetCount; ++nDataSet)
		{
			ShDataSet * pDataSet = ShObject::GetDataSet(aEntities[nEntity], nDataSet);

			CShIdentifier idDataSetIdentifier = ShDataSet::GetDataSetIdentifier(pDataSet);

			if (CShIdentifier("player") == idDataSetIdentifier)
			{
				// Find Shape
				ShDummyAABB2 * pShape = shNULL;
				{
					int iDataCount = ShDataSet::GetDataCount(pDataSet);

					for (int nData = 0; nData < iDataCount; ++nData)
					{
						CShIdentifier dataIdentifier = ShDataSet::GetDataIdentifier(pDataSet, nData);

						if (dataIdentifier == CShIdentifier("shape"))
						{
							ShDataSet::GetDataValue(pDataSet, nData, (ShObject**)&pShape);
						}
					}
				}

				// Create body from shape
				if (shNULL != pShape)
				{
					const CShVector2 & vPosition = ShDummyAABB2::GetPosition2(pShape);
					const CShAABB2 & aabb = ShDummyAABB2::GetAABB(pShape);
					const CShVector2 & minPoint = aabb.GetMin();
					const CShVector2 & maxPoint = aabb.GetMax();
					const CShVector3 & scale = ShDummyAABB2::GetScale(pShape);

					const float fWidth = shAbsf(maxPoint.m_x - minPoint.m_x) * scale.m_x;
					const float fHeight = shAbsf(maxPoint.m_y - minPoint.m_y) * scale.m_y;

					ShEntity2::SetShow(aEntities[nEntity], false);

					b2Body * pBody = CreateBodyBox(vPosition, fWidth, fHeight, b2_dynamicBody, GameObject::e_type_player, 255, false);
					m_aBody.Add(pBody);
					m_pPlayer = new GameObjectPlayer(pBody, aEntities[nEntity]);
				}
			}
			else if(CShIdentifier("enemy") == idDataSetIdentifier)
			{
				// Find Shape
				ShObject * pShape = shNULL;
				ShObject * pCollisionSegmentLeft = shNULL;
				ShObject * pCollisionSegmentRight = shNULL;

				{
					int iDataCount = ShDataSet::GetDataCount(pDataSet);

					for (int nData = 0; nData < iDataCount; ++nData)
					{
						CShIdentifier dataIdentifier = ShDataSet::GetDataIdentifier(pDataSet, nData);

						if (dataIdentifier == CShIdentifier("shape"))
						{
							ShDataSet::GetDataValue(pDataSet, nData, &pShape);
						}
						else if(dataIdentifier == CShIdentifier("Limit_left"))
						{
							ShDataSet::GetDataValue(pDataSet, nData, &pCollisionSegmentLeft);

							ShObject * pCollisionObject = ShCollisionSegment::GetPoint1((ShCollisionSegment*)pCollisionSegmentLeft);

							b2Body* pBody = CreateBodySegment(CShVector2(ShObject::GetWorldTM(pCollisionObject).getTranslation().m_x, ShObject::GetWorldTM(pCollisionObject).getTranslation().m_y),
																CShVector2(ShObject::GetWorldTM(pCollisionObject).getTranslation().m_x, ShObject::GetWorldTM(pCollisionObject).getTranslation().m_y),
																b2_staticBody,
																GameObject::e_type_sensor,
																GameObject::e_type_enemy,
																false,
																true);

							m_aSensor.Add(new GameObjectSensor(pBody));
						}
						else if(dataIdentifier == CShIdentifier("Limit_right"))
						{
							ShDataSet::GetDataValue(pDataSet, nData, &pCollisionSegmentRight);

							ShObject * pCollisionObject = ShCollisionSegment::GetPoint1((ShCollisionSegment*)pCollisionSegmentRight);

							b2Body* pBody = CreateBodySegment(CShVector2(ShObject::GetWorldTM(pCollisionObject).getTranslation().m_x, ShObject::GetWorldTM(pCollisionObject).getTranslation().m_y),
																CShVector2(ShObject::GetWorldTM(pCollisionObject).getTranslation().m_x, ShObject::GetWorldTM(pCollisionObject).getTranslation().m_y),
																b2_staticBody,
																GameObject::e_type_sensor,
																GameObject::e_type_enemy,
																false,
																true);

							m_aSensor.Add(new GameObjectSensor(pBody));
						}
					}
				}

				// Create body from shape
				if (shNULL != pShape)
				{
					const CShVector2 & vPosition = ShObject::GetPosition2(aEntities[nEntity]);
					const float fWidth = ShEntity2::GetWidth(aEntities[nEntity]);
					const float fHeight = ShEntity2::GetHeight(aEntities[nEntity]);

					b2Body * pBody = CreateBodyBox(vPosition, fWidth, fHeight, b2_dynamicBody, GameObject::e_type_enemy, 255, false);
					m_aBody.Add(pBody);
					m_aEnemy.Add(new GameObjectEnemy(pBody, aEntities[nEntity]));
				}
			}
			else if (CShIdentifier("platform") == idDataSetIdentifier)
			{
				// Find AABB2
				ShDummyAABB2 * pShape = shNULL;
				{
					int iDataCount = ShDataSet::GetDataCount(pDataSet);

					for (int nData = 0; nData < iDataCount; ++nData)
					{
						const CShIdentifier & dataIdentifier = ShDataSet::GetDataIdentifier(pDataSet, nData);

						if (dataIdentifier == CShIdentifier("box"))
						{
							ShDataSet::GetDataValue(pDataSet, nData, (ShObject**)&pShape);
						}
					}
				}

				// Create body from AABB2
				if (shNULL != pShape)
				{
					const CShVector2 & vPosition = ShDummyAABB2::GetPosition2(pShape);
					const CShAABB2 & aabb = ShDummyAABB2::GetAABB(pShape);
					const CShVector2 & minPoint = aabb.GetMin();
					const CShVector2 & maxPoint = aabb.GetMax();
					const CShVector3 & scale = ShDummyAABB2::GetScale(pShape);

					const float fWidth = shAbsf(maxPoint.m_x - minPoint.m_x) * scale.m_x;
					const float fHeight = shAbsf(maxPoint.m_y - minPoint.m_y) * scale.m_y;

					b2Body * pBody = CreateBodyBox(vPosition, fWidth, fHeight, b2_staticBody, GameObject::e_type_platform, 255, false);
					m_aBody.Add(pBody);
					m_aPlatform.Add(new GameObjectPlatform(pBody, aEntities[nEntity]));
				}
			}
		}
	}

	m_pPlayer->Initialize(levelIdentifier);

	m_bPaused = false;

}

/*virtual*/ void CShPluginPlatformer::OnPlayStop(const CShIdentifier & levelIdentifier)
{
	SH_SAFE_DELETE(m_pPlayer);

	for (int nEnemy = 0; nEnemy < m_aEnemy.GetCount(); ++nEnemy)
	{
		SH_SAFE_DELETE(m_aEnemy[nEnemy]);
	}

	m_aEnemy.Empty();

	for (int nPlatform = 0; nPlatform < m_aPlatform.GetCount(); ++nPlatform)
	{
		SH_SAFE_DELETE(m_aPlatform[nPlatform]);
	}

	m_aPlatform.Empty();

	for (int nSensor = 0; nSensor < m_aSensor.GetCount(); ++nSensor)
	{
		SH_SAFE_DELETE(m_aSensor[nSensor]);
	}

	m_aSensor.Empty();

	int iBodyCount = m_aBody.GetCount();
	for (int nBody = 0; nBody < iBodyCount; ++nBody)
	{
		b2Body* pBody = m_aBody[nBody];
		m_pWorld->DestroyBody(pBody);
	}

	m_aBody.Empty();
	SH_SAFE_DELETE(m_pWorld);

	m_background.Release();
	m_camera.Release();
}

/*virtual*/ void CShPluginPlatformer::OnPlayPause(const CShIdentifier & levelIdentifier)
{

}

/*virtual*/ void CShPluginPlatformer::OnPlayResume(const CShIdentifier & levelIdentifier)
{

}

/*virtual*/ void CShPluginPlatformer::OnPreUpdate(void)
{
	if (m_bPaused)
	{
		return;
	}
}

/*virtual*/ void CShPluginPlatformer::OnPostUpdate(float dt)
{
	if (m_bPaused)
	{
		return;
	}

	CShVector2 center = ShEntity2::GetPosition2(m_pPlayer->GetEntity());

	if (center.m_x < 0.0f)
	{
		center.m_x = 0.0f;
	}

	m_camera.Update(dt, center);
	m_background.Update(dt, center);

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


b2Body* CShPluginPlatformer::CreateBodySegment(const CShVector2 & point1, const CShVector2 & point2, b2BodyType type, unsigned int categoryBits, unsigned int maskBits, bool isBullet, bool isSensor)
{
	// Create Body
	b2Body * pBody = NULL;
	{
		b2BodyDef bd;
		bd.bullet = isBullet;
		bd.type = type;
	//	bd.position.x = point1.m_x / RATIO_B2_SH;
	//	bd.position.y = 0.0f;
		pBody = m_pWorld->CreateBody(&bd);
	}

	{
		// Create Shape
		b2EdgeShape shape;
		b2Vec2 p1, p2;

		p1.x = point1.m_x / RATIO_B2_SH;
		p1.y = point1.m_x / RATIO_B2_SH;

		p2.x = point2.m_x / RATIO_B2_SH;
		p2.y = point2.m_y / RATIO_B2_SH;
		shape.Set(p1, p2);

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

b2Body* CShPluginPlatformer::CreateBodyBox(const CShVector2 & position, float fWidth, float fHeight, b2BodyType type, unsigned int categoryBits, unsigned int maskBits, bool isSensor)
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

ShScriptTree * CShPluginPlatformer::LoadConfig(const CShIdentifier & levelIdentifier)
{
	ShScriptTree * pScriptTree = ShScriptTree::Load(CShString("level_01.xml"));
	SH_ASSERT(shNULL != pScriptTree);

	ShScriptTreeNode * pRootNode = ShScriptTree::GetRootNode(pScriptTree);

	if (CShIdentifier("level") != ShScriptTreeNode::GetIdentifier(pRootNode))
	{
		ShScriptTree::Release(pScriptTree);

		return(shNULL);
	}

	return(pScriptTree);
}
