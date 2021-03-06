#pragma once

class GameCamera
{
public:

	//
	// Construction / Destruction
	explicit			GameCamera				(void);
	virtual				~GameCamera				(void);

	void				Initialize				(const CShIdentifier & levelIdentifier);
	void				Release					(void);

	void				Update					(float	dt, const CShVector2 & center);

protected:

private:

public:

protected:

private:

	ShCamera * m_pCamera;

};
