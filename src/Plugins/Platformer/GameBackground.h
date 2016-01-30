#pragma once

class GameBackground
{

public:

	struct Plane
	{
		float speed;
		CShArray<ShEntity2 *> aEntities;
	};

	//
	// Construction / Destruction
	explicit			GameBackground			(void);
	virtual				~GameBackground			(void);

	void				Initialize				(const CShIdentifier & levelIdentifier);
	void				Release					(void);

	void				Update					(float	dt, const CShVector2 & center);

private:

	float				m_fLastPosX;

	ShEntity2 *			m_pBackgroundEntity;

	CShArray<Plane>		m_aPlane;
};
