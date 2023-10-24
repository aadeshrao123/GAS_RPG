// Copyright AadeshRao


#include "Player/Hero_PlayerController.h"

#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Interaction/EnemyInterface.h"

AHero_PlayerController::AHero_PlayerController()
{
	bReplicates = true; // For Making our Controller Replicate
}

void AHero_PlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);
	CursorTrace();
}

void AHero_PlayerController::BeginPlay()
{
	Super::BeginPlay();
	check(HeroInputMappingContext); // For Check if its valid or not

	UEnhancedInputLocalPlayerSubsystem* SubSystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());// For Getting our Local Player Enhanced Sub System
	check(SubSystem);
	SubSystem->AddMappingContext(HeroInputMappingContext, 0); //Setting our Created Input Mapping Context

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


void AHero_PlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent); // casting and  to get our Enhanced Input Component Pointer 
	EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AHero_PlayerController::Move);
	// Binding our IA_Move Action to our Move Function. So When we press any move key it will call Move Function and Our Character will move accordingly
}

void AHero_PlayerController::Move(const FInputActionValue& InputActionValue)
{
	const FVector2d InputAxisVector = InputActionValue.Get<FVector2d>(); // Getting our FVector 2D from our Input Action
	const FRotator ControlRotaion = GetControlRotation();// Storing our Control Rotation in local variable
	const FRotator YawRotation (0.f, ControlRotaion.Yaw, 0.f); // For getting only Yaw value from our control rotation

	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y); // For Getting our Forward Direction
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X); // For Getting our Right Direction

	if (APawn* ControlledPawn = GetPawn<APawn>())
	{
		ControlledPawn->AddMovementInput(ForwardDirection, InputAxisVector.Y); // For Moving our Pawn Forward and Backward
		ControlledPawn->AddMovementInput(RightDirection, InputAxisVector.X); // For Moving our Pawn Right and Left
	}
}

