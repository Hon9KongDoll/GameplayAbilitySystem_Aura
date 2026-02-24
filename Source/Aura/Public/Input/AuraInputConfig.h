#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "GameplayTagContainer.h"
#include "AuraInputConfig.generated.h"

class UInputAction;

USTRUCT()
struct FAuraInputAction
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UInputAction> InputAction = nullptr;

	UPROPERTY(EditDefaultsOnly)
	FGameplayTag InputTag = FGameplayTag();
};

UCLASS()
class AURA_API UAuraInputConfig : public UDataAsset
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable)
	const UInputAction* FindInputActionByGameplayTag(const FGameplayTag& GameplayTag, bool bLogNotFound = true) const;

private:
	// 输入操作关联游戏标签数据
	UPROPERTY(EditDefaultsOnly)
	TArray<FAuraInputAction> AbilityInputAction;
};
