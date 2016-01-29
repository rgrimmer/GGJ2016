#pragma once

class GameObjectPlatform : public GameObject
{

public:

	enum EState
	{
		e_state_none
	};

	//
	// Construction / Destruction
	explicit			GameObjectPlatform			(b2Body * body, ShEntity2 * pEntity);
	virtual				~GameObjectPlatform			(void);

	void				SetState					(EState eState);
	EState				GetState					(void) const;

	void				Update						(float dt);

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