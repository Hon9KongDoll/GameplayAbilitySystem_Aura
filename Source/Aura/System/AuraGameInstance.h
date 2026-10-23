#pragma once

#include "Engine/GameInstance.h"
#include "AuraGameInstance.generated.h"

UCLASS()
class AURA_API UAuraGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	virtual void Init() override;
};
