#pragma once

class GameStateMenuMain : public GameState
{
public:

	//
	// Construction / Destruction
	explicit		GameStateMenuMain		(void);
	virtual			~GameStateMenuMain		(void);

	//
	// Initialization / Release / Activation / Deactivation
	virtual void	Initialize				(void);
	virtual void	Release					(void);
	virtual void	Activate				(void);
	virtual void	DeActivate				(void);

	//
	// Update
	void			Update					(float dt);

	//
	// Events
	virtual void	OnTouchDown				(int iTouch, float positionX, float positionY);
	virtual void	OnTouchUp				(int iTouch, float positionX, float positionY);
	virtual void	OnTouchMove				(int iTouch, float positionX, float positionY);

protected:

private:

public:

protected:

private:

};