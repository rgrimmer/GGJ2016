#pragma once

#include <ShSDK/ShSDK.h>
#include <ShEngineExt/ShEngineExt.h>

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

};
