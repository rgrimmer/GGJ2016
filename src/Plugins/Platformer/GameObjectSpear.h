#pragma once

class GameObjectSpear : public GameObject
{

public:

	enum EState
	{
		e_state_on,
		e_state_off,
		e_state_none
	};

	//
	// Construction / Destruction
	explicit			GameObjectSpear				(b2Body * body, ShEntity2 * pEntity);
	virtual				~GameObjectSpear			(void);

	void				SetState					(EState eState, float fCameraCenter);
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
