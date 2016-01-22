#include "Extension.h"

#include <ShSDK/ShSDK.h>

//
// Include plugins
#include "../Plugins/Example/CShPluginExample.h"

//
// Declare plugins
static CShPluginExample plugin_example;

extern "C"
{

EXTENSION_GGJ2016_EXPORT void ExtensionInitialize(void)
{
	//
	// Initialize plugins
	plugin_example.Initialize();

	// Register plugins here
	ShApplication::RegisterPlugin(&plugin_example);
}

EXTENSION_GGJ2016_EXPORT void ExtensionRelease(void)
{
	// Release plugins here
	plugin_example.Release();
}

}

