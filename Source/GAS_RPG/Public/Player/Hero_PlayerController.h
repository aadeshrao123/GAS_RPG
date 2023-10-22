// Copyright AadeshRao

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Hero_PlayerController.generated.h"

class UInputMappingContext;
/**
 * 
 */
UCLASS()
class GAS_RPG_API AHero_PlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	AHero_PlayerController();

protected:
	virtual  void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputMappingContext> HeroInputMappingContext;
	
	
};
