#include "Game.h"

//--------------------------------------------------------------------------------------------------
/// @todo comment
//--------------------------------------------------------------------------------------------------
/*explicit*/ Sound::Sound(void)
{
	for (int eSound = 0 ; eSound < e_sound_max ; ++eSound)
	{
		m_aSound[eSound] = -1;
	}
}

//--------------------------------------------------------------------------------------------------
/// @todo comment
//--------------------------------------------------------------------------------------------------
/*virtual*/ Sound::~Sound(void)
{

}

//--------------------------------------------------------------------------------------------------
/// @todo comment
//--------------------------------------------------------------------------------------------------
void Sound::Initialize(void)
{
	//
	// Load sounds definition file
	ShScriptTree * pScriptTree = ShScriptTree::Load(CShString("game_sounds.xml"));
	SH_ASSERT(NULL != pScriptTree);

	ShScriptTreeNode * pRootNode = ShScriptTree::GetRootNode(pScriptTree);
	if (!pRootNode)
	{
		ShScriptTree::Release(pScriptTree);
		SH_ASSERT_ALWAYS();
		return;
	}

	SH_ASSERT(ShScriptTreeNode::GetIdentifier(pRootNode) == CShIdentifier("sound_list"));

	for (int nChild = 0 ; nChild < ShScriptTreeNode::GetChildCount(pRootNode) ; ++nChild)
	{
		ShScriptTreeNode * pChildNode = ShScriptTreeNode::GetChild(pRootNode, nChild);
		if (ShScriptTreeNode::GetIdentifier(pChildNode) == CShIdentifier("sound"))
		{
			CShString strName;
			ShScriptTreeNode::GetAttributeValueAsString(pChildNode, CShIdentifier("name"), strName);

			CShString strValue;
			ShScriptTreeNode::GetAttributeValueAsString(pChildNode, CShIdentifier("value"), strValue);
		
			if      (strName == "music_menu")					{ m_aSound[e_sound_music_menu]                = ShSoundResource::Find(CShIdentifier(strValue)); } 
			else if (strName == "music_game")					{ m_aSound[e_sound_music_game]                = ShSoundResource::Find(CShIdentifier(strValue)); }
		}
	}
}

//--------------------------------------------------------------------------------------------------
/// @todo comment
//--------------------------------------------------------------------------------------------------
void Sound::Release(void)
{

}

//--------------------------------------------------------------------------------------------------
/// @todo comment
//--------------------------------------------------------------------------------------------------
void Sound::Update(float dt)
{

}

//--------------------------------------------------------------------------------------------------
/// @todo comment
//--------------------------------------------------------------------------------------------------
void Sound::PlaySound(ESound eSound)
{
	int soundResourceId = m_aSound[eSound];

	if (-1 != soundResourceId)
	{
		ShSoundInstance::Handle soundInstanceHandle;
		ShSoundInstance::PlaySFX(soundResourceId, soundInstanceHandle, false);
	}
}