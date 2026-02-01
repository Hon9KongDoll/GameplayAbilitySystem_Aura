#include "Character/AuraEnemy.h"

AAuraEnemy::AAuraEnemy()
{
	bHighLight = false;
}

void AAuraEnemy::HighLightAcrot()
{
	bHighLight = true;
}

void AAuraEnemy::UnHighLightAcrot()
{
	bHighLight = false;
}
