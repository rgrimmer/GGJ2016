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
protected:

private:

public:

protected:

private:
	ShCamera * m_pCamera;
};