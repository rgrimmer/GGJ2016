#pragma once

class GameState
{
public:

	//
	// Construction / Destruction
	explicit		GameState		(void);
	virtual			~GameState		(void);

	//
	// Initialization / Release / Activation / Deactivation
	virtual void	Initialize				(void) = 0;
	virtual void	Release					(void) = 0;

	virtual void	Obscuring				(void) = 0;
	virtual void	Revealed				(void) = 0;
	virtual void	Exiting					(void) = 0;
	virtual void	Entered					(void) = 0;

	//
	// Update
	void			Update					(void);

	//
	// Timer
	void			ResetActivationTime		(void);
	float			GetDelta				(void);

	//
	// Events
	virtual void	OnTouchDown				(int iTouch, float positionX, float positionY) = 0;
	virtual void	OnTouchUp				(int iTouch, float positionX, float positionY) = 0;
	virtual void	OnTouchMove				(int iTouch, float positionX, float positionY) = 0;

protected:

	virtual void	Update					(float deltaTimeInMs) = 0;

private:

public:

protected:

private:

	float	m_fLastUpdateTime;

};