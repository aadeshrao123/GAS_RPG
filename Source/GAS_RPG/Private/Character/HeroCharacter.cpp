// Copyright AadeshRao


#include "Character/HeroCharacter.h"

#include "AbilitySystemComponent.h"
#include "NiagaraComponent.h"
#include "AbilitySystem/Base_AbilitySystemComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Player/Hero_PlayerController.h"
#include "Player/Hero_PlayerState.h"
#include "UI/HUD/HeroHUD.h"

AHeroCharacter::AHeroCharacter()
{
	SpringArm = CreateDefaultSubobject<USpringArmComponent>("Spring Arm");
	SpringArm->SetupAttachment(RootComponent);

	Camera = CreateDefaultSubobject<UCameraComponent>("Camera");
	Camera->SetupAttachment(SpringArm);

	LevelUpNiagaraComponent = CreateDefaultSubobject<UNiagaraComponent>("LevelUPNiagaraComponent");
	LevelUpNiagaraComponent->SetupAttachment(GetRootComponent());
	LevelUpNiagaraComponent->bAutoActivate = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 400.f, 0.f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;

	CharacterClass = ECharacterClass::Elementalist;
}

void AHeroCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void AHeroCharacter::InitAbilityActorInfo()
{
	AHero_PlayerState* HeroPlayerState = GetPlayerState<AHero_PlayerState>();
	check(HeroPlayerState);
	HeroPlayerState->GetAbilitySystemComponent()->InitAbilityActorInfo(HeroPlayerState, this);
	Cast<UBase_AbilitySystemComponent>(HeroPlayerState->GetAbilitySystemComponent())->AbilityActorInfoSet();
	AbilitySystemComponent = HeroPlayerState->GetAbilitySystemComponent();
	AttributeSet = HeroPlayerState->GetAttributeSet();
	OnASCRegistered.Broadcast(AbilitySystemComponent);

	if (AHero_PlayerController* Hero_PlayerController = Cast<AHero_PlayerController>(GetController()))
	{
		if (AHeroHUD* HeroHUD = Cast<AHeroHUD>(Hero_PlayerController->GetHUD())) 
		{
			HeroHUD->InitOverlay(Hero_PlayerController, HeroPlayerState, AbilitySystemComponent, AttributeSet); //Calling the add widget to viewport and initializing our widget controller required variables
		}
	}
	InitializeDefaultAttributes();
}

void AHeroCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	// Init Ability for ServerS
	InitAbilityActorInfo();
	AddCharacterAbilities();
}

void AHeroCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();
	// Init Ability for Client
	InitAbilityActorInfo();
}

int32 AHeroCharacter::GetPlayerLevel_Implementation()
{
	AHero_PlayerState* HeroPlayerState = GetPlayerState<AHero_PlayerState>();
	check(HeroPlayerState);
	return HeroPlayerState->GetPlayerLevel();

}

void AHeroCharacter::AddToXP_Implementation(int32 InXP)
{
	AHero_PlayerState* HeroPlayerState = GetPlayerState<AHero_PlayerState>();
	check(HeroPlayerState);
	HeroPlayerState->AddToXP(InXP);

}

void AHeroCharacter::LevelUP_Implementation()
{
	MulticastLevelUPParticles();
}

void AHeroCharacter::MulticastLevelUPParticles_Implementation() const
{
	if (IsValid(LevelUpNiagaraComponent))
	{
		const FVector CameraLocation = Camera->GetComponentLocation();
		const FVector NiagaraLocation = LevelUpNiagaraComponent->GetComponentLocation();
		const FRotator ToCameraRotation = (CameraLocation - NiagaraLocation).Rotation();
		LevelUpNiagaraComponent->SetWorldRotation(ToCameraRotation);
		LevelUpNiagaraComponent->Activate(true);
	}
}

int32 AHeroCharacter::GetXP_Implementation()
{
	AHero_PlayerState* HeroPlayerState = GetPlayerState<AHero_PlayerState>();
	check(HeroPlayerState);
	return HeroPlayerState->GetPlayerXP();
}

int32 AHeroCharacter::FindLevelForXP_Implementation(int32 InXP)
{
	AHero_PlayerState* HeroPlayerState = GetPlayerState<AHero_PlayerState>();
	check(HeroPlayerState);
	return HeroPlayerState->LevelUpInfo->FindLevelForXP(InXP);
}

int32 AHeroCharacter::GetAttributePointsReward_Implementation(int32 Level) const
{
	const AHero_PlayerState* HeroPlayerState = GetPlayerState<AHero_PlayerState>();
	check(HeroPlayerState);
	return HeroPlayerState->LevelUpInfo->LevelUpInfo[Level].AttributePointRewards;
}

int32 AHeroCharacter::GetSpellPointsReward_Implementation(int32 Level) const
{
	const AHero_PlayerState* HeroPlayerState = GetPlayerState<AHero_PlayerState>();
	check(HeroPlayerState);
	return HeroPlayerState->LevelUpInfo->LevelUpInfo[Level].SpellPointReward;
}

void AHeroCharacter::AddToPlayerLevel_Implementation(int32 InPlayerLevel)
{
	AHero_PlayerState* HeroPlayerState = GetPlayerState<AHero_PlayerState>();
	check(HeroPlayerState);
	HeroPlayerState->AddToLevel(InPlayerLevel);

	if (UBase_AbilitySystemComponent* HeroASC = Cast<UBase_AbilitySystemComponent>(AbilitySystemComponent))
	{
		HeroASC->UpdateAbilityStatuses(HeroPlayerState->GetPlayerLevel());
	}
}

void AHeroCharacter::AddToAttributePoints_Implementation(int32 InAttributePoints)
{
	AHero_PlayerState* HeroPlayerState = GetPlayerState<AHero_PlayerState>();
	check(HeroPlayerState);
	HeroPlayerState->AddAttributePoints(InAttributePoints);
}

void AHeroCharacter::AddToSpellPoints_Implementation(int32 InSpellPoints)
{
	AHero_PlayerState* HeroPlayerState = GetPlayerState<AHero_PlayerState>();
	check(HeroPlayerState);
	HeroPlayerState->AddSpellPoints(InSpellPoints);
}

int32 AHeroCharacter::GetAttributePointsPoints_Implementation() const
{
	AHero_PlayerState* HeroPlayerState = GetPlayerState<AHero_PlayerState>();
	check(HeroPlayerState);
	return HeroPlayerState->GetAttributePoints();
}

int32 AHeroCharacter::GetSpellPoints_Implementation() const
{
	AHero_PlayerState* HeroPlayerState = GetPlayerState<AHero_PlayerState>();
	check(HeroPlayerState);
	return HeroPlayerState->GetSpellPoints();
}
