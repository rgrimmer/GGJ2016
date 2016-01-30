#pragma once

class GameBackground
{

public:

	struct Plane
	{
		float speed;
		CShArray<ShEntity2 *> aEntities;
		float totalWidth;
	};

	//
	// Construction / Destruction
	explicit			GameBackground			(void);
	virtual				~GameBackground			(void);

	void				Initialize				(const CShIdentifier & levelIdentifier);
	void				Release					(void);

	void				LoadParallax			(const CShIdentifier & levelIdentifier, ShScriptTreeNode * pNode);

	void				Update					(float	dt, const CShVector2 & center);

private:

	float				m_fLastPosX;

	ShEntity2 *			m_pBackgroundEntity;

	CShArray<Plane>		m_aPlane;
};
