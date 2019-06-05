#pragma once

/**
* Base class of all HUDs in the game.
*/

#include "MyGameplayWidgetBase.h"
#include "MyHUDWidgetBase.generated.h"

UCLASS()
class UMyHUDWidgetBase : public UMyGameplayWidgetBase
{
	GENERATED_BODY()

public:

protected:
	virtual bool Initialize() override;
};