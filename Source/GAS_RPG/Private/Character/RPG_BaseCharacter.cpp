// Copyright AadeshRao


#include "Character/RPG_BaseCharacter.h"

#include "AbilitySystemComponent.h"
#include "RPGAbilityTypes.h"
#include "RPG_GameplayTags.h"
#include "AbilitySystem/Base_AbilitySystemComponent.h"
#include "Components/CapsuleComponent.h"
#include "GAS_RPG/GAS_RPG.h"
#include "Kismet/GameplayStatics.h"

ARPG_BaseCharacter::ARPG_BaseCharacter()
{
	PrimaryActorTick.bCanEverTick = false;

	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_Camera,ECR_Ignore);
	GetCapsuleComponent()->SetGenerateOverlapEvents(false);
	GetMesh()->SetCollisionResponseToChannel(ECC_Camera, ECR_Ignore);
	GetMesh()->SetCollisionResponseToChannel(ECC_Projectile, ECR_Overlap);
	GetMesh()->SetGenerateOverlapEvents(true);

	Weapon = CreateDefaultSubobject<USkeletalMeshComponent>("Weapon");
	Weapon->SetupAttachment(GetMesh(), "HandWeaponSocket");
	Weapon->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

UAbilitySystemComponent* ARPG_BaseCharacter::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

UAnimMontage* ARPG_BaseCharacter::GetHitReactMontage_Implementation()
{
	return HitReactMontage;
}

void ARPG_BaseCharacter::Die()
{
	Weapon->DetachFromComponent(FDetachmentTransformRules(EDetachmentRule::KeepWorld, true));
	MulticastHandelDeath();
}

void ARPG_BaseCharacter::MulticastHandelDeath_Implementation()
{
	UGameplayStatics::PlaySoundAtLocation(this, DeathSound, GetActorLocation(), GetActorRotation());
	
	Weapon->SetSimulatePhysics(true);
	Weapon->SetEnableGravity(true);
	Weapon->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);

	GetMesh()->SetSimulatePhysics(true);
	GetMesh()->SetEnableGravity(true);
	GetMesh()->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);
	GetMesh()->SetCollisionResponseToChannel(ECC_WorldStatic, ECR_Block);
	
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	Dissolve();
	bDead = true;
}

void ARPG_BaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

FVector ARPG_BaseCharacter::GetCombatSocketLocation_Implementation(const FGameplayTag& MontageTag)
{
	const FRPG_GameplayTags& GameplayTags = FRPG_GameplayTags::Get();
	if (MontageTag.MatchesTagExact(GameplayTags.Sockets_Attack_Weapon) && IsValid(Weapon))
	{
		return Weapon->GetSocketLocation(WeaponTipSocketName);
	}
	if (MontageTag.MatchesTagExact(GameplayTags.Sockets_Attack_LeftHand))
	{
		return GetMesh()->GetSocketLocation(LeftHandSocketName);
	}
	if (MontageTag.MatchesTagExact(GameplayTags.Sockets_Attack_RightHand))
	{
		return GetMesh()->GetSocketLocation(RightHandSocketName);
	}
	if (MontageTag.MatchesTagExact(GameplayTags.Sockets_Attack_Tail))
	{
		return GetMesh()->GetSocketLocation(TailSocketName);
	}
	
	return FVector();
}

bool ARPG_BaseCharacter::IsDead_Implementation() const
{
	return bDead;
}

AActor* ARPG_BaseCharacter::GetAvatar_Implementation()
{
	return this;
}

TArray<FTaggedMontage> ARPG_BaseCharacter::GetAttackMontage_Implementation()
{
	return AttackMontages;
}

UNiagaraSystem* ARPG_BaseCharacter::GetBloodEffect_Implementation()
{
	return BloodEffect;
}

FTaggedMontage ARPG_BaseCharacter::GetTaggedMontageByTag_Implementation(const FGameplayTag& MontageTag)
{
	for (FTaggedMontage TaggedMontage : AttackMontages)
	{
		if (TaggedMontage.MontageTag == MontageTag)
		{
			return TaggedMontage;
		}
	}
	return FTaggedMontage();
}

int32 ARPG_BaseCharacter::GetMinionCount_Implementation()
{
	return MinionCount;
}

void ARPG_BaseCharacter::IncrementtMinionCount_Implementation(int32 Amount)
{
	MinionCount += Amount;
}

ECharacterClass ARPG_BaseCharacter::GetCharacterClass_Implementation()
{
	return CharacterClass;
}

void ARPG_BaseCharacter::InitAbilityActorInfo()
{
}

void ARPG_BaseCharacter::ApplyEffectToSelf(TSubclassOf<UGameplayEffect> GameplayEffectClass, float Level) const
{
	check(IsValid(AbilitySystemComponent));
	check(GameplayEffectClass);
	FGameplayEffectContextHandle ContextHandle = GetAbilitySystemComponent()->MakeEffectContext();
	ContextHandle.AddSourceObject(this);
	const FGameplayEffectSpecHandle SpecHandle = GetAbilitySystemComponent()->MakeOutgoingSpec(GameplayEffectClass, Level, ContextHandle);
	GetAbilitySystemComponent()->ApplyGameplayEffectSpecToTarget(*SpecHandle.Data.Get(), GetAbilitySystemComponent());
}

void ARPG_BaseCharacter::InitializeDefaultAttributes() const
{
	ApplyEffectToSelf(DefaultPrimaryAttributes, 1.f);
	ApplyEffectToSelf(DefaultSecondaryAttributes, 1.f);
	ApplyEffectToSelf(DefaultVitalAttributes, 1.f);
}

void ARPG_BaseCharacter::AddCharacterAbilities()
{
	UBase_AbilitySystemComponent* ASC = Cast<UBase_AbilitySystemComponent>(AbilitySystemComponent);
	if (!HasAuthority()) return;

	ASC->AddCharacterAbilities(StartupAbility);
	ASC->AddCharacterPassiveAbilities(StartupPassiveAbility);
	
}

void ARPG_BaseCharacter::Dissolve()
{
	if (MeshDissolveMaterialInstance)
	{
		UMaterialInstanceDynamic* MeshDynamicMaterial = UMaterialInstanceDynamic::Create(MeshDissolveMaterialInstance, this);
		GetMesh()->SetMaterial(0, MeshDynamicMaterial);
		StartDissolveMaterialTimelineMesh(MeshDynamicMaterial);
	}
	if (WeaponDissolveMaterialInstance)
	{
		UMaterialInstanceDynamic* WeaponDynamicMaterial = UMaterialInstanceDynamic::Create(WeaponDissolveMaterialInstance, this);
		Weapon->SetMaterial(0, WeaponDynamicMaterial);
		StartDissolveMaterialTimelineWeapon(WeaponDynamicMaterial);
	}
}

