// Copyright AadeshRao


#include "Player/Hero_PlayerController.h"

#include "EnhancedInputSubsystems.h"

AHero_PlayerController::AHero_PlayerController()
{
	bReplicates = true; // For Making our Controller Replicate
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
