#include "Game.h"

/**
 * Called before engine initialization
 */
void OnPreInitialize(void)
{
	// nothing here
}

/**
 * Called after engine initialization
 */
void OnPostInitialize(void)
{
	GameStateManager::instance().initialize();
}

/**
 * Called on each frame, before the engine update
 */
void OnPreUpdate(float deltaTimeInMs)
{
	// nothing here
}

/**
 * Called on each frame, after the engine update
 */
void OnPostUpdate(float deltaTimeInMs)
{
//	GameStateManager::instance().update(deltaTimeInMs);
}

/**
 * Called before the engine release
 */
void OnPreRelease(void)
{
	// nothing here
}

/**
 * Called after the engine release
 */
void OnPostRelease(void)
{
//	GameStateManager::instance().release();
}

/**
 * Called after a touch down
 */
void OnTouchDown(int iTouch, float fPositionX, float fPositionY)
{
//	GameStateManager::instance().touchBegin(iTouch, CShVector2(fPositionX, fPositionY));
}

/**
 * Called after a touch up
 */
void OnTouchUp(int iTouch, float fPositionX, float fPositionY)
{
//	GameStateManager::instance().touchEnd(iTouch, CShVector2(fPositionX, fPositionY));
}

/**
 * Called after a touch move
 */
void OnTouchMove(int iTouch, float fPositionX, float fPositionY)
{
//	GameStateManager::instance().touchMove(iTouch, CShVector2(fPositionX, fPositionY));
}



