// Copyright AadeshRao

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "GameplayTagContainer.h"
#include "Hero_PlayerController.generated.h"

class USplineComponent;
class UBase_AbilitySystemComponent;
struct FInputActionValue;
class UInputAction;
class UInputMappingContext;
class IEnemyInterface;
class URPGInputConfig;

/**
 * 
 */
UCLASS()
class GAS_RPG_API AHero_PlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	AHero_PlayerController();
	virtual void PlayerTick(float DeltaTime) override;

protected:
	virtual  void BeginPlay() override;
	virtual void SetupInputComponent() override;

private:
	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputMappingContext> HeroInputMappingContext;

	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputAction> MoveAction;

	void Move(const FInputActionValue& InputActionValue);

	void CursorTrace();
	IEnemyInterface* LastActor;
	IEnemyInterface* ThisActor;

	void AbilityInputTagPressed(FGameplayTag InputTag);
	void AbilityInputTagReleased(FGameplayTag InputTag);
	void AbilityInputTagHeld(FGameplayTag InputTag);

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<URPGInputConfig> InputConfig;

	TObjectPtr<UBase_AbilitySystemComponent> ASC;
	
	UBase_AbilitySystemComponent* GetASC();

	FVector CachedDestination = FVector::ZeroVector;
	float FollowTime = 0.f; //How Long we have pressed the button
	float ShortPress = 0.5f;
	bool bAutoRunning = false;
	bool bTargeting = false;
	FHitResult HitResultUnderCursor;

	UPROPERTY(EditDefaultsOnly)
	float AutoRunAcceptanceRadius = 50.f;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USplineComponent> Spline;

	void AutoRun();
};
