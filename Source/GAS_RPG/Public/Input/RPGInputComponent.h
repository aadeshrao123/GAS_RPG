// Copyright AadeshRao

#pragma once

#include "CoreMinimal.h"
#include "EnhancedInputComponent.h"
#include "RPGInputConfig.h"
#include "RPGInputComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class GAS_RPG_API URPGInputComponent : public UEnhancedInputComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	URPGInputComponent();

	template<class UserClass, typename PressedFuncType, typename ReleasedFuncType, typename HeldFuncType>
	void BindAbilityAction(const URPGInputConfig* InputConfig, UserClass* UserObject, PressedFuncType PressedFunc, ReleasedFuncType ReleasedFunc, HeldFuncType HeldFunc);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;
};

template <class UserClass, typename PressedFuncType, typename ReleasedFuncType, typename HeldFuncType>
void URPGInputComponent::BindAbilityAction(const URPGInputConfig* InputConfig, UserClass* UserObject,
	PressedFuncType PressedFunc, ReleasedFuncType ReleasedFunc, HeldFuncType HeldFunc)
{
	check(InputConfig);

	for (const FRPGInputAction Action : InputConfig->AbilitySystemInputAction)
	{
		if (Action.InputAction && Action.InputTag.IsValid())
		{
			if (PressedFunc)
			{
				BindAction(Action.InputAction, ETriggerEvent::Started, UserObject, PressedFunc, Action.InputTag);
			}
			if (ReleasedFunc)
			{
				BindAction(Action.InputAction, ETriggerEvent::Completed, UserObject, HeldFunc, Action.InputTag);
			}
			if (HeldFunc)
			{
				BindAction(Action.InputAction, ETriggerEvent::Triggered, UserObject, HeldFunc, Action.InputTag);
			}
		}
	}
	
}
