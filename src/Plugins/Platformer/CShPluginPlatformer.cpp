#include "CShPluginPlatformer.h"


BEGIN_DERIVED_CLASS(CShPluginPlatformer, CShPlugin)
	// ...
END_CLASS()

CShPluginPlatformer::CShPluginPlatformer(void)
: CShPlugin(CShIdentifier("Example"))
{

}

/*virtual*/ CShPluginPlatformer::~CShPluginPlatformer(void)
{

}

void CShPluginPlatformer::Initialize(void)
{

}

void CShPluginPlatformer::Release(void)
{

}

/*virtual*/ void CShPluginPlatformer::OnPlayStart(const CShIdentifier & levelIdentifier)
{

}

/*virtual*/ void CShPluginPlatformer::OnPlayStop(const CShIdentifier & levelIdentifier)
{

}

/*virtual*/ void CShPluginPlatformer::OnPlayPause(const CShIdentifier & levelIdentifier)
{

}

/*virtual*/ void CShPluginPlatformer::OnPlayResume(const CShIdentifier & levelIdentifier)
{

}

/*virtual*/ void CShPluginPlatformer::OnPreUpdate(void)
{

}

/*virtual*/ void CShPluginPlatformer::OnPostUpdate(float dt)
{

}
