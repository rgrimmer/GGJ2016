#pragma once

//
/// @todo comment
class GameObjectPlayer : public GameObject
{

public:

	enum EState
	{
		e_state_idle,
		e_state_move_right,
		e_state_move_left,
		e_state_jump
	};

	enum EAnimation
	{
		e_animation_idle,
		e_animation_max
	};

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

	void				Initialize					(const CShIdentifier & levelIdentifier);

	void				Update						(float dt);

	void				SetState					(EState state);

	virtual EType		GetType						(void) const;
	ShEntity2 *			GetEntity					(void) const;

	bool				CheckAction					(EAction eAction) const;

protected:

private:

public:

protected:

private:
public:

	EState				m_eState;					///< @todo comment
	EJumpState			m_eJumpState;				///< @todo comment

	ShEntity2 *			m_pEntity;				///< @todo comment

	CShArray<ShEntity2*>m_aAnimationEntity[e_animation_max];
	CShArray<ShEntity2*>m_apCurrentAnimation;
	int					m_iCurrentAnimation;
	float				m_fAnimationTime;

	ActionBinding		m_aActions [e_action_max];

};
