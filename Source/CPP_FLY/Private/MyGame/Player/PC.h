#pragma once

/**
* Main player controller (non-test).
*/

#include "MyGameBase/Player/PCBase.h"
#include "PC.generated.h"

UCLASS(BlueprintType)
class APC : public APCBase
{
	GENERATED_BODY()

public:
	APC();
};