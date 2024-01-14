// Copyright AadeshRao


#include "AbilitySystem/Abilities/RPGSummonAbility.h"

#include "Kismet/KismetSystemLibrary.h"

TArray<FVector> URPGSummonAbility::GetSpawnLocations()
{
	const FVector ForwardVector = GetAvatarActorFromActorInfo()->GetActorForwardVector();
	const FVector Location = GetAvatarActorFromActorInfo()->GetActorLocation();
	const float DeltaSpread = SpawnSpread / NumMinions;

	const FVector LeftOfSpread = ForwardVector.RotateAngleAxis(-SpawnSpread / 2.f, FVector::UpVector);

	TArray<FVector> SpawnLocations;
	for (int32 i = 0; i < NumMinions; i++)
	{
		const FVector Direction = LeftOfSpread.RotateAngleAxis((DeltaSpread * i), FVector::UpVector);
		const FVector ChosenSpawnLocation = Location + Direction * FMath::FRandRange(MinSpawnDistance, MaxSpawnDistance);
		SpawnLocations.Add(ChosenSpawnLocation);
	}
	return SpawnLocations;
}
