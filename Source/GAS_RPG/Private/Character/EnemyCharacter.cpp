// Copyright AadeshRao


#include "Character/EnemyCharacter.h"

#include "RPG_GameplayTags.h"
#include "AbilitySystem/Base_AbilitySystemComponent.h"
#include "AbilitySystem/Base_AttributeSet.h"
#include "AbilitySystem/RPGBlueprintFunctionLibrary.h"
#include "Components/WidgetComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GAS_RPG/GAS_RPG.h"
#include "UI/Widget/HeroUserWidget.h"

void AEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();
	GetCharacterMovement()->MaxWalkSpeed = BaseWalkSpeed;
	InitAbilityActorInfo();

	URPGBlueprintFunctionLibrary::GiveStartupAbilituies(this, AbilitySystemComponent);
	
	if (UHeroUserWidget* HeroWidget = Cast<UHeroUserWidget>(HealthBar->GetUserWidgetObject()))
	{
		HeroWidget->SetWidgetController(this);
	}
	
	UBase_AttributeSet* BaseAttributeSet = CastChecked<UBase_AttributeSet>(AttributeSet);
	if (BaseAttributeSet)
	{
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(BaseAttributeSet->GetHealthAttribute()).AddLambda(
	[this](const FOnAttributeChangeData& Data)
		{
			OnHealthChanged.Broadcast(Data.NewValue);
		});
		
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(BaseAttributeSet->GetMaxHealthAttribute()).AddLambda(
	[this](const FOnAttributeChangeData& Data)
		{
			OnHealthChanged.Broadcast(Data.NewValue);
		});
	}
	AbilitySystemComponent->RegisterGameplayTagEvent(FRPG_GameplayTags::Get().HitReact, EGameplayTagEventType::NewOrRemoved).AddUObject(this, &AEnemyCharacter::HitReactChange);
	
	OnHealthChanged.Broadcast(BaseAttributeSet->GetHealth());
	OnMaxHealthChanged.Broadcast(BaseAttributeSet->GetMaxHealth());
}

AEnemyCharacter::AEnemyCharacter()
{
	GetMesh()->GetCollisionResponseToChannel(ECC_Visibility);
	
	AbilitySystemComponent = CreateDefaultSubobject<UBase_AbilitySystemComponent>("AbilitySystemComponent");
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);
	
	AttributeSet = CreateDefaultSubobject<UBase_AttributeSet>("AttributeSet");
	
	HealthBar = CreateDefaultSubobject<UWidgetComponent>("HealthBar");
	HealthBar->SetupAttachment(GetRootComponent());
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

int32 AEnemyCharacter::GetPlayerLevel()
{
	return Level;
}

void AEnemyCharacter::Die()
{
	SetLifeSpan(LifeSpan);
	Super::Die();
}

void AEnemyCharacter::InitAbilityActorInfo()
{
	AbilitySystemComponent->InitAbilityActorInfo(this, this);
	Cast<UBase_AbilitySystemComponent>(AbilitySystemComponent)->AbilityActorInfoSet();
	InitializeDefaultAttributes();
}

void AEnemyCharacter::InitializeDefaultAttributes() const
{
	URPGBlueprintFunctionLibrary::InitializeDefaultAttribute(this, CharacterClass, Level, AbilitySystemComponent);	
}

void AEnemyCharacter::HitReactChange(const FGameplayTag CallbackTag, int32 NewCount)
{
	bHitReacting = NewCount > 0;
	GetCharacterMovement()->MaxWalkSpeed = bHitReacting ? 0.f : BaseWalkSpeed;
}
