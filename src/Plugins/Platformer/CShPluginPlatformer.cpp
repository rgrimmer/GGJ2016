#include "CShPluginPlatformer.h"

#include <Box2D/Box2D.h>

BEGIN_DERIVED_CLASS(CShPluginPlatformer, CShPlugin)
	// ...
END_CLASS()

CShPluginPlatformer::CShPluginPlatformer(void)
: CShPlugin(CShIdentifier("Platformer"))
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
	b2Body *pBody = shNULL;
	CShArray<ShEntity2 *> aEntities;

	ShEntity2::GetEntity2Array(levelIdentifier, aEntities);

	int nEntityCount = aEntities.GetCount();
	for (int nEntity = 0; nEntity < nEntityCount; ++nEntityCount)
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
			}
		}
	}

	SH_ASSERT(shNULL != pBody)
}

/*virtual*/ void CShPluginPlatformer::OnPlayStop(const CShIdentifier & levelIdentifier)
{

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
