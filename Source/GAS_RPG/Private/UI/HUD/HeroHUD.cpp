// Copyright AadeshRao


#include "UI/HUD/HeroHUD.h"
#include "UI/Widget/HeroUserWidget.h"

void AHeroHUD::BeginPlay()
{
	Super::BeginPlay();
	UUserWidget* Widget = CreateWidget<UUserWidget>(GetWorld(), OverlayWidgetClass);
	Widget->AddToViewport();
}
