#pragma once

class GameCamera
{
public:

	//
	// Construction / Destruction
	explicit			GameCamera				(void);
	virtual				~GameCamera				(void);

	void				Initialize				(void);
	void				Release					(void);

	void				FollowObject			(ShObject * pObjectToFollow);

	void				Update					(float	dt);
protected:

private:

public:

protected:

private:
	ShCamera * m_pCamera;
	ShObject * m_pObjectToFollow;
};