#include "Extension.h"

#include <ShSDK/ShSDK.h>

//
// Include plugins
#include "../Plugins/Example/CShPluginExample.h"
#include "../Plugins/Platformer/CShPluginPlatformer.h"

//
// Declare plugins
static CShPluginExample plugin_example;
static CShPluginPlatformer plugin_platformer;

extern "C"
{

EXTENSION_GGJ2016_EXPORT void ExtensionInitialize(void)
{
	//
	// Initialize plugins
	plugin_example.Initialize();
	plugin_platformer.Initialize();

	// Register plugins here
	ShApplication::RegisterPlugin(&plugin_example);
	ShApplication::RegisterPlugin(&plugin_platformer);
}

EXTENSION_GGJ2016_EXPORT void ExtensionRelease(void)
{
	// Release plugins here
	plugin_platformer.Release();
	plugin_example.Release();
}

}

