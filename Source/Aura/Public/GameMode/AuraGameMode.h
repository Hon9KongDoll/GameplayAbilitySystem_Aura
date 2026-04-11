#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "AbilitySystem/Data/CharacterClassInfo.h"
#include "AuraGameMode.generated.h"

UCLASS()
class AURA_API AAuraGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UCharacterClassInfo> CharacterClassInfo;
};