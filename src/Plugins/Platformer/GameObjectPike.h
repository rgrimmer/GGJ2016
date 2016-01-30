#pragma once

class GameObjectPike : public GameObject
{

public:

	enum EState
	{
		e_state_none
	};

	//
	// Construction / Destruction
	explicit			GameObjectPike				(b2Body * body, ShEntity2 * pEntity);
	virtual				~GameObjectPike				(void);

	virtual EType		GetType						(void) const;

	void				Start						(void);
	void				End							(void);

protected:

private:

public:

protected:

private:
	ShEntity2*			m_pEntity;
public:
	
};	