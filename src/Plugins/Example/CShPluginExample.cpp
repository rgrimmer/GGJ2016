#include "CShPluginExample.h"


BEGIN_DERIVED_CLASS(CShPluginExample, CShPlugin)
	// ...
END_CLASS()

CShPluginExample::CShPluginExample(void)
: CShPlugin(CShIdentifier("Example"))
{

}

/*virtual*/ CShPluginExample::~CShPluginExample(void)
{

}

void CShPluginExample::Initialize(void)
{

}

void CShPluginExample::Release(void)
{

}

/*virtual*/ void CShPluginExample::OnPlayStart(const CShIdentifier & levelIdentifier)
{

}

/*virtual*/ void CShPluginExample::OnPlayStop(const CShIdentifier & levelIdentifier)
{

}

/*virtual*/ void CShPluginExample::OnPlayPause(const CShIdentifier & levelIdentifier)
{

}

/*virtual*/ void CShPluginExample::OnPlayResume(const CShIdentifier & levelIdentifier)
{

}

/*virtual*/ void CShPluginExample::OnPreUpdate(void)
{

}

/*virtual*/ void CShPluginExample::OnPostUpdate(float dt)
{

}
