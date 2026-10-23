#pragma once

#include "CoreMinimal.h"
#include "Components/PawnComponent.h"
#include "Components/GameFrameworkInitStateInterface.h"
#include "AuraPawnExtensionComponent.generated.h"

UCLASS()
class AURA_API UAuraPawnExtensionComponent : public UPawnComponent, public IGameFrameworkInitStateInterface
{
	GENERATED_BODY()

public:
	static const FName NAME_ActorFeatureName;

	virtual void BeginPlay() override;

//{@ IGameFrameworkInitStateInterface
public:
	virtual FName GetFeatureName() const override { return NAME_ActorFeatureName; }
	virtual void CheckDefaultInitialization() override;
//@}

protected:
	virtual void OnRegister() override;
};
