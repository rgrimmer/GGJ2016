#pragma once

#include <ShSDK/ShSDK.h>

#include "GameState.h"
#include "GameStateMenuMain.h"
#include "GameStateGame.h"

#include "GameStateManager.h"

void OnPreInitialize	(void);
void OnPostInitialize	(void);
void OnPreUpdate		(float dt);
void OnPostUpdate		(float dt);
void OnPreRelease		(void);
void OnPostRelease		(void);

void OnTouchDown		(int iTouch, float fPositionX, float fPositionY);
void OnTouchUp			(int iTouch, float fPositionX, float fPositionY);
void OnTouchMove		(int iTouch, float fPositionX, float fPositionY);