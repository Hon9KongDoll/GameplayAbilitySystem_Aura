#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "GameplayTagContainer.h"
#include "AuraGameplayAbility.generated.h"

UCLASS()
class AURA_API UAuraGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()
	
public:
	// ≥ı º ‰»Î±Í«©
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FGameplayTag StartupInputTag;
};
