#pragma once

class GameStateGame : public GameState
{
public:

	enum EState
	{
		e_state_intro,
		e_state_smoke,
		e_state_play
	};

	//
	// Construction / Destruction
	explicit		GameStateGame		(void);
	virtual			~GameStateGame		(void);

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


	void			SetState				(EState state);

protected:

private:

	void			Activate				(void);
	void			DeActivate				(void);

public:

protected:

	struct SmokeParticle
	{
		ShEntity2 * pEntity;
		float startTime;
		float duration;
	};

private:

	EState							m_eState;
	float							m_fStateTime;

	CShArray<SmokeParticle>			m_aEntitySmoke;

	ShEntity2 *						m_pEntityPlayerDead;

};
