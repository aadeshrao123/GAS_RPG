// Copyright AadeshRao


#include "Character/HeroCharacter.h"

#include "AbilitySystemComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Player/Hero_PlayerState.h"

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
}

UAbilitySystemComponent* AHeroCharacter::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
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
	AbilitySystemComponent = HeroPlayerState->GetAbilitySystemComponent();
	AttributeSet = HeroPlayerState->GetAttributeSet();
}

void AHeroCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	// Init Ability for ServerS
	InitAbilityActorInfo();
}

void AHeroCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();
	// Init Ability for Client
	InitAbilityActorInfo();
}
