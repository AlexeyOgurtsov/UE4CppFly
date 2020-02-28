#pragma once

/**
* Base class of all damage types in the game.
*/

#include "GameFramework/DamageType.h"
#include "MyDamageType.generated.h"

UCLASS()
class UMyDamageType : public UDamageType
{
	GENERATED_BODY()

public:
	UMyDamageType();
};