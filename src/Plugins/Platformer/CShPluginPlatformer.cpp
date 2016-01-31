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

bool CShPluginPlatformer::RestartGame(void)
{
	return m_bRestartGame;
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
	m_pContactListener->Initialize(this);
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

					b2Body * pBody = CreateBodyBox(vPosition, fWidth, fHeight, b2_dynamicBody, 0.0f, GameObject::e_type_player, 255, false);
					m_aBody.Add(pBody);
					m_pPlayer = new GameObjectPlayer(this, pBody, aEntities[nEntity]);
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

					b2Body * pBody = CreateBodyBox(vPosition, fWidth, fHeight, b2_dynamicBody, 0.5f, GameObject::e_type_enemy, 255, false);
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

					b2Body * pBody = CreateBodyBox(vPosition, fWidth, fHeight, b2_staticBody, 0.1f, GameObject::e_type_platform, 255, false);
					m_aBody.Add(pBody);
					m_aPlatform.Add(new GameObjectPlatform(pBody, aEntities[nEntity]));
				}
			}
			else if(CShIdentifier("pike") == idDataSetIdentifier)
			{
				// Find AABB2
				ShDummyAABB2 * pShape = shNULL;
				{
					int iDataCount = ShDataSet::GetDataCount(pDataSet);

					for (int nData = 0; nData < iDataCount; ++nData)
					{
						const CShIdentifier & dataIdentifier = ShDataSet::GetDataIdentifier(pDataSet, nData);

						if (dataIdentifier == CShIdentifier("sensor"))
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

					b2Body * pBody = CreateBodyBox(vPosition, fWidth, fHeight, b2_staticBody, 1.0f, GameObject::e_type_pike, GameObject::e_type_player, true);
					m_aBody.Add(pBody);
					m_aPike.Add(new GameObjectPike(this, pBody, aEntities[nEntity]));
				}
			}
			else if(CShIdentifier("rock") == idDataSetIdentifier)
			{
				ShDummyAABB2 * pShape = shNULL;
				{
					int iDataCount = ShDataSet::GetDataCount(pDataSet);

					for (int nData = 0; nData < iDataCount; ++nData)
					{
						const CShIdentifier & dataIdentifier = ShDataSet::GetDataIdentifier(pDataSet, nData);

						if (dataIdentifier == CShIdentifier("circle"))
						{
							ShDataSet::GetDataValue(pDataSet, nData, (ShObject**)&pShape);
						}
					}
				}

				if (shNULL != pShape)
				{
					ShDummyCircle * pCircle = (ShDummyCircle *)pShape;

					const CShVector2 & vPosition = ShDummyCircle::GetPosition2(pCircle);
					float fRadius = 0.5f * ShEntity2::GetWidth(aEntities[nEntity]); //ShDummyCircle::GetCircle(pCircle).GetRadius();
					b2Body * pBody = CreateBodyCircle(vPosition, fRadius, b2_dynamicBody, 0.8f, GameObject::e_type_rock, GameObject::e_type_player, false, false);
					m_aBody.Add(pBody);
					m_aRock.Add(new GameObjectRock(pBody, aEntities[nEntity]));
				}
			}
			else if(CShIdentifier("spear") == idDataSetIdentifier)
			{
				ShDummyAABB2 * pShapePike = shNULL;
				ShDummyAABB2 * pShapeHandle = shNULL;

				{
					int iDataCount = ShDataSet::GetDataCount(pDataSet);

					for (int nData = 0; nData < iDataCount; ++nData)
					{
						const CShIdentifier & dataIdentifier = ShDataSet::GetDataIdentifier(pDataSet, nData);

						if (dataIdentifier == CShIdentifier("pike"))
						{
							ShDataSet::GetDataValue(pDataSet, nData, (ShObject**)&pShapePike);
						}
						else if(dataIdentifier == CShIdentifier("handle"))
						{
							ShDataSet::GetDataValue(pDataSet, nData, (ShObject**)&pShapeHandle);
						}
					}
				}

				if (shNULL != pShapePike && shNULL != pShapeHandle)
				{
					//for (int i = 0; i < 1.; ++i)
					//{
						b2Body * pBody = CreateSpear(pShapePike, pShapeHandle);
						m_aSpear.Add(new GameObjectSpear(pBody, aEntities[nEntity]));
					//}

				}
			}
		}
	}

	m_pPlayer->Initialize(levelIdentifier);

	m_aSpear[m_iCurrentSpear]->SetState(GameObjectSpear::e_state_on, 1920.0f);

	m_iCurrentSpear = 0;
	m_bPaused = false;

}

