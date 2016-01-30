#include "CShPluginPlatformer.h"

//--------------------------------------------------------------------------------------------------
/// @todo comment
//--------------------------------------------------------------------------------------------------
/*explicit*/ GameCamera::GameCamera(void)
: m_pCamera(shNULL)
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
void GameCamera::Initialize(const CShIdentifier & levelIdentifier)
{
	// Create the Camera
	m_pCamera = ShCamera::Create(levelIdentifier, GID(camera), false);
	SH_ASSERT(shNULL != m_pCamera);

	ShCamera::SetUp(m_pCamera, CShVector3(0.0f, 1.0f, 0.0f));

	ShCamera::SetProjectionOrtho(m_pCamera);
	ShCamera::SetNearPlaneDistance(m_pCamera, 0.001f);
	ShCamera::SetFarPlaneDistance(m_pCamera, 200.0f);
	ShCamera::SetViewport(m_pCamera, DISPLAY_WIDTH, DISPLAY_HEIGHT);
	ShCamera::SetTarget(m_pCamera, CShVector3(0.0f, 0.0f, 0.0f));
	ShCamera::SetPosition(m_pCamera, CShVector3(0.0f, 0.0f, 150.0f));

	ShCamera::SetCurrent2D(m_pCamera);
}

//--------------------------------------------------------------------------------------------------
/// @todo comment
//--------------------------------------------------------------------------------------------------
void GameCamera::Release(void)
{
	ShCamera::SetTarget(m_pCamera, CShVector3(0.0f, 0.0f, 0.0f));
	ShCamera::SetPosition(m_pCamera, CShVector3(0.0f, 0.0f, 150.0f));
}

//--------------------------------------------------------------------------------------------------
/// @todo comment
//--------------------------------------------------------------------------------------------------
void GameCamera::Update(float dt, const CShVector2 & center)
{
	ShCamera::SetTarget(m_pCamera, CShVector3(center.m_x, 0.0f, 0.0f));
	ShCamera::SetPosition(m_pCamera, CShVector3(center.m_x, 0.0f, 150.0f));
}
