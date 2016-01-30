#pragma once

class GameObjectSensor : public GameObject
{

public:

	enum EState
	{
		e_state_none
	};

	//
	// Construction / Destruction
	explicit			GameObjectSensor			(b2Body * body);
	virtual				~GameObjectSensor			(void);

	virtual EType		GetType						(void) const;

protected:

private:

public:

protected:

private:
public:
	
};	