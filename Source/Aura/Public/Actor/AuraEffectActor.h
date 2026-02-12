#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AuraEffectActor.generated.h"

class UGameplayEffect;

UCLASS()
class AURA_API AAuraEffectActor : public AActor
{
	GENERATED_BODY()
	
public:	
	AAuraEffectActor();

protected:
	UFUNCTION(BlueprintCallable, Category = "Gameplay Effect")
	void ApplyEffectToTarget(AActor* InTargetActor, TSubclassOf<UGameplayEffect> InGameplayEffectClass);

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Gameplay Effect")
	TSubclassOf<UGameplayEffect> InstantGameplayEffectClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Gameplay Effect")
	TSubclassOf<UGameplayEffect> DurationGameplayEffectClass;
};
