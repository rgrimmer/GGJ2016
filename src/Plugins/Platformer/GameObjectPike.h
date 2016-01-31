#pragma once

class CShPluginPlatformer;
class GameObjectPike : public GameObject
{

public:

	enum EState
	{
		e_state_none
	};

	//
	// Construction / Destruction
	explicit			GameObjectPike				(CShPluginPlatformer * pPlatformer, b2Body * body, ShEntity2 * pEntity);
	virtual				~GameObjectPike				(void);

	virtual EType		GetType						(void) const;

	void				Start						(void);
	void				End							(void);

protected:

private:

public:

protected:

private:
	CShPluginPlatformer *	m_pPlatformer;
	ShEntity2*				m_pEntity;
public:
	
};	