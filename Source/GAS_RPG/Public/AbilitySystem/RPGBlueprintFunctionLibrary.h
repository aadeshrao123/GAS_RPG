// Copyright AadeshRao

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "RPGBlueprintFunctionLibrary.generated.h"

class UOverlayWidgetController;
/**
 * 
 */
UCLASS()
class GAS_RPG_API URPGBlueprintFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:

	UFUNCTION(BlueprintPure, Category = "RPGAbilitySystemLibrary | WidgetController")
	static UOverlayWidgetController* GetOverlayWidgetController(const UObject* WorldContextObject);
};
