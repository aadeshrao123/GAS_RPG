// Copyright AadeshRao

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Hero_PlayerController.generated.h"

struct FInputActionValue;
class UInputAction;
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
	virtual void SetupInputComponent() override;

private:
	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputMappingContext> HeroInputMappingContext;

	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputAction> MoveAction;

	void Move(const FInputActionValue& InputActionValue); 
	
};
