#include "AuraGameplayTags.h"

namespace AuraPrimaryAttributeTag
{
	UE_DEFINE_GAMEPLAY_TAG(Attribute_Primary_Strength, FName{TEXTVIEW("Attribute.Primary.Strength")})
	UE_DEFINE_GAMEPLAY_TAG(Attribute_Primary_Intelligence, FName{TEXTVIEW("Attribute.Primary.Intelligence")})
	UE_DEFINE_GAMEPLAY_TAG(Attribute_Primary_Resilience, FName{TEXTVIEW("Attribute.Primary.Resilience")})
	UE_DEFINE_GAMEPLAY_TAG(Attribute_Primary_Vigor, FName{TEXTVIEW("Attribute.Primary.Vigor")})
}

namespace AuraSecondaryAttributeTag
{
	UE_DEFINE_GAMEPLAY_TAG(Attribute_Secondary_Armor, FName{ TEXTVIEW("Attribute.Secondary.Armor") })
	UE_DEFINE_GAMEPLAY_TAG(Attribute_Secondary_ArmorPenetration, FName{ TEXTVIEW("Attribute.Secondary.ArmorPenetration") })
	UE_DEFINE_GAMEPLAY_TAG(Attribute_Secondary_BlockChance, FName{ TEXTVIEW("Attribute.Secondary.BlockChance") })
	UE_DEFINE_GAMEPLAY_TAG(Attribute_Secondary_CriticalHitChance, FName{ TEXTVIEW("Attribute.Secondary.CriticalHitChance") })
	UE_DEFINE_GAMEPLAY_TAG(Attribute_Secondary_CriticalHitDamage, FName{ TEXTVIEW("Attribute.Secondary.CriticalHitDamage") })
	UE_DEFINE_GAMEPLAY_TAG(Attribute_Secondary_CriticalHitResistance, FName{ TEXTVIEW("Attribute.Secondary.CriticalHitResistance") })
	UE_DEFINE_GAMEPLAY_TAG(Attribute_Secondary_HealthRegeneration, FName{ TEXTVIEW("Attribute.Secondary.HealthRegeneration") })
	UE_DEFINE_GAMEPLAY_TAG(Attribute_Secondary_ManaRegeneration, FName{ TEXTVIEW("Attribute.Secondary.ManaRegeneration") })
	UE_DEFINE_GAMEPLAY_TAG(Attribute_Secondary_MaxHealth, FName{ TEXTVIEW("Attribute.Secondary.MaxHealth") })
	UE_DEFINE_GAMEPLAY_TAG(Attribute_Secondary_MaxMana, FName{ TEXTVIEW("Attribute.Secondary.MaxMana") })
}

namespace AuraDamageTag
{
	UE_DEFINE_GAMEPLAY_TAG(Damage, FName{ TEXTVIEW("Damage") })
}

namespace AuraInputTag
{
	UE_DEFINE_GAMEPLAY_TAG(InputTag_LMB, FName{ TEXTVIEW("InputTag.LMB") })
	UE_DEFINE_GAMEPLAY_TAG(InputTag_RMB, FName{ TEXTVIEW("InputTag.RMB") })
	UE_DEFINE_GAMEPLAY_TAG(InputTag_1, FName{ TEXTVIEW("InputTag.1") })
	UE_DEFINE_GAMEPLAY_TAG(InputTag_2, FName{ TEXTVIEW("InputTag.2") })
	UE_DEFINE_GAMEPLAY_TAG(InputTag_3, FName{ TEXTVIEW("InputTag.3") })
	UE_DEFINE_GAMEPLAY_TAG(InputTag_4, FName{ TEXTVIEW("InputTag.4") })
}

namespace AuraCharacterClassTag
{
	UE_DEFINE_GAMEPLAY_TAG(CharacterClass_Elementalist, FName{ TEXTVIEW("CharacterClass.Elementalist") })
	UE_DEFINE_GAMEPLAY_TAG(CharacterClass_Ranger, FName{ TEXTVIEW("CharacterClass.Ranger") })
	UE_DEFINE_GAMEPLAY_TAG(CharacterClass_Warrior, FName{ TEXTVIEW("CharacterClass.Warrior") })
}