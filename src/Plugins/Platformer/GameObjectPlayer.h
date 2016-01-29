#pragma once

//
/// @todo comment
class GameObjectPlayer : public GameObject
{

public:

	enum EInput
	{
		e_input_move_left,
		e_input_move_right,
		e_input_jump,
		e_input_max
	};

	enum EState
	{
		e_state_none
	};

	//
	// Construction / Destruction
	explicit			GameObjectPlayer			(b2Body * body, ShEntity2 * pEntity);
	virtual				~GameObjectPlayer			(void);

	void				SetState					(EState eState);
	EState				GetState					(void) const;

	void				Update						(void);

	virtual EType		GetType						(void) const;

protected:

private:

public:

protected:

private:
public:

	EState				m_eState;				///< @todo comment
	ShEntity2*			m_pEntity;				///< @todo comment
	ShInput *			m_aInputs[e_input_max]; ///< @todo comment
};
