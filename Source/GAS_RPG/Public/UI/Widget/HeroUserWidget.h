// Copyright AadeshRao

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HeroUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class GAS_RPG_API UHeroUserWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable)
	void SetWidgetController(UObject* InWidgetController); // For setting up our Widget Controller for our Widget.
	
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UObject> WidgetController; //For getting a pointer to our widget controller

protected:
	
	UFUNCTION(BlueprintImplementableEvent)
	void WidgetControllerSet(); // It will be when our Widget Controller have been set up

};
