#pragma once

class Transition
{
public:

	enum EState
	{
		e_state_transition_in,
		e_state_transition_out,
		e_state_waiting,
		e_state_idle
	};

	//
	// Construction / Destruction
	explicit					Transition					(void);
	virtual						~Transition					(void);

	void						Initialize					(void);
	void						Release						(void);

	void						Update						(float dt);

	void						SetState					(EState eState);
	const EState				GetState					(void) const;
protected:

private:


public:

protected:

private:
	EState					m_eState;
	float					m_fStateTime;

	ShEntity2*				m_pEntityBackground;
};