#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "CombatInterface.generated.h"

UINTERFACE(MinimalAPI)
class UCombatInterface : public UInterface
{
	GENERATED_BODY()
};

class AURA_API ICombatInterface
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintNativeEvent)
	int32 GetCharacterLevel();

	UFUNCTION(BlueprintNativeEvent)
	FVector GetCombatSocketLocation();
};
