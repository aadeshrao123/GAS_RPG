// Copyright AadeshRao


#include "AbilitySystem/RPGBlueprintFunctionLibrary.h"

#include "Game/Hero_GameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "Player/Hero_PlayerState.h"
#include "UI/HUD/HeroHUD.h"
#include "UI/WidgetController/HeroWidgetController.h"

UOverlayWidgetController* URPGBlueprintFunctionLibrary::GetOverlayWidgetController(const UObject* WorldContextObject)
{
	if (APlayerController* PC = UGameplayStatics::GetPlayerController(WorldContextObject, 0))
	{
		if (AHeroHUD* HeroHUD = Cast<AHeroHUD>(PC->GetHUD()))
		{
			AHero_PlayerState* PS = PC->GetPlayerState<AHero_PlayerState>();
			UAbilitySystemComponent* ASC = PS->GetAbilitySystemComponent();
			UAttributeSet* AS = PS->GetAttributeSet();

			const FWidgetControllerParams WCParams(PC, PS, ASC, AS);
			return HeroHUD->GetOverlayWidgetController(WCParams);
		}
	}
	return nullptr;
}

UAttributeMenuWidgetController* URPGBlueprintFunctionLibrary::GetAttributeMenuWidgetController(const UObject* WorldContextObject)
{
	if (APlayerController* PC = UGameplayStatics::GetPlayerController(WorldContextObject, 0))
	{
		if (AHeroHUD* HeroHUD = Cast<AHeroHUD>(PC->GetHUD()))
		{
			AHero_PlayerState* PS = PC->GetPlayerState<AHero_PlayerState>();
			UAbilitySystemComponent* ASC = PS->GetAbilitySystemComponent();
			UAttributeSet* AS = PS->GetAttributeSet();

			const FWidgetControllerParams WCParams(PC, PS, ASC, AS);
			return HeroHUD->GetAttributeMenuWidgetController(WCParams);
		}
	}
	return nullptr;
}

void URPGBlueprintFunctionLibrary::InitializeDefaultAttribute(const UObject* WorldContextObject, ECharacterClass CharacterClass, float Level, UAbilitySystemComponent* ASC)
{
	AHero_GameModeBase* GameMode = Cast<AHero_GameModeBase>(UGameplayStatics::GetGameMode(WorldContextObject));
	if (GameMode)
	{
		AActor* AvatarActor = ASC->GetAvatarActor();
		UCharacterClassInfo* CharacterClassInfo = GameMode->CharacterClassInfo;
		FCharacterClassDefaultInfo ClassDefaultInfo = GameMode->CharacterClassInfo->GetClassDefaultInfo(CharacterClass);

		FGameplayEffectContextHandle PrimaryAttributesContextHandle = ASC->MakeEffectContext();
		PrimaryAttributesContextHandle.AddSourceObject(AvatarActor);
		const FGameplayEffectSpecHandle PrimaryAttributesEffectSpecHandle = ASC->MakeOutgoingSpec(ClassDefaultInfo.PrimaryAttributes, Level, PrimaryAttributesContextHandle);
		ASC->ApplyGameplayEffectSpecToSelf(*PrimaryAttributesEffectSpecHandle.Data.Get());
		
		FGameplayEffectContextHandle SecondaryAttributesContextHandle = ASC->MakeEffectContext();
		SecondaryAttributesContextHandle.AddSourceObject(AvatarActor);
		const FGameplayEffectSpecHandle SecondaryAttributesEffectSpecHandle = ASC->MakeOutgoingSpec(CharacterClassInfo->SecondaryAttributes, Level, SecondaryAttributesContextHandle);
		ASC->ApplyGameplayEffectSpecToSelf(*SecondaryAttributesEffectSpecHandle.Data.Get());

		FGameplayEffectContextHandle VitalAttributesContextHandle = ASC->MakeEffectContext();
		VitalAttributesContextHandle.AddSourceObject(AvatarActor);
		const FGameplayEffectSpecHandle VitalAttributesEffectSpecHandle = ASC->MakeOutgoingSpec(CharacterClassInfo->VitalAttributes, Level, VitalAttributesContextHandle);
		ASC->ApplyGameplayEffectSpecToSelf(*VitalAttributesEffectSpecHandle.Data.Get());
	}
}

void URPGBlueprintFunctionLibrary::GiveStartupAbilituies(const UObject* WorldContextObject,
	UAbilitySystemComponent* ASC)
{
	AHero_GameModeBase* GameMode = Cast<AHero_GameModeBase>(UGameplayStatics::GetGameMode(WorldContextObject));
	if (GameMode)
	{
		UCharacterClassInfo* CharacterClassInfo = GameMode->CharacterClassInfo;

		for (TSubclassOf<UGameplayAbility> AbilityClass : CharacterClassInfo->CommonAbilities)
		{
			FGameplayAbilitySpec AbilitySpec = FGameplayAbilitySpec(AbilityClass, 1);
			ASC->GiveAbility(AbilitySpec);
		}

	}

}
