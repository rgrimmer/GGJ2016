#pragma once

//
/// @todo comment
class GameObjectPlayer : public GameObject
{

public:

	enum EState
	{
		e_state_idle,
		e_state_running,
		e_state_jumping
	};

	enum EDirection
	{
		e_direction_right,
		e_direction_left
	};

	enum EAnimation
	{
		e_animation_idle,
		e_animation_run,
		e_animation_jump,
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

	//
	// Construction / Destruction
	explicit			GameObjectPlayer			(b2Body * body, ShEntity2 * pEntity);
	virtual				~GameObjectPlayer			(void);

	void				Initialize					(const CShIdentifier & levelIdentifier);
	void				Release						(void);

	void				Update						(float dt);

	void				SetState					(EState state);
	void				SetDirection				(EDirection direction);

	virtual EType		GetType						(void) const;
	ShEntity2 *			GetEntity					(void) const;

	bool				CheckAction					(EAction eAction) const;

protected:

private:

public:

protected:

private:
public:

	EState					m_eState;					///< @todo comment
	EDirection				m_eDirection;

	ShEntity2 *				m_pEntity;				///< @todo comment

	CShArray<ShEntity2*>	m_aAnimationEntity[e_animation_max];

	EAnimation				m_eCurrentAnimation;
	int						m_iCurrentAnimation;
	float					m_fAnimationTime;

	ActionBinding			m_aActions [e_action_max];

};
