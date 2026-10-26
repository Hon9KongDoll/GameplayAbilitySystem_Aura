#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AuraCharacterBase.generated.h"

class USkeletalMeshComponent;
class UAuraPawnExtensionComponent;

UCLASS(Abstract)
class AURA_API AAuraCharacterBase : public ACharacter
{
	GENERATED_BODY()

public:
	AAuraCharacterBase();

	virtual void PreInitializeComponents() override;
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

protected:
	UPROPERTY(EditAnywhere, Category = "Combat")
	TObjectPtr<USkeletalMeshComponent> Weapon;

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Aura|Character", Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UAuraPawnExtensionComponent> PawnExtensionComponent;
};
