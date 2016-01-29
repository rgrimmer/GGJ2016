#pragma once

#include <ShSDK/ShSDK.h>
#include <ShEngineExt/ShEngineExt.h>

#include "GameObject.h"
#include "GameObjectPlayer.h"

class CShPluginPlatformer : public CShPlugin
{

public:

								CShPluginPlatformer			(void);
	virtual						~CShPluginPlatformer			(void);

	void						Initialize					(void);
	void						Release						(void);

	virtual	void				OnPlayStart					(const CShIdentifier & levelIdentifier);
	virtual	void				OnPlayStop					(const CShIdentifier & levelIdentifier);
	virtual	void				OnPlayPause					(const CShIdentifier & levelIdentifier);
	virtual	void				OnPlayResume				(const CShIdentifier & levelIdentifier);

	virtual	void				OnPreUpdate					(void);
	virtual	void				OnPostUpdate				(float dt);

	DECLARE_VARIABLES();

private:
	b2Body* CreateBodyCircle(const CShVector2 & position, float radius, b2BodyType type, unsigned int categoryBits, unsigned int maskBits, bool isBullet, bool isSensor);
	b2Body*	CreateBodyShape(const CShVector2 & position, float fWidth, float fHeight, b2BodyType type, unsigned int categoryBits, unsigned int maskBits, bool isSensor);
};
