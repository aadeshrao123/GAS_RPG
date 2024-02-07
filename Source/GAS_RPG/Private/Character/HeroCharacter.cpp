// Copyright AadeshRao


#include "Character/HeroCharacter.h"

#include "AbilitySystemComponent.h"
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

int32 AHeroCharacter::GetPlayerLevel()
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
