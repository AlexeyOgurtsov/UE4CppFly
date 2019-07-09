#pragma once

#include "UObject/Interface.h"
#include "IWeaponInventory.generated.h"

UINTERFACE()
class UWeaponInventory : public UInterface
{
	GENERATED_BODY()

public:
};

class IWeaponInventory
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void Fire(int32 InWeaponIndex = 0);
};
