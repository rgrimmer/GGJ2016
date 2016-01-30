#include "CShPluginPlatformer.h"

//--------------------------------------------------------------------------------------------------
/// @todo comment
//--------------------------------------------------------------------------------------------------
/*explicit*/ GameCamera::GameCamera(void)
{
}

//--------------------------------------------------------------------------------------------------
/// @todo comment
//--------------------------------------------------------------------------------------------------
/*virtual*/ GameCamera::~GameCamera(void)
{

}

//--------------------------------------------------------------------------------------------------
/// @todo comment
//--------------------------------------------------------------------------------------------------
void GameCamera::Initialize(void)
{
    // Create the Camera
    ShCamera * pCamera = ShCamera::Create(GID(global), GID(camera), false);
    SH_ASSERT(shNULL != pCamera);

    ShCamera::SetPosition(pCamera, CShVector3(0.0f, 0.0f, 100.0f));
    ShCamera::SetTarget(pCamera, CShVector3(0.0f, 0.0f, 0.0f));

    ShCamera::SetUp(pCamera, CShVector3(0.0f, 1.0f, 0.0f));

    ShCamera::SetProjectionOrtho(pCamera);
    ShCamera::SetNearPlaneDistance(pCamera, 0.0f);
    ShCamera::SetFarPlaneDistance(pCamera, 200.0f);

    float fRescaleRatio = ShDisplay::GetHeight() / (float)ShDisplay::GetWidth();
    ShCamera::SetViewport(pCamera, DISPLAY_WIDTH, DISPLAY_WIDTH * fRescaleRatio);

    ShCamera::SetCurrent2D(pCamera);
}

//--------------------------------------------------------------------------------------------------
/// @todo comment
//--------------------------------------------------------------------------------------------------
void GameCamera::Release(void)
{

}
