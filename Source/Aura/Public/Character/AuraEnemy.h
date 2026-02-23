#pragma once

#include "CoreMinimal.h"
#include "Character/AuraCharacterBase.h"
#include "Interface/EnemyInterface.h"
#include "AuraEnemy.generated.h"

UCLASS()
class AURA_API AAuraEnemy : public AAuraCharacterBase, public IEnemyInterface
{
	GENERATED_BODY()

public:
	AAuraEnemy();

	/** Enemy Interface */
	virtual void HighLightAcrot() override;
	virtual void UnHighLightAcrot() override;
	/** End Enemy Interface */

	/** Combat Interface */
	virtual int32 GetCharacterLevel_Implementation() override;
	/** end Combat Interface */

protected:
	virtual void BeginPlay() override;

private:
	virtual void InitAbilityActorInfo() override;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int32 Level = 1.f;
};