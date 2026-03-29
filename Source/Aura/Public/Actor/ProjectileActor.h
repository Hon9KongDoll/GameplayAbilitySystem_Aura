#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ProjectileActor.generated.h"

class UNiagaraSystem;
class USphereComponent;
class UProjectileMovementComponent;

UCLASS()
class AURA_API AProjectileActor : public AActor
{
	GENERATED_BODY()
	
public:	
	AProjectileActor();

protected:
	virtual void BeginPlay() override;

	virtual void Destroyed() override;

	UFUNCTION()
	void SphereComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<USphereComponent> SphereComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UProjectileMovementComponent> ProjectileMovementComponent;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UNiagaraSystem> ImpactEffect;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<USoundBase> ImpactSound;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<USoundBase> LoopingSound;

private:
	// 用于客户端是否触发 SphereComponentBeginOverlap
	uint8 bHitObject : 1;

	UPROPERTY()
	TObjectPtr<UAudioComponent> LoopingSoundComponent;
};
