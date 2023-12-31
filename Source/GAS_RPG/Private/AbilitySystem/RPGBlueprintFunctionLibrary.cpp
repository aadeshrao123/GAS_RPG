﻿// Copyright AadeshRao


#include "AbilitySystem/RPGBlueprintFunctionLibrary.h"

#include "RPGAbilityTypes.h"
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
	AActor* AvatarActor = ASC->GetAvatarActor();
	UCharacterClassInfo* CharacterClassInfo = GetCharacterClassInfo(WorldContextObject);
	FCharacterClassDefaultInfo ClassDefaultInfo = CharacterClassInfo->GetClassDefaultInfo(CharacterClass);

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

void URPGBlueprintFunctionLibrary::GiveStartupAbilituies(const UObject* WorldContextObject,
	UAbilitySystemComponent* ASC, ECharacterClass CharacterClass)
{
	UCharacterClassInfo* CharacterClassInfo = GetCharacterClassInfo(WorldContextObject);
	if(CharacterClassInfo == nullptr) return; 
	for (TSubclassOf<UGameplayAbility> AbilityClass : CharacterClassInfo->CommonAbilities)
	{
		FGameplayAbilitySpec AbilitySpec = FGameplayAbilitySpec(AbilityClass, 1);
		ASC->GiveAbility(AbilitySpec);
	}
	const FCharacterClassDefaultInfo DefaultInfo = CharacterClassInfo->GetClassDefaultInfo(CharacterClass);
	for (TSubclassOf<UGameplayAbility> AbilityClass : DefaultInfo.StartupAbilities)
	{
		if (ICombatInterface* CombatInterface = Cast<ICombatInterface>(ASC->GetAvatarActor()))
		{
			const int PlayerLevel = CombatInterface->GetPlayerLevel();
			FGameplayAbilitySpec AbilitySpec = FGameplayAbilitySpec(AbilityClass, PlayerLevel);
			ASC->GiveAbility(AbilitySpec);
		}
	}

}

UCharacterClassInfo* URPGBlueprintFunctionLibrary::GetCharacterClassInfo(const UObject* WorldContextObject)
{
	AHero_GameModeBase* GameMode = Cast<AHero_GameModeBase>(UGameplayStatics::GetGameMode(WorldContextObject));
	if (GameMode)
	{
		return GameMode->CharacterClassInfo;
	}
	return nullptr;
}

bool URPGBlueprintFunctionLibrary::IsBlockedHit(const FGameplayEffectContextHandle& EffectContextHandle)
{
	if (const FRPGGameplayEffectContext* RPGEffectContext = static_cast<const FRPGGameplayEffectContext*>(EffectContextHandle.Get()))
	{
		return RPGEffectContext->IsBlockedHit();
	}
	return false;
}

bool URPGBlueprintFunctionLibrary::IsCriticalHit(const FGameplayEffectContextHandle& EffectContextHandle)
{
	if (const FRPGGameplayEffectContext* RPGEffectContext = static_cast<const FRPGGameplayEffectContext*>(EffectContextHandle.Get()))
	{
		return RPGEffectContext->IsCriticalHit();
	}
	return false;
}

void URPGBlueprintFunctionLibrary::SetIsBlockedHit(FGameplayEffectContextHandle& EffectContextHandle,
	bool bIsInBlockingHit)
{
	if (FRPGGameplayEffectContext* RPGEffectContext = static_cast<FRPGGameplayEffectContext*>(EffectContextHandle.Get()))
	{
		RPGEffectContext->SetIsBlockedHit(bIsInBlockingHit);
	}
}

void URPGBlueprintFunctionLibrary::SetIsCriticalHit(FGameplayEffectContextHandle& EffectContextHandle,
	bool bIsInCriticalHit)
{
	if (FRPGGameplayEffectContext* RPGEffectContext = static_cast<FRPGGameplayEffectContext*>(EffectContextHandle.Get()))
	{
		RPGEffectContext->SetIsCriticalHit(bIsInCriticalHit);
	}
}

void URPGBlueprintFunctionLibrary::GetLivePlayerWithinRadius(const UObject* WorldContextObject,
	TArray<AActor*>& OutOverlappingActors, TArray<AActor*> ActorsToIgnore, float Radius, const FVector& SphereOrigin)
{
	FCollisionQueryParams SphereParams;
	SphereParams.AddIgnoredActors(ActorsToIgnore);
	TArray<FOverlapResult> Overlaps;
	if (const UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull))
	{
		World->OverlapMultiByObjectType(Overlaps, SphereOrigin, FQuat::Identity, FCollisionObjectQueryParams(FCollisionObjectQueryParams::InitType::AllDynamicObjects), FCollisionShape::MakeSphere(Radius), SphereParams);
		for (FOverlapResult& Overlap : Overlaps)
		{
			if (Overlap.GetActor()->Implements<UCombatInterface>() && !ICombatInterface::Execute_IsDead(Overlap.GetActor()))
			{
				OutOverlappingActors.AddUnique(ICombatInterface::Execute_GetAvatar(Overlap.GetActor()));
			}
		}
	}
}

bool URPGBlueprintFunctionLibrary::IsNotFriend(AActor* FirstActor, AActor* SecondActor)
{
	const bool bFirstIsPlayer= FirstActor->ActorHasTag(FName("Player"));
	const bool bSecondIsPlayer= SecondActor->ActorHasTag(FName("Player"));

	const bool bFirstIsEnemy= FirstActor->ActorHasTag(FName("Enemy"));
	const bool bSecondIsEnemy= SecondActor->ActorHasTag(FName("Enemy"));

	const bool BothArePlayer = bFirstIsPlayer && bSecondIsPlayer;
	const bool BothAreEnemies = bFirstIsEnemy && bSecondIsEnemy;

	const bool Friends = BothArePlayer || BothAreEnemies;
	return !Friends;
}
