#include "Game.h"

void RegisterGameCallbacks(void)
{
	ShApplication::SetOnPreInitialize(OnPreInitialize);
	ShApplication::SetOnPostInitialize(OnPostInitialize);
	ShApplication::SetOnPreUpdate(OnPreUpdate);
	ShApplication::SetOnPostUpdate(OnPostUpdate);
	ShApplication::SetOnPreRelease(OnPreRelease);
	ShApplication::SetOnPostRelease(OnPostRelease);

	ShInput::AddOnTouchDown(OnTouchDown);
	ShInput::AddOnTouchUp(OnTouchUp);
	ShInput::AddOnTouchMove(OnTouchMove);
}

#if SH_PC
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR, int)
#else
int main(int argc, char ** argv)
#endif
{
	RegisterGameCallbacks();

	ShDisplayProperties displayProperties;
	
	displayProperties.m_bLandscape		= true;
	displayProperties.m_width           	= 1280;
	displayProperties.m_height          	= 720;

	displayProperties.m_bEnable3d       	= false;
	displayProperties.m_bEnableZ        	= false;
	displayProperties.m_bUseSpecular    	= false;
	displayProperties.m_bUsePointLights 	= false;
	displayProperties.m_bUseShadows		= false;

#if SH_PC
	return(ShMain((void*)&hInstance, displayProperties));
#else
	return(ShMain(argc, argv, displayProperties));
#endif
}

