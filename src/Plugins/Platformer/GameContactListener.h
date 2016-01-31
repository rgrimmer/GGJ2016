#pragma once

class CShPluginPlatformer;
class GameContactListener : public b2ContactListener
{

public:

	void			Initialize			(CShPluginPlatformer * pGame);
	void			Release				(void);

	void			Update				(float dt);

	virtual void	BeginContact		(b2Contact * contact);
	virtual void	EndContact			(b2Contact * contact);

	virtual void	PreSolve			(b2Contact * contact, const b2Manifold * oldManifold);
	virtual void	PostSolve			(b2Contact * contact, const b2ContactImpulse * impulse);

	void			CollisionStart		(b2Contact * contact, GameObject * object);
	void			CollisionEnd		(b2Contact * contact, GameObject * object);
private:

	CShPluginPlatformer *				m_pGame;
	CShIdentifier						m_levelIdentifier;
};