#include "AbilitySystem/AbilityTask/TargetDataUnderMouse.h"

UTargetDataUnderMouse* UTargetDataUnderMouse::CreateTargetDataUnderMouse(UGameplayAbility* OwningAbility)
{
	UTargetDataUnderMouse* TargetDataUnderMouse = NewAbilityTask<UTargetDataUnderMouse>(OwningAbility);

	return TargetDataUnderMouse;
}

void UTargetDataUnderMouse::Activate()
{
	Super::Activate();

	APlayerController* PlayerController = Ability->GetCurrentActorInfo()->PlayerController.Get();

	FHitResult HitResult;

	PlayerController->GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, false, HitResult);

	MouseTargetDataDelegate.Broadcast(HitResult.Location);
}
