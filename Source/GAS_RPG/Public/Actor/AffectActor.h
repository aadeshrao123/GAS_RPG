// Copyright AadeshRao

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AffectActor.generated.h"

class UGameplayEffect;
class USphereComponent;

UCLASS()
class GAS_RPG_API AAffectActor : public AActor
{
	GENERATED_BODY()

public:
	AAffectActor();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintCallable)
	void ApplyEffectTOTarget(AActor* Target, TSubclassOf<UGameplayEffect> GameplayEffectClass);

private:

};
