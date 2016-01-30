#pragma once

//
/// @todo comment
class GameObjectPlayer : public GameObject
{

public:

	enum EAction
	{
		e_action_move_left,
		e_action_move_right,
		e_action_jump,
		e_action_max
	};

	struct ActionBinding
	{
		CShArray<ShInput*> m_aKeyInputs;
		CShArray<ShInput*> m_aLeftJoystickInputs;
		CShArray<ShInput*> m_aRightJoystickInputs;
	};

	enum EJumpState
	{
		e_jump_state_none,
		e_jump_state_simple,
		e_jump_state_double
	};

	//
	// Construction / Destruction
	explicit			GameObjectPlayer			(b2Body * body, ShEntity2 * pEntity);
	virtual				~GameObjectPlayer			(void);

	void				Update						(float dt);

	virtual EType		GetType						(void) const;
	ShEntity2 *			GetEntity					(void) const;

	bool				CheckAction					(EAction eAction) const;

protected:

private:

public:

protected:

private:
public:

	EJumpState			m_eJumpState;				///< @todo comment

	ShEntity2 *			m_pEntity;				///< @todo comment

	ActionBinding		m_aActions [e_action_max];
};
