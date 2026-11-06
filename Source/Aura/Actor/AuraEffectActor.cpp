#include "AuraEffectActor.h"
#include "Aura/AbilitySystem/AuraAttributeSet.h"

// Engine
#include "AbilitySystemBlueprintLibrary.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"

AAuraEffectActor::AAuraEffectActor()
{
	PrimaryActorTick.bCanEverTick = false;

	Sphere = CreateDefaultSubobject<USphereComponent>("Sphere");
	SetRootComponent(Sphere);

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	Mesh->SetupAttachment(Sphere);
}

void AAuraEffectActor::BeginPlay()
{
	Super::BeginPlay();

	Sphere->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::ComponentBeginOverlap);
	Sphere->OnComponentEndOverlap.AddDynamic(this, &ThisClass::ComponentEndOverlap);
}

void AAuraEffectActor::ComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex,
	bool bFromSweep,
	const FHitResult& SweepResult)
{
	if (UAbilitySystemComponent* ASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(OtherActor))
	{
		if (const UAuraAttributeSet* AuraAttributeSet = Cast<UAuraAttributeSet>(ASC->GetAttributeSet(UAuraAttributeSet::StaticClass())))
		{
			if (UAuraAttributeSet* MutableAuraAttributeSet = const_cast<UAuraAttributeSet*>(AuraAttributeSet))
			{
				MutableAuraAttributeSet->SetHealth(MutableAuraAttributeSet->GetHealth() + 25.f);

				Destroy();
			}
		}
	}
}

void AAuraEffectActor::ComponentEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{

}
