#pragma once

//
/// @todo comment
class GameObjectEnemy : public GameObject
{

public:

	enum EState
	{
		e_state_none
	};

	//
	// Construction / Destruction
	explicit			GameObjectEnemy				(b2Body * body, ShEntity2 * pEntity);
	virtual				~GameObjectEnemy			(void);

	void				SetState					(EState eState);
	EState				GetState					(void) const;

	void				Update						(float dt);

	void				ToggleDirection				(void);

	virtual EType		GetType						(void) const;

protected:

private:


public:

protected:

private:
public:

	EState				m_eState;				///< @todo comment
	ShEntity2*			m_pEntity;				///< @todo comment
	int					m_iDirection;			///< @todo comment
};
