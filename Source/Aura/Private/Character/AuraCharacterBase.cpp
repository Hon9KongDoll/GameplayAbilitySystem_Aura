#include "Character/AuraCharacterBase.h"

AAuraCharacterBase::AAuraCharacterBase()
{
	PrimaryActorTick.bCanEverTick = false;

	LeftWeapon = CreateDefaultSubobject<UStaticMeshComponent>(FName("LeftWeapon"));
	LeftWeapon->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	LeftWeapon->SetupAttachment(GetMesh(), FName("Weapon_L"));

	RightWeapon = CreateDefaultSubobject<UStaticMeshComponent>(FName("RightWeapon"));
	RightWeapon->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	RightWeapon->SetupAttachment(GetMesh(), FName("Weapon_R"));
}

void AAuraCharacterBase::BeginPlay()
{
	Super::BeginPlay();
}

