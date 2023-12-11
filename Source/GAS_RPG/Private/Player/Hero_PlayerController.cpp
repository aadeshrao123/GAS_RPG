// Copyright AadeshRao


#include "Player/Hero_PlayerController.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AutomationTestExcludelist.h"
#include "EnhancedInputSubsystems.h"
#include "NavigationPath.h"
#include "NavigationSystem.h"
#include "RPG_GameplayTags.h"
#include "AbilitySystem/Base_AbilitySystemComponent.h"
#include "Components/SplineComponent.h"
#include "Input/RPGInputComponent.h"
#include "Interaction/EnemyInterface.h"

AHero_PlayerController::AHero_PlayerController()
{
	bReplicates = true; // For Making our Controller Replicate

	Spline = CreateDefaultSubobject<USplineComponent>("Spline");
}

void AHero_PlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);
	CursorTrace();
	AutoRun();
}

void AHero_PlayerController::AutoRun()
{
	if (!bAutoRunning) return;
	if (APawn* ControlledPawn = GetPawn())
	{
		const FVector LocationOnSpline = Spline->FindLocationClosestToWorldLocation(ControlledPawn->GetActorLocation(), ESplineCoordinateSpace::World);
		const FVector Direction = Spline->FindDirectionClosestToWorldLocation(LocationOnSpline, ESplineCoordinateSpace::World);
		
		ControlledPawn->AddMovementInput(Direction);

		const float DistanceToDestination = (LocationOnSpline - CachedDestination).Length();
		if (DistanceToDestination <= AutoRunAcceptanceRadius)
		{
			bAutoRunning = false;
		}
	}
}


void AHero_PlayerController::BeginPlay()
{
	Super::BeginPlay();
	check(HeroInputMappingContext); // For Check if its valid or not

	UEnhancedInputLocalPlayerSubsystem* SubSystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());// For Getting our Local Player Enhanced Sub System
	if(SubSystem)
	{
		SubSystem->AddMappingContext(HeroInputMappingContext, 0); //Setting our Created Input Mapping Context
	}

	bShowMouseCursor = true; // For Showing our Mouse Cursor While Playing
	DefaultMouseCursor = EMouseCursor::Default; // For Choosing our Mouse cursor style

	FInputModeGameAndUI InputModeData; // Creating a Struct for storing our desired Input data
	InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock); // For not locking our mouse to the viewport
	InputModeData.SetHideCursorDuringCapture(false); // For Showing our mouse Cursor on capture
	SetInputMode(InputModeData);// For setting our desired input data
	
}

void AHero_PlayerController::CursorTrace()
{
	FHitResult HitResultUnderCursor;
	GetHitResultUnderCursor(ECC_Visibility, false, HitResultUnderCursor);
	if (!HitResultUnderCursor.bBlockingHit) return;


	LastActor = ThisActor;
	ThisActor = Cast<IEnemyInterface>(HitResultUnderCursor.GetActor());

	if (ThisActor && ThisActor != LastActor)
	{
		ThisActor->HighlightActor();
	}

	if (LastActor && ThisActor != LastActor)
	{
		LastActor->UnHighlightActor();
	}
}

void AHero_PlayerController::AbilityInputTagPressed(FGameplayTag InputTag)
{
	if (InputTag.MatchesTagExact(FRPG_GameplayTags::Get().InputTag_LMB))
	{
		bTargeting = ThisActor ? true : false;
		bAutoRunning = false;
	}
}

void AHero_PlayerController::AbilityInputTagReleased(FGameplayTag InputTag)
{
	if (!InputTag.MatchesTagExact(FRPG_GameplayTags::Get().InputTag_LMB))
	{
		if (GetASC() == nullptr)
		{
			GetASC()->AbilityInputTagReleased(InputTag);
		}
		return;
	}
	if (bTargeting)
	{
		if (GetASC())
		{
			GetASC()->AbilityInputTagReleased(InputTag);
		}
	}
	else
	{
		APawn* ControlledPawn = GetPawn();
		if (FollowTime <= ShortPress && ControlledPawn)
		{
			if (UNavigationPath* NavPath = UNavigationSystemV1::FindPathToLocationSynchronously(this, ControlledPawn->GetActorLocation(), CachedDestination))
			{
				Spline->ClearSplinePoints();
				for (FVector PointLocation : NavPath->PathPoints)
				{
					Spline->AddSplinePoint(PointLocation, ESplineCoordinateSpace::World);
					DrawDebugSphere(GetWorld(), PointLocation, 5.f, 12, FColor::Red, false, 5.f);
				}
				CachedDestination = NavPath->PathPoints[NavPath->PathPoints.Num() -1];
				bAutoRunning = true;
			}
		}
		FollowTime = 0.f;
		bTargeting = false;
	}
}

void AHero_PlayerController::AbilityInputTagHeld(FGameplayTag InputTag)
{
	if (!InputTag.MatchesTagExact(FRPG_GameplayTags::Get().InputTag_LMB))
	{
		if (GetASC() == nullptr)
		{
			GetASC()->AbilityInputTagHeld(InputTag);
		}
		return;
	}
	if (bTargeting)
	{
		if (GetASC())
		{
			GetASC()->AbilityInputTagHeld(InputTag);
		}
	}
	else
	{
		FollowTime += GetWorld()->GetDeltaSeconds();

		FHitResult Hit;
		if (GetHitResultUnderCursor(ECC_Visibility, false, Hit))
		{
			CachedDestination = Hit.ImpactPoint;
		}
		if (APawn* ControlledPawn = GetPawn())
		{
			const FVector WorldDirection = (CachedDestination - ControlledPawn->GetActorLocation()).GetSafeNormal();
			ControlledPawn->AddMovementInput(WorldDirection);
		}
	}
}

UBase_AbilitySystemComponent* AHero_PlayerController::GetASC()
{
	if (ASC == nullptr)
	{
		ASC = Cast<UBase_AbilitySystemComponent>(UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(GetPawn<APawn>()));
	}
	return ASC;
}

void AHero_PlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	URPGInputComponent* RPGInputComponent = CastChecked<URPGInputComponent>(InputComponent); // casting and  to get our Enhanced Input Component Pointer 
	RPGInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AHero_PlayerController::Move);
	// Binding our IA_Move Action to our Move Function. So When we press any move key it will call Move Function and Our Character will move accordingly

	RPGInputComponent->BindAbilityAction(InputConfig, this, &ThisClass::AbilityInputTagPressed, &ThisClass::AbilityInputTagReleased, &ThisClass::AbilityInputTagHeld);
}

void AHero_PlayerController::Move(const FInputActionValue& InputActionValue)
{
	const FVector2d InputAxisVector = InputActionValue.Get<FVector2d>(); // Getting our FVector 2D from our Input Action
	const FRotator Rotation = GetControlRotation();// Storing our Control Rotation in local variable
	const FRotator YawRotation (0.f, Rotation.Yaw, 0.f); // For getting only Yaw value from our control rotation

	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y); // For Getting our Forward Direction
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X); // For Getting our Right Direction

	if (APawn* ControlledPawn = GetPawn<APawn>())
	{
		ControlledPawn->AddMovementInput(ForwardDirection, InputAxisVector.Y); // For Moving our Pawn Forward and Backward
		ControlledPawn->AddMovementInput(RightDirection, InputAxisVector.X); // For Moving our Pawn Right and Left
	}
}

