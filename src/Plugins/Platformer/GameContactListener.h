#pragma once

class GameContactListener : public b2ContactListener
{

public:

	void			Initialize			(CShIdentifier levelIdentifier);
	void			Release				(void);

	void			Update				(float dt);

	virtual void	BeginContact		(b2Contact * contact);
	virtual void	EndContact			(b2Contact * contact);

	virtual void	PreSolve			(b2Contact * contact, const b2Manifold * oldManifold);
	virtual void	PostSolve			(b2Contact * contact, const b2ContactImpulse * impulse);

	void			CollisionCallback	(b2Contact * contact, GameObject * object);

private:

	CShIdentifier						m_levelIdentifier;
};