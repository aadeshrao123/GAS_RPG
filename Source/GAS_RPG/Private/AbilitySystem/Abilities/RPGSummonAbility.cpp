﻿// Copyright AadeshRao


#include "AbilitySystem/Abilities/RPGSummonAbility.h"

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
		FVector ChosenSpawnLocation = Location + Direction * FMath::FRandRange(MinSpawnDistance, MaxSpawnDistance);

		FHitResult Hit;
		GetWorld()->LineTraceSingleByChannel(Hit, ChosenSpawnLocation + FVector(0.f, 0.f, 500.f), ChosenSpawnLocation - FVector(0.f, 0.f, 500.f), ECC_Visibility);
		if (Hit.bBlockingHit)
		{
			ChosenSpawnLocation = Hit.ImpactPoint;
		}
	
		SpawnLocations.Add(ChosenSpawnLocation);
	}
	return SpawnLocations;
}

TSubclassOf<APawn> URPGSummonAbility::GetRandomMinionClass()
{
	return MinionClasses[FMath::RandRange(0, MinionClasses.Num() - 1)];
}