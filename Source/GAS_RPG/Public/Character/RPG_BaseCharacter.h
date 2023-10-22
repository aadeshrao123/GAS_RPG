// Copyright AadeshRao

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "RPG_BaseCharacter.generated.h"

UCLASS()
class GAS_RPG_API ARPG_BaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ARPG_BaseCharacter();

protected:
	virtual void BeginPlay() override;
	

};
