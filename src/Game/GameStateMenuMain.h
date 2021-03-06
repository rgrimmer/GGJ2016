#pragma once

class GameStateMenuMain : public GameState
{
public:

	enum EInput
	{
		e_input_up,
		e_input_down,
		e_input_validate,
		e_input_cancel,
		e_input_max
	};

	enum EMenu
	{
		e_menu_play,
		e_menu_credits
	};

	//
	// Construction / Destruction
	explicit		GameStateMenuMain		(void);
	virtual			~GameStateMenuMain		(void);

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

	void			UpdateHighlightPosition (void);

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
	CShArray<ShTextZone *>	m_aTextZoneMenu;
	ShTextZone *			m_pTextZonePlay;
	ShTextZone *			m_pTextZoneCredits;
	
	int						m_iMenuSelectedIndex;

	ShEntity2	*			m_pEntityHiglight;

	// menu inputs
	ShInput *				m_aInputs[e_input_max];
};