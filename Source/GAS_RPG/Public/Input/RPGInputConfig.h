// Copyright AadeshRao

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Engine/DataAsset.h"
#include "RPGInputConfig.generated.h"


USTRUCT(BlueprintType)
struct FRPGInputAction
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly)
	const class UInputAction* InputAction = nullptr;
	
	UPROPERTY(EditDefaultsOnly)
	FGameplayTag InputTag = FGameplayTag();
};

/**
 * 
 */

UCLASS()
class GAS_RPG_API URPGInputConfig : public UDataAsset
{
	GENERATED_BODY()
public:

	const UInputAction* FindAbilityInputActionForTag(const FGameplayTag& InputTag, bool bLogNotFound = false) const;	

	UPROPERTY(EditDefaultsOnly)
	TArray<FRPGInputAction> AbilitySystemInputAction;
};
