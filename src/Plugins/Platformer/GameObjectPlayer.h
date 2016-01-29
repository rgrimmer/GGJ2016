#pragma once

//
/// @todo comment
class GameObjectPlayer : public GameObject
{

public:

	//
	// Construction / Destruction
	explicit			GameObjectPlayer			(b2Body * body, ShEntity2 * pEntity);
	virtual				~GameObjectPlayer			(void);

	void				SetState					(EState eState);
	EState				GetState					(void) const;

	void				Update						(void);

	virtual EType		GetType						(void) const;

protected:

private:

	void				UpdatePosition			(void);


public:

protected:

private:
public:
		
	EState				m_eState;				///< @todo comment
	ShEntity2*			m_pEntity;				///< @todo comment
};	

#endif // __CShPinballObjectBall_H
