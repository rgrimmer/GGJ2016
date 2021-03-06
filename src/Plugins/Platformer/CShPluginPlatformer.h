#pragma once

#include <ShSDK/ShSDK.h>
#include <ShEngineExt/ShEngineExt.h>

#include <Box2D/Box2D.h>

#include "GameCamera.h"
#include "GameBackground.h"

#include "GameObject.h"
#include "GameObjectPlayer.h"
#include "GameObjectEnemy.h"
#include "GameObjectPlatform.h"
#include "GameObjectSensor.h"
#include "GameObjectPike.h"
#include "GameObjectRock.h"
#include "GameObjectSpear.h"

#include "GameContactListener.h"

#define RATIO_B2_SH 200.0f
#define convert_Sh_b2(a) (b2Vec2(a.m_x/RATIO_B2_SH, a.m_y/RATIO_B2_SH))

#if SH_EDITOR
#	define DISPLAY_WIDTH (1920*6)
#	define DISPLAY_HEIGHT (1080*6)
#else
#	define DISPLAY_WIDTH (1920)
#	define DISPLAY_HEIGHT (1080)
#endif // SH_EDITOR

class CShPluginPlatformer : public CShPlugin
{

public:

	enum EState
	{
		e_state_intro,
		e_state_smoke,
		e_state_play
	};

								CShPluginPlatformer			(void);
	virtual						~CShPluginPlatformer			(void);

	void						Initialize					(void);
	void						Release						(void);

	bool						RestartGame					(void);

	virtual	void				OnPlayStart					(const CShIdentifier & levelIdentifier);
	virtual	void				OnPlayStop					(const CShIdentifier & levelIdentifier);
	virtual	void				OnPlayPause					(const CShIdentifier & levelIdentifier);
	virtual	void				OnPlayResume				(const CShIdentifier & levelIdentifier);

	virtual	void				OnPreUpdate					(void);
	virtual	void				OnPostUpdate				(float dt);

	//
	// Pause State
	void SetPaused(bool paused)
	{
		m_bPaused = paused;
	}

	DECLARE_VARIABLES();

	bool m_bRestartGame;

private:

	b2Body *					CreateSpear					(b2BodyType etype, ShDummyAABB2 * pShapePike, ShDummyAABB2 * pShapeSpear);
	b2Body *					CreateBodyCircle			(const CShVector2 & position, float radius, b2BodyType type, float fFriction, unsigned int categoryBits, unsigned int maskBits, bool isBullet, bool isSensor);
	b2Body *					CreateBodyBox				(const CShVector2 & position, float fWidth, float fHeight, b2BodyType type, float fFriction, unsigned int categoryBits, unsigned int maskBits, bool isSensor);
	b2Body *					CreateBodySegment			(const CShVector2 & p1, const CShVector2 & p2, b2BodyType type, unsigned int categoryBits, unsigned int maskBits, bool isBullet, bool isSensor);

	ShScriptTree *				LoadConfig					(const CShIdentifier & levelIdentifier);

protected:

	b2World * m_pWorld;

	CShArray<b2Body*> m_aBody;

	GameContactListener *			m_pContactListener;
	GameObjectPlayer *				m_pPlayer;

	CShArray<GameObjectPike *>		m_aPike;
	CShArray<GameObjectEnemy *>		m_aEnemy;
	CShArray<GameObjectPlatform *>	m_aPlatform;
	CShArray<GameObjectSensor *>	m_aSensor;
	CShArray<GameObjectRock *>		m_aRock;

	GameObjectSpear *				m_pKinematicSpear;
	CShArray<GameObjectSpear *>		m_aSpear;
	float							m_fSpearTime;
	int								m_iCurrentSpear;

	GameCamera m_camera;
	GameBackground m_background;

	bool m_bPaused;
};
