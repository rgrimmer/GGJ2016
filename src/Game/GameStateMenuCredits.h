#pragma once

class GameStateMenuCredits : public GameState
{
public:

	//
	// Construction / Destruction
	explicit		GameStateMenuCredits		(void);
	virtual			~GameStateMenuCredits		(void);

	//
	// Initialization / Release / Activation / Deactivation
	virtual void	Initialize				(void);
	virtual void	Release					(void);

	virtual void	Obscuring				(void);
	virtual void	Revealed				(void);
	virtual void	Exiting					(void);
	virtual void	Entered					(void);
			
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
	void			Activate				(void);
	void			DeActivate				(void);
public:

protected:

private:
	ShTextZone * m_pTextZone;
};