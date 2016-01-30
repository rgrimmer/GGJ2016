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
	explicit			GameObjectPike				(b2Body * body);
	virtual				~GameObjectPike				(void);

	virtual EType		GetType						(void) const;

protected:

private:

public:

protected:

private:
public:
	
};	