#include "AbilitySystem/Data/CharacterClassInfo.h"

FCharacterClassDefaultInfo UCharacterClassInfo::GetCharacterClassDefaultInfo(const FGameplayTag& CharacterClass)
{
	return CharacterClassInformation.FindChecked(CharacterClass);
}
