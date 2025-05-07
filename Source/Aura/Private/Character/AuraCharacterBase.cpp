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

UAbilitySystemComponent* AAuraCharacterBase::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

UAttributeSet* AAuraCharacterBase::GetAttributeSet() const
{
	return AttributeSet;
}

void AAuraCharacterBase::BeginPlay()
{
	Super::BeginPlay();
}

