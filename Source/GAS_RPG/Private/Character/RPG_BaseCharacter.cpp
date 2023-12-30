// Copyright AadeshRao


#include "Character/RPG_BaseCharacter.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystem/Base_AbilitySystemComponent.h"
#include "Components/CapsuleComponent.h"
#include "GAS_RPG/GAS_RPG.h"

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

FVector ARPG_BaseCharacter::GetCombatSocketLocation_Implementation()
{
	check(Weapon)
	return Weapon->GetSocketLocation(WeaponTipSocketName);
}

bool ARPG_BaseCharacter::IsDead_Implementation() const
{
	return bDead;
}

AActor* ARPG_BaseCharacter::GetAvatar_Implementation()
{
	return this;
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

