#pragma once

#include "CoreMinimal.h"
#include "Components/PawnComponent.h"
#include "Components/GameFrameworkInitStateInterface.h"
#include "AuraPawnExtensionComponent.generated.h"

/**
 * 为所有 Pawn 类添加通用功能，使其可用于角色、载具等对象。
 * 此组件负责协调其他组件的初始化流程。
 */
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
	virtual bool CanChangeInitState(UGameFrameworkComponentManager* Manager, FGameplayTag CurrentState, FGameplayTag DesiredState) const;
	virtual void HandleChangeInitState(UGameFrameworkComponentManager* Manager, FGameplayTag CurrentState, FGameplayTag DesiredState) override;
	virtual void OnActorInitStateChanged(const FActorInitStateChangedParams& Params) override;
	virtual void CheckDefaultInitialization() override;
//@}

protected:
	virtual void OnRegister() override;
};
