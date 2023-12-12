// Copyright AadeshRao


#include "AbilitySystem/AbilityTasks/TargetDataUnderMouse.h"

#include "AbilitySystemComponent.h"

UTargetDataUnderMouse* UTargetDataUnderMouse::CreateTargetDataUnderMouse(UGameplayAbility* OwningAbility)
{
	UTargetDataUnderMouse* MyObj = NewAbilityTask<UTargetDataUnderMouse>(OwningAbility);
	
	return MyObj;
}

void UTargetDataUnderMouse::Activate()
{
	Super::Activate();
	APlayerController* Controller = Ability->GetCurrentActorInfo()->PlayerController.Get();
	FHitResult HitResult;
	Controller->GetHitResultUnderCursor(ECC_Visibility, false, HitResult);
	if (HitResult.bBlockingHit)
	{
		ValidData.Broadcast(HitResult.ImpactPoint);
	}
	
}
