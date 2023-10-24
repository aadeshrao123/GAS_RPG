// Copyright AadeshRao


#include "Character/EnemyCharacter.h"

#include "GAS_RPG/GAS_RPG.h"

AEnemyCharacter::AEnemyCharacter()
{
	GetMesh()->GetCollisionResponseToChannel(ECC_Visibility);
}

void AEnemyCharacter::HighlightActor()
{
	bHighlighted = true;
	GetMesh()->SetRenderCustomDepth(true);
	GetMesh()->SetCustomDepthStencilValue(CUSTOM_DEPTH_RED_HIGHLIGHT);
	Weapon->SetRenderCustomDepth(true);
	Weapon->SetCustomDepthStencilValue(CUSTOM_DEPTH_RED_HIGHLIGHT);
}

void AEnemyCharacter::UnHighlightActor()
{
	bHighlighted = false;
	GetMesh()->SetRenderCustomDepth(false);
	Weapon->SetRenderCustomDepth(false);
}
