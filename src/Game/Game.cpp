#include "Game.h"

/**
 * Called before engine initialization
 */
void Game::OnPreInitialize(void)
{
	// nothing here
}

/**
 * Called after engine initialization
 */
void Game::OnPostInitialize(void)
{
//	GameStateManager::instance().initialize();
}

/**
 * Called on each frame, before the engine update
 */
void Game::OnPreUpdate(float dt)
{
	// nothing here
}

/**
 * Called on each frame, after the engine update
 */
void Game::OnPostUpdate(float dt)
{
//	GameStateManager::instance().update(deltaTimeInMs);
}

/**
 * Called before the engine release
 */
void Game::OnPreRelease(void)
{
	// nothing here
}

/**
 * Called after the engine release
 */
void Game::OnPostRelease(void)
{
//	GameStateManager::instance().release();
}

/**
 * Called after a touch down
 */
void Game::OnTouchDown(int iTouch, float fPositionX, float fPositionY)
{
//	GameStateManager::instance().touchBegin(iTouch, CShVector2(fPositionX, fPositionY));
}

/**
 * Called after a touch up
 */
void Game::OnTouchUp(int iTouch, float fPositionX, float fPositionY)
{
//	GameStateManager::instance().touchEnd(iTouch, CShVector2(fPositionX, fPositionY));
}

/**
 * Called after a touch move
 */
void Game::OnTouchMove(int iTouch, float fPositionX, float fPositionY)
{
//	GameStateManager::instance().touchMove(iTouch, CShVector2(fPositionX, fPositionY));
}