/*virtual*/ void CShPluginPlatformer::OnPlayStop(const CShIdentifier & levelIdentifier)
{
	int iBodyCount = m_aBody.GetCount();
	for (int nBody = 0; nBody < iBodyCount; ++nBody)
	{
		b2Body* pBody = m_aBody[nBody];
		m_pWorld->DestroyBody(pBody);
	}

	m_pPlayer->Release();
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

	for (int nPike = 0; nPike < m_aPike.GetCount(); ++nPike)
	{
		SH_SAFE_DELETE(m_aPike[nPike]);
	}

	m_aPike.Empty();

	for (int nRock = 0; nRock < m_aRock.GetCount(); ++nRock)
	{
		SH_SAFE_DELETE(m_aRock[nRock]);
	}

	m_aRock.Empty();

	for (int nSpear = 0; nSpear < m_aSpear.GetCount(); ++nSpear)
	{
		SH_SAFE_DELETE(m_aSpear[nSpear]);
	}

	m_aSpear.Empty();

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

	int iRockCount = m_aRock.GetCount();
	for (int nRock = 0; nRock < iRockCount; ++nRock)
	{
		GameObjectRock * pRock = m_aRock[nRock];
		pRock->Update(dt);
	}

	m_fSpearTime += dt;

	if (m_aSpear[m_iCurrentSpear]->GetBody()->GetPosition().x * RATIO_B2_SH < center.m_x - 1920.0f)
	{
		m_aSpear[m_iCurrentSpear]->SetState(GameObjectSpear::e_state_off, center.m_x);
		//m_iCurrentSpear++;
		//m_iCurrentSpear %= m_aSpear.GetCount();
		m_aSpear[m_iCurrentSpear]->SetState(GameObjectSpear::e_state_on, center.m_x);
		m_fSpearTime = 0.0f;
	}

	m_aSpear[m_iCurrentSpear]->Update(dt);

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
		p1.y = point1.m_y / RATIO_B2_SH;

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

b2Body * CShPluginPlatformer::CreateSpear(ShDummyAABB2 * pShapePike, ShDummyAABB2 * pShapeSpear)
{
	//pike
	const CShVector2 & vPikePosition = ShDummyAABB2::GetPosition2(pShapePike);
	const CShAABB2 & pikeAabb = ShDummyAABB2::GetAABB(pShapePike);
	const CShVector2 & pikeMinPoint = pikeAabb.GetMin();
	const CShVector2 & pikeMaxPoint = pikeAabb.GetMax();
	const CShVector3 & pikeScale = ShDummyAABB2::GetScale(pShapePike);
	const float fPikeWidth = shAbsf(pikeMaxPoint.m_x - pikeMinPoint.m_x) * pikeScale.m_x;
	const float fPikeHeight = shAbsf(pikeMaxPoint.m_y - pikeMinPoint.m_y) * pikeScale.m_y;

	//spear
	const CShVector2 & vPosition = ShDummyAABB2::GetPosition2(pShapeSpear);
	const CShAABB2 & aabb = ShDummyAABB2::GetAABB(pShapeSpear);
	const CShVector2 & minPoint = aabb.GetMin();
	const CShVector2 & maxPoint = aabb.GetMax();
	const CShVector3 & scale = ShDummyAABB2::GetScale(pShapeSpear);
	const float fWidth = shAbsf(maxPoint.m_x - minPoint.m_x) * scale.m_x;
	const float fHeight = shAbsf(maxPoint.m_y - minPoint.m_y) * scale.m_y;

	b2Vec2 pos = convert_Sh_b2(vPosition);

	// Create Body
	b2Body * pBody = NULL;
	{
		b2BodyDef bd;
		bd.type = b2_kinematicBody;
		bd.fixedRotation = true;
		bd.position.x = pos.x;
		bd.position.y = pos.y;
		pBody = m_pWorld->CreateBody(&bd);
	}

	//pike
	{
		b2PolygonShape pikeShape;
		pikeShape.SetAsBox(fPikeWidth * 0.5f / RATIO_B2_SH, fPikeHeight * 0.5f / RATIO_B2_SH, convert_Sh_b2(vPikePosition) - pos, 0);
		b2FixtureDef fd;
		fd.shape = &pikeShape;
		fd.density = 20.0f;
		fd.friction = 0.1f;
		fd.isSensor = false;
		fd.filter.categoryBits = GameObject::e_type_spear;
		fd.userData = (void*)1;
		fd.filter.maskBits = GameObject::e_type_player;

		pBody->CreateFixture(&fd);
	}
	
	//spear
	{
		b2PolygonShape spearShape;
		spearShape.SetAsBox(fWidth * 0.5f / RATIO_B2_SH, fHeight * 0.5f / RATIO_B2_SH);

		b2FixtureDef fd;
		fd.shape = &spearShape;
		fd.density = 20.0f;
		fd.friction = 0.0f;
		fd.isSensor = false;
		fd.filter.categoryBits = GameObject::e_type_spear;
		fd.filter.maskBits = GameObject::e_type_player;

		pBody->CreateFixture(&fd);
	}

	m_aBody.Add(pBody);
	return pBody;
}

b2Body* CShPluginPlatformer::CreateBodyCircle(const CShVector2 & position, float radius, b2BodyType type, float fFriction, unsigned int categoryBits, unsigned int maskBits, bool isBullet, bool isSensor)
{
	b2Vec2 pos = convert_Sh_b2(position);

	// Create Body
	b2Body * pBody = NULL;
	{
		b2BodyDef bd;
		bd.bullet = isBullet;
		bd.fixedRotation = true;
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
		fd.density = 200.0f;
		fd.friction = fFriction;
		fd.filter.categoryBits = categoryBits;
		fd.filter.maskBits = maskBits;
		fd.isSensor = isSensor;

		pBody->CreateFixture(&fd);
	}

	return(pBody);
}

b2Body* CShPluginPlatformer::CreateBodyBox(const CShVector2 & position, float fWidth, float fHeight, b2BodyType type, float fFriction, unsigned int categoryBits, unsigned int maskBits, bool isSensor)
{
	b2Vec2 pos = convert_Sh_b2(position);

	// Create Body
	b2Body * pBody = NULL;
	{
		b2BodyDef bd;
		bd.type = type;
		bd.fixedRotation = true;
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
		fd.density = 20.0f;
		fd.friction = fFriction;
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
