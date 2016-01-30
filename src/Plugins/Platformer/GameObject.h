#pragma once

class GameObject
{
public:

	//
	/// @todo comment
	enum EType
	{
		e_type_player = 1,			///< @todo comment
		e_type_enemy = 2,			///< @todo comment
		e_type_platform = 3,		///< @todo comment
		e_type_sensor = 4,
		e_type_pike = 5,
		e_type_rock = 6
	};

	//
	// Construction / Destruction
	explicit			GameObject				(b2Body * body);
	virtual				~GameObject				(void);

	virtual EType		GetType					(void) const = 0;

	b2Body *			GetBody					(void);

protected:

private:

public:

protected:

	b2Body *			m_pBody;

private:

};
