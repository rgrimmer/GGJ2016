#pragma once

class GameBackground
{

public:

	//
	// Construction / Destruction
	explicit			GameBackground			(void);
	virtual				~GameBackground			(void);

	void				Initialize				(const CShIdentifier & levelIdentifier);
	void				Release					(void);

	void				Update					(float	dt, const CShVector2 & center);

private:

	ShEntity2 * m_pBackgroundEntity;
};
