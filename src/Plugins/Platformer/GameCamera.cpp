#include "CShPluginPlatformer.h"

//--------------------------------------------------------------------------------------------------
/// @todo comment
//--------------------------------------------------------------------------------------------------
/*explicit*/ GameCamera::GameCamera(void)
: m_pObjectToFollow(shNULL)
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
    m_pCamera = ShCamera::Create(GID(global), GID(camera), false);
    SH_ASSERT(shNULL != m_pCamera);

    ShCamera::SetPosition(m_pCamera, CShVector3(0.0f, 0.0f, 100.0f));
    ShCamera::SetTarget(m_pCamera, CShVector3(0.0f, 0.0f, 0.0f));

    ShCamera::SetUp(m_pCamera, CShVector3(0.0f, 1.0f, 0.0f));

    ShCamera::SetProjectionOrtho(m_pCamera);
    ShCamera::SetNearPlaneDistance(m_pCamera, 0.0f);
    ShCamera::SetFarPlaneDistance(m_pCamera, 200.0f);

    ShCamera::SetViewport(m_pCamera, DISPLAY_WIDTH, DISPLAY_HEIGHT);

    ShCamera::SetCurrent2D(m_pCamera);
}

//--------------------------------------------------------------------------------------------------
/// @todo comment
//--------------------------------------------------------------------------------------------------
void GameCamera::Release(void)
{

}

//--------------------------------------------------------------------------------------------------
/// @todo comment
//--------------------------------------------------------------------------------------------------
void GameCamera::FollowObject(ShObject * pObjectToFollow)
{
	m_pObjectToFollow = pObjectToFollow;
}

//--------------------------------------------------------------------------------------------------
/// @todo comment
//--------------------------------------------------------------------------------------------------
void GameCamera::Update(float dt)
{
	if (shNULL != m_pObjectToFollow)
	{
		ShCamera::SetTarget(m_pCamera, CShVector3(ShObject::GetPosition2(m_pObjectToFollow).m_x, 0.0f, 0.0f));
		ShCamera::SetPosition(m_pCamera, CShVector3(ShObject::GetPosition2(m_pObjectToFollow).m_x, 0.0f, 200.0f));
	}
}