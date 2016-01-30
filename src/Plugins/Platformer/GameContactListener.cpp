#include "CShPluginPlatformer.h"

//--------------------------------------------------------------------------------------------------
/// @todo comment
//--------------------------------------------------------------------------------------------------
void GameContactListener::Initialize(CShIdentifier levelIdentifier)
{

}

//--------------------------------------------------------------------------------------------------
/// @todo comment
//--------------------------------------------------------------------------------------------------
void GameContactListener::Release(void)
{

}

//--------------------------------------------------------------------------------------------------
/// @todo comment
//--------------------------------------------------------------------------------------------------
void GameContactListener::Update(float dt)
{
	
}


//--------------------------------------------------------------------------------------------------
/// @todo comment
//--------------------------------------------------------------------------------------------------
void GameContactListener::BeginContact(b2Contact* contact)
{
	GameObject * objectA = static_cast<GameObject *>(contact->GetFixtureA()->GetBody()->GetUserData());
	GameObject * objectB = static_cast<GameObject *>(contact->GetFixtureB()->GetBody()->GetUserData());

	if (NULL != objectA)
	{
		CollisionStart(contact, objectA);
	}
	
	if (NULL != objectB)
	{
		CollisionStart(contact, objectB);
	}
}

//--------------------------------------------------------------------------------------------------
/// @todo comment
//--------------------------------------------------------------------------------------------------
void GameContactListener::EndContact(b2Contact* contact)
{
	GameObject * objectA = static_cast<GameObject *>(contact->GetFixtureA()->GetBody()->GetUserData());
	GameObject * objectB = static_cast<GameObject *>(contact->GetFixtureB()->GetBody()->GetUserData());

	if (NULL != objectA)
	{
		CollisionEnd(contact, objectA);
	}
	
	if (NULL != objectB)
	{
		CollisionEnd(contact, objectB);
	}
}

//--------------------------------------------------------------------------------------------------
/// @todo comment
//--------------------------------------------------------------------------------------------------
void GameContactListener::CollisionStart(b2Contact * contact, GameObject * object)
{
	b2WorldManifold worldManifold;
	contact->GetWorldManifold(&worldManifold);

	switch (object->GetType())
	{
		case GameObject::e_type_enemy:
		{
			if (static_cast<GameObject *>(contact->GetFixtureA()->GetBody()->GetUserData())->GetType() == GameObject::e_type_sensor)
			{
				static_cast<GameObjectEnemy *>(object)->ToggleDirection();
			}
			else if(static_cast<GameObject *>(contact->GetFixtureB()->GetBody()->GetUserData())->GetType() == GameObject::e_type_sensor)
			{
				static_cast<GameObjectEnemy *>(object)->ToggleDirection();
			}
		}
		break;

		case GameObject::e_type_pike:
		{
			if (static_cast<GameObject *>(contact->GetFixtureA()->GetBody()->GetUserData())->GetType() == GameObject::e_type_player)
			{
				static_cast<GameObjectPike *>(object)->Start();
			}
			else if(static_cast<GameObject *>(contact->GetFixtureB()->GetBody()->GetUserData())->GetType() == GameObject::e_type_player)
			{
				static_cast<GameObjectPike *>(object)->Start();
			}		
		}
		break;

		case GameObject::e_type_sensor:
		{

		}
		break;
	}
}

//--------------------------------------------------------------------------------------------------
/// @todo comment
//--------------------------------------------------------------------------------------------------
void GameContactListener::CollisionEnd(b2Contact * contact, GameObject * object)
{
	b2WorldManifold worldManifold;
	contact->GetWorldManifold(&worldManifold);

	switch (object->GetType())
	{
		case GameObject::e_type_pike:
		{
			if (static_cast<GameObject *>(contact->GetFixtureA()->GetBody()->GetUserData())->GetType() == GameObject::e_type_player)
			{
				static_cast<GameObjectPike *>(object)->End();
			}
			else if(static_cast<GameObject *>(contact->GetFixtureB()->GetBody()->GetUserData())->GetType() == GameObject::e_type_player)
			{
				static_cast<GameObjectPike *>(object)->End();
			}		
		}
		break;

		case GameObject::e_type_sensor:
		{

		}
		break;
	}
}

//--------------------------------------------------------------------------------------------------
/// @todo comment
//--------------------------------------------------------------------------------------------------
void GameContactListener::PreSolve(b2Contact * contact, const b2Manifold * oldManifold)
{

}

//--------------------------------------------------------------------------------------------------
/// @todo comment
//--------------------------------------------------------------------------------------------------
void GameContactListener::PostSolve(b2Contact * contact, const b2ContactImpulse * impulse)
{

}