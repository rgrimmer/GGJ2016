#pragma once

#include <ShSDK/ShSDK.h>
#include <ShEngineExt/ShEngineExt.h>

class CShPluginExample : public CShPlugin
{

public:

								CShPluginExample			(void);
	virtual						~CShPluginExample			(void);

	bool						Initialize					(void);
	bool						Release						(void);

	virtual	void				OnPlayStart					(void);
	virtual	void				OnPlayStop					(void);
	virtual	void				OnPlayPause					(void);
	virtual	void				OnPlayResume				(void);

	virtual	void				OnPreUpdate					(void);
	virtual	void				OnPostUpdate				(float dt);

	DECLARE_VARIABLES();

private:

};
