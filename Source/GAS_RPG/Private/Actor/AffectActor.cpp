// Copyright AadeshRao


#include "Actor/AffectActor.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystemInterface.h"
#include "NavigationSystemTypes.h"
#include "AbilitySystem/Base_AttributeSet.h"
#include "Components/SphereComponent.h"


AAffectActor::AAffectActor()
{
	PrimaryActorTick.bCanEverTick = false;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	SetRootComponent(Mesh);

	Sphere = CreateDefaultSubobject<USphereComponent>("Sphere");
	Sphere->SetupAttachment(Mesh);
}

void AAffectActor::OnOverlap(UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
	const FHitResult& SweepResult)
{
	// Change this to apply a Gameplay Effect. Using const_Cast is just for test Attribute Sets
	if(IAbilitySystemInterface* ASCInterface = Cast<IAbilitySystemInterface>(OtherActor))
	{
		UE_LOG(LogTemp, Warning, TEXT("CastSucceded"));

		const UBase_AttributeSet* HeroAttributeSet = Cast<UBase_AttributeSet>(ASCInterface->GetAbilitySystemComponent()->GetAttributeSet(UBase_AttributeSet::StaticClass()));
		
		UBase_AttributeSet* MutableHeroAttributeSet = const_cast<UBase_AttributeSet*>(HeroAttributeSet);
		MutableHeroAttributeSet->SetHealth(HeroAttributeSet->GetHealth() + 25.f);
		Destroy();
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("CastFailed"));
	}
}

void AAffectActor::EndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
}

void AAffectActor::BeginPlay()
{
	Super::BeginPlay();
	Sphere->OnComponentBeginOverlap.AddDynamic(this, &AAffectActor::OnOverlap);
	Sphere->OnComponentEndOverlap.AddDynamic(this, &AAffectActor::EndOverlap);
	
}
