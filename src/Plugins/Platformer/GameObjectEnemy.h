#pragma once

//
/// @todo comment
class GameObjectEnemy : public GameObject
{

public:

	//
	// Construction / Destruction
	explicit			GameObjectEnemy				(b2Body * body, ShEntity2 * pEntity);
	virtual				~GameObjectEnemy			(void);

	void				SetState					(EState eState);
	EState				GetState					(void) const;

	void				Update						(void);

	virtual EType		GetType						(void) const;

protected:

private:


public:

protected:

private:
public:
		
	EState				m_eState;				///< @todo comment
	ShEntity2*			m_pEntity;				///< @todo comment
};	

#endif // __CShPinballObjectBall_H
