#include "Character/AuraCharacterBase.h"

//Engine
#include "Components/SkeletalMeshComponent.h"

AAuraCharacterBase::AAuraCharacterBase()
{
	PrimaryActorTick.bCanEverTick = false;

	Weapon = CreateDefaultSubobject<USkeletalMeshComponent>("Weapon");
	Weapon->SetupAttachment(GetMesh(), "WeaponHandSocket");
}

void AAuraCharacterBase::BeginPlay()
{
	Super::BeginPlay();
}