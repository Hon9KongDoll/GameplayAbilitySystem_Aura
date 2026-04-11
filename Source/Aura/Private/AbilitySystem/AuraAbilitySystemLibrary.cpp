#include "AbilitySystem/AuraAbilitySystemLibrary.h"
#include "HUD/AuraHUD.h"
#include "GameMode/AuraGameMode.h"
#include "PlayerState/AuraPlayerState.h"
#include "AbilitySystem/Data/CharacterClassInfo.h"
#include "UserWidget/WidgetController/AuraWidgetController.h"

//Engine
#include "Kismet/GameplayStatics.h"
#include "AbilitySystemComponent.h"

UOverlayWidgetController* UAuraAbilitySystemLibrary::GetOverlayWidgetController(const UObject* WorldContextObject)
{
	if (APlayerController* PlayerController = UGameplayStatics::GetPlayerController(WorldContextObject, 0))
	{
		if (AAuraHUD* AuraHUD = Cast<AAuraHUD>(PlayerController->GetHUD()))
		{
			AAuraPlayerState* AuraPlayerState = PlayerController->GetPlayerState<AAuraPlayerState>();

			UAbilitySystemComponent* AbilitySystemComponent = AuraPlayerState->GetAbilitySystemComponent();

			UAttributeSet* AttributeSet = AuraPlayerState->GetAttributeSet();

			const FWidgetControllerParams WidgetControllerParams(PlayerController, AuraPlayerState, AbilitySystemComponent, AttributeSet);

			return AuraHUD->GetOverlayWidgetController(WidgetControllerParams);
		}
		
	}

	return nullptr;
}

UAttributeMenuWidgetController* UAuraAbilitySystemLibrary::GetAttributeMenuWidgetController(const UObject* WorldContextObject)
{
	if (APlayerController* PlayerController = UGameplayStatics::GetPlayerController(WorldContextObject, 0))
	{
		if (AAuraHUD* AuraHUD = Cast<AAuraHUD>(PlayerController->GetHUD()))
		{
			AAuraPlayerState* AuraPlayerState = PlayerController->GetPlayerState<AAuraPlayerState>();

			UAbilitySystemComponent* AbilitySystemComponent = AuraPlayerState->GetAbilitySystemComponent();

			UAttributeSet* AttributeSet = AuraPlayerState->GetAttributeSet();

			const FWidgetControllerParams WidgetControllerParams(PlayerController, AuraPlayerState, AbilitySystemComponent, AttributeSet);

			return AuraHUD->GetAttributeMenuWidgetController(WidgetControllerParams);
		}

	}

	return nullptr;
}

void UAuraAbilitySystemLibrary::InitializeCharacterClassDefaultAttributes(const UObject* WorldContextObject, UAbilitySystemComponent* ASC, const FGameplayTag& CharacterClass, float Level)
{
	AAuraGameMode* GameMode = Cast<AAuraGameMode>(UGameplayStatics::GetGameMode(WorldContextObject));

	UCharacterClassInfo* CharacterClassInfo = GameMode->CharacterClassInfo;

	FCharacterClassDefaultInfo CharacterClassDefaultInfo = CharacterClassInfo->GetCharacterClassDefaultInfo(CharacterClass);

	FGameplayEffectContextHandle PrimaryAttributeContextHandle = ASC->MakeEffectContext();
	const FGameplayEffectSpecHandle PrimaryAttributeSpecHandle = ASC->MakeOutgoingSpec(CharacterClassDefaultInfo.PrimaryAttributes, Level, PrimaryAttributeContextHandle);
	ASC->ApplyGameplayEffectSpecToSelf(*PrimaryAttributeSpecHandle.Data.Get());

	FGameplayEffectContextHandle SecondaryAttributeContextHandle = ASC->MakeEffectContext();
	const FGameplayEffectSpecHandle SecondaryAttributeSpecHandle = ASC->MakeOutgoingSpec(CharacterClassInfo->SecondaryAttributes, Level, SecondaryAttributeContextHandle);
	ASC->ApplyGameplayEffectSpecToSelf(*SecondaryAttributeSpecHandle.Data.Get());

	FGameplayEffectContextHandle VitalAttributeContextHandle = ASC->MakeEffectContext();
	const FGameplayEffectSpecHandle VitalAttributeSpecHandle = ASC->MakeOutgoingSpec(CharacterClassInfo->VitalAttributes, Level, VitalAttributeContextHandle);
	ASC->ApplyGameplayEffectSpecToSelf(*VitalAttributeSpecHandle.Data.Get());
}
