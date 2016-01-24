#pragma once

#include <ShSDK/ShSDK.h>

#include "GameState.h"
#include "GameStateMenuMain.h"
#include "GameStateGame.h"

#include "GameStateManager.h"

class Game
{
public:

	static void OnPreInitialize		(void);
	static void OnPostInitialize	(void);
	static void OnPreUpdate			(float dt);
	static void OnPostUpdate		(float dt);
	static void OnPreRelease		(void);
	static void OnPostRelease		(void);

	static void OnTouchDown			(int iTouch, float fPositionX, float fPositionY);
	static void OnTouchUp			(int iTouch, float fPositionX, float fPositionY);
	static void OnTouchMove			(int iTouch, float fPositionX, float fPositionY);
};
