// Copyright AadeshRao


#include "Character/RPG_BaseCharacter.h"

ARPG_BaseCharacter::ARPG_BaseCharacter()
{
	PrimaryActorTick.bCanEverTick = false;
	Weapon = CreateDefaultSubobject<USkeletalMeshComponent>("Weapon");
	Weapon->SetupAttachment(GetMesh(), "HandWeaponSocket");
	Weapon->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void ARPG_BaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

