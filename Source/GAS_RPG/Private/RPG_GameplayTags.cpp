// Copyright AadeshRao


#include "RPG_GameplayTags.h"
#include "GameplayTagsManager.h"



FRPG_GameplayTags FRPG_GameplayTags::GameplayTags;

void FRPG_GameplayTags::InitializeNativeGameplayTags()
{
	UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.Armor"));
}
