#pragma once

/**
* Normal physical damage (normally to be used by default).
*/

#include "MyDamageType.h"
#include "PhysicalDamageType.generated.h"

UCLASS()
class UPhysicalDamageType : public UMyDamageType
{
	GENERATED_BODY()

public:
	UPhysicalDamageType();
};